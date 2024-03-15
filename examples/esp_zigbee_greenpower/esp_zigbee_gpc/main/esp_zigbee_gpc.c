/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee Green Power combo Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_check.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "string.h"
#include <stdint.h>
#include <string.h>
#include "ha/esp_zigbee_ha_standard.h"
#include "zgp/esp_zigbee_zgps.h"
#include "esp_zigbee_gpc.h"

#if ! defined ZB_ZGP_SIMPLE_COMBO_START_AS_ZR && ! defined ZB_COORDINATOR_ROLE
#error define ZB_COORDINATOR_ROLE to compile zc tests
#endif

#if defined ZB_ZGP_SIMPLE_COMBO_START_AS_ZR && ! defined ZB_ROUTER_ROLE
#error Router role is not compiled!
#endif

#if defined ZB_ZGP_SIMPLE_COMBO_START_AS_ZR && ! defined ZB_SECURITY_INSTALLCODES
#error define ZB_SECURITY_INSTALLCODES
#endif

static const char *TAG = "ESP_ZGP_COMBO";

static esp_zb_zgps_mapping_entry_t zgp_mapping_table_items[ZGP_MAX_MAPPING_TABLE_ENTRIES] = {
    {0},
};
static esp_zb_zgps_mapping_entry_t *zgp_mapping_table[ZGP_MAX_MAPPING_TABLE_ENTRIES] = {
    NULL,
};
static uint16_t zgp_mapping_table_length = ZGP_MAX_MAPPING_TABLE_ENTRIES;

static void zb_zgp_accept_commissioning_handler(esp_zgp_approve_comm_params_t *params);
static void zb_zgp_commissioning_done_handler(esp_zb_zgpd_id_t zgpd_id, esp_zb_zgp_comm_status_t result);
static void zb_zgp_mode_change_handler(esp_zb_zgp_mode_t new_mode, esp_zb_zgp_mode_change_reason_t reason);

static switch_func_pair_t button_func_pair[] = {{GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}};

static void zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    switch (button_func_pair->func) {
    case SWITCH_ONOFF_TOGGLE_CONTROL: {
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zgps_start_commissioning_on_endpoint(HA_LIGHT_ENDPOINT, 0);
        esp_zb_lock_release();
        ESP_EARLY_LOGI(TAG, "Enter commissioning mode");
#if !ZGP_COMBO_PROXY_ENABLED
        esp_zgp_zcl_proxy_commissioning_enter_req_t cmd_req;
        cmd_req.exit_mode = ESP_ZGP_COMMISSIONING_EXIT_MODE_ON_PAIRING_SUCCESS;
        cmd_req.commissioning_window = 180;
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zgp_zcl_proxy_commissioning_mode_enter_cmd_req(&cmd_req);
        esp_zb_lock_release();
        ESP_EARLY_LOGI(TAG, "Send commissioning mode to ZGP proxy");
#endif
    } break;
    default:
        break;
    }
}

static esp_err_t deferred_driver_init(void)
{
    light_driver_init(LIGHT_DEFAULT_OFF);
    ESP_RETURN_ON_FALSE(switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), zb_buttons_handler), ESP_FAIL, TAG,
                        "Failed to initialize switch driver");
    return ESP_OK;
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_RETURN_ON_FALSE(esp_zb_bdb_start_top_level_commissioning(mode_mask) == ESP_OK, , TAG, "Failed to start Zigbee bdb commissioning");
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Initialize Zigbee stack");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Deferred driver initialization %s", deferred_driver_init() ? "failed" : "successful");
            ESP_LOGI(TAG, "Device started up in %s factory-reset mode", esp_zb_bdb_is_factory_new() ? "" : "non");
            if (esp_zb_bdb_is_factory_new()) {
                ESP_LOGI(TAG, "Start network formation");
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
            } else {
                ESP_LOGI(TAG, "Device rebooted");
            }
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG,
                     "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d, Short "
                     "Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4], extended_pan_id[3], extended_pan_id[2],
                     extended_pan_id[1], extended_pan_id[0], esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGI(TAG, "Restart network formation (status: %s)", esp_err_to_name(err_status));
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Network steering started");
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        break;
    case ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS:
        if (err_status == ESP_OK) {
            if (*(uint8_t *)esp_zb_app_signal_get_params(p_sg_p)) {
                ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", esp_zb_get_pan_id(), *(uint8_t *)esp_zb_app_signal_get_params(p_sg_p));
            } else {
                ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", esp_zb_get_pan_id());
            }
        }
        break;
    case ESP_ZB_ZGP_SIGNAL_APPROVE_COMMISSIONING: {
        esp_zb_zgp_signal_approve_comm_params_t *app_comm_params = (esp_zb_zgp_signal_approve_comm_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        zb_zgp_accept_commissioning_handler(app_comm_params->param);
    } break;
    case ESP_ZB_ZGP_SIGNAL_COMMISSIONING: {
        esp_zb_zgp_signal_commissioning_params_t *comm_params = (esp_zb_zgp_signal_commissioning_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        zb_zgp_commissioning_done_handler(comm_params->zgpd_id, comm_params->result);
    } break;
    case ESP_ZB_ZGP_SIGNAL_MODE_CHANGE: {
        esp_zb_zgp_signal_mode_change_params_t *signal_params = (esp_zb_zgp_signal_mode_change_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        zb_zgp_mode_change_handler(signal_params->new_mode, signal_params->reason);
    } break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type, esp_err_to_name(err_status));
        break;
    }
}

static esp_err_t zb_attribute_handler(const esp_zb_zcl_set_attr_value_message_t *message)
{
    esp_err_t ret = ESP_OK;
    bool light_state = 0;

    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    ESP_LOGI(TAG, "Received message: endpoint(%d), cluster(0x%x), attribute(0x%x), data size(%d)", message->info.dst_endpoint, message->info.cluster,
             message->attribute.id, message->attribute.data.size);
    if (message->info.dst_endpoint == HA_LIGHT_ENDPOINT) {
        if (message->info.cluster == ESP_ZB_ZCL_CLUSTER_ID_ON_OFF) {
            if (message->attribute.id == ESP_ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID && message->attribute.data.type == ESP_ZB_ZCL_ATTR_TYPE_BOOL) {
                light_state = message->attribute.data.value ? *(bool *)message->attribute.data.value : light_state;
                ESP_LOGI(TAG, "Light sets to %s", light_state ? "On" : "Off");
                light_driver_set_power(light_state);
            }
        }
    }
    return ret;
}

static esp_err_t zb_green_power_handler(const esp_zb_zcl_cmd_green_power_recv_message_t *message)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    ESP_LOGI(TAG, "Received ZGP %s message: endpoint(%d), cluster(0x%x), command(0x%x)", message->info.command.direction == 1 ? "proxy" : "sink",
             message->info.dst_endpoint, message->info.cluster, message->info.command.id);
    return ret;
}

static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
    case ESP_ZB_CORE_SET_ATTR_VALUE_CB_ID:
        ret = zb_attribute_handler((esp_zb_zcl_set_attr_value_message_t *)message);
        break;
    case ESP_ZB_CORE_CMD_GREEN_POWER_RECV_CB_ID:
        ret = zb_green_power_handler((esp_zb_zcl_cmd_green_power_recv_message_t *)message);
        break;
    default:
        ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
        break;
    }
    return ret;
}

static void esp_zb_task(void *pvParameters)
{
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);

    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    esp_zb_zgp_set_skip_gpdf(!ZGP_COMBO_PROXY_ENABLED);
    esp_zb_zgps_set_mapping_table((const esp_zb_zgps_mapping_entry_t **)zgp_mapping_table, &zgp_mapping_table_length);
    esp_zb_zgps_set_communication_mode(ESP_ZB_ZGP_COMMUNICATION_MODE_GROUPCAST_DERIVED);
    esp_zb_zgps_set_commissioning_exit_mode(ESP_ZGP_COMMISSIONING_EXIT_MODE_ON_PAIRING_SUCCESS);
    esp_zb_zgps_set_commissioning_window(180);
    esp_zb_zgps_set_functionality(ESP_ZGP_GPSB_FUNCTIONALITY, ESP_ZGP_ACTIVE_FUNCTIONALITY_ID);
    esp_zb_zgps_set_security_level(ESP_ZB_ZGP_FILL_GPS_SECURITY_LEVEL(
        ESP_ZB_ZGP_SEC_LEVEL_FULL_NO_ENC, ESP_ZB_ZGP_SEC_LEVEL_PROTECTION_WITH_GP_LINK_KEY, ESP_ZB_ZGP_SEC_LEVEL_PROTECTION_DO_NOT_INVOLVE_TC));

    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_on_off_light_cfg_t light_cfg = ESP_ZB_DEFAULT_ON_OFF_LIGHT_CONFIG();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = HA_LIGHT_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID,
        .app_device_version = 0
    };
    esp_zb_ep_list_add_ep(ep_list, esp_zb_on_off_light_clusters_create(&light_cfg), endpoint_config);
    esp_zb_device_register(ep_list);
    esp_zb_core_action_handler_register(zb_action_handler);

    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_main_loop_iteration();
}

void app_main()
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}

static bool mapping_table_delete_entry_by_zgpd_id(esp_zb_zgpd_id_t *zgpd_id)
{
    for (uint8_t i = 0; i < ZGP_MAX_MAPPING_TABLE_ENTRIES; i++) {
        if (zgp_mapping_table[i] != NULL) {
            esp_zb_zgpd_id_t id = {
                .app_id = zgp_mapping_table[i]->options & 7U,
                .endpoint = zgp_mapping_table[i]->gpd_endpoint,
                .addr = zgp_mapping_table[i]->gpd_id,
            };

            if (ESP_ZB_ZGPD_IDS_COMPARE(zgpd_id, &id)) {
                zgp_mapping_table[i] = NULL;
            }
        }
    }

    return true;
}

static bool mapping_table_add_entry(esp_zb_zgpd_id_t *zgpd_id, uint8_t gpd_command, uint8_t endpoint, uint16_t profile, uint16_t cluster_id,
                                    uint8_t zcl_command)
{
    for (uint8_t i = 0; i < ZGP_MAX_MAPPING_TABLE_ENTRIES; i++) {
        if (zgp_mapping_table[i] == NULL) {
            esp_zb_zgps_mapping_entry_t *entry;
            entry = &zgp_mapping_table_items[i];
            entry->options = zgpd_id->app_id;
            memcpy(&entry->gpd_id, &zgpd_id->addr, sizeof(esp_zb_zgpd_addr_t));
            entry->gpd_endpoint = zgpd_id->endpoint;
            entry->gpd_command = gpd_command;
            entry->endpoint = endpoint;
            entry->profile = profile;
            entry->cluster = cluster_id;
            entry->zcl_command = zcl_command;
            entry->zcl_payload_length = ESP_ZB_ZGP_MAPPING_ENTRY_PARSED_PAYLOAD;
            zgp_mapping_table[i] = entry;
            return true;
        }
    }
    return false;
}

static void zb_zgp_accept_commissioning_handler(esp_zgp_approve_comm_params_t *params)
{
    bool accept = true;
    /* Delete all entries for this device, if any */
    mapping_table_delete_entry_by_zgpd_id(&params->zgpd_id);
    ESP_LOGI(TAG, "handle accept commissioning information");
    /* check supported Device ID */
    if (params->device_id == ESP_ZB_ZGP_ON_OFF_SWITCH_DEV_ID || params->device_id == ESP_ZB_ZGP_GEN_8_CONT_SWITCH_DEV_ID ||
        params->device_id == ESP_ZB_ZGP_MANUF_SPECIFIC_DEV_ID) {
        /* check Application Description if present */
        if (params->num_of_reports == 0) {
            /* GPD didn't give us any specific data, let's be as generic as possible */
            accept = mapping_table_add_entry(&params->zgpd_id, ESP_ZB_GPDF_CMD_UNDEFINED, params->pairing_endpoint, ESP_ZB_AF_GP_PROFILE_ID,
                                             ESP_ZB_ZGP_ZCL_CLUSTER_ID_UNDEFINED, /* Match all cluster_ids */
                                             ESP_ZB_ZGP_ZCL_CMD_ID_UNDEFINED);
        } else {
            bool ent_added = true;

            /* Check that at least one cluster matched */
            for (uint8_t idx = 0; idx < params->num_of_reports; idx++) {
                uint8_t len = params->reports[idx].len;
                uint8_t *data = params->reports[idx].data;
                uint8_t i = 0;

                while (i < len) {
                    uint16_t cluster_id;
                    uint8_t num_of_attr_records, client_server, cluster_role;
                    bool manuf_id_present;

                    /* check Data point options */
                    num_of_attr_records = (data[i] & 0x07) + 1;
                    client_server = data[i] & 0x08;
                    cluster_role = client_server ? ESP_ZB_ZCL_CLUSTER_SERVER_ROLE : ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE;
                    manuf_id_present = (data[i] & 0x10) ? true : false;
                    i++;

                    memcpy(&cluster_id, &data[i], sizeof(uint16_t));
                    i += 2;

                    /* check Cluster ID and role */
                    if ((cluster_role == ESP_ZB_ZCL_CLUSTER_SERVER_ROLE &&
                         (cluster_id == ESP_ZB_ZCL_CLUSTER_ID_BASIC || cluster_id == ESP_ZB_ZCL_CLUSTER_ID_POWER_CONFIG ||
                          cluster_id == ESP_ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT || cluster_id == ESP_ZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING ||
                          cluster_id == ESP_ZB_ZCL_CLUSTER_ID_IAS_ZONE)) ||
                        (cluster_role == ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE &&
                         (cluster_id == ESP_ZB_ZCL_CLUSTER_ID_SCENES || cluster_id == ESP_ZB_ZCL_CLUSTER_ID_ON_OFF ||
                          cluster_id == ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL))) {
                        accept = mapping_table_add_entry(&params->zgpd_id, ESP_ZB_GPDF_CMD_UNDEFINED, params->pairing_endpoint,
                                                         ESP_ZB_AF_GP_PROFILE_ID, cluster_id, ESP_ZB_ZGP_ZCL_CMD_ID_UNDEFINED);
                        if (accept == false) {
                            break;
                        } else {
                            ent_added = true;
                        }
                    }

                    if (manuf_id_present) {
                        i += 2;
                    }
                    while (num_of_attr_records--) {
                        i += 2 + 1 + 1 + (data[i + 3] & 0x0FU) + 1;
                    }
                }

                if (accept == false) {
                    break;
                }
            }

            if (accept == false) {
                if (ent_added == false) {
                    mapping_table_delete_entry_by_zgpd_id(&params->zgpd_id);
                }
            } else {
                accept = ent_added;
            }
        }
    } else {
        accept = false;
    }

    esp_zb_zgps_accept_commissioning(accept);
}

void zb_zgp_commissioning_done_handler(esp_zb_zgpd_id_t zgpd_id, esp_zb_zgp_comm_status_t result)
{
    ESP_LOGI(TAG, "Commissioning done with status: %d", result);
    if (result == ESP_ZB_ZGP_COMMISSIONING_COMPLETED || result == ESP_ZB_ZGP_ZGPD_DECOMMISSIONED) {
        ESP_LOGI(TAG, "Commissioning information: app_id %hd endpoint %hd and src_id is 0x%lx", zgpd_id.app_id, zgpd_id.endpoint,
                 zgpd_id.addr.src_id);
    }
    if (result == ESP_ZB_ZGP_ZGPD_DECOMMISSIONED) {
        mapping_table_delete_entry_by_zgpd_id(&zgpd_id);
    }
}

void zb_zgp_mode_change_handler(esp_zb_zgp_mode_t new_mode, esp_zb_zgp_mode_change_reason_t reason)
{
    ESP_LOGI(TAG, "ZGP commissioning new mode %hx caused by: %hx", (uint8_t)new_mode, (uint8_t)reason);
}
