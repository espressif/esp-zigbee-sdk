/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include "esp_flash.h"
#include "esp_flash_partitions.h"
#include "esp_partition.h"

#include "esp_zigbee.h"
#include "ezbee/bdb.h"
#include "ezbee/app_signals.h"

#include "partition_utils.h"
#include "custom_themostat.h"

#define TAG "APP_MAIN"

#define NVS_PAGE_SIZE 0x1000

#define ALIGN_UP(addr, align) \
    (((addr) + (align) - 1) & ~((align) - 1))

#define NVS_ALIGNED(offset) \
    ALIGN_UP(offset, NVS_PAGE_SIZE)

#if !defined(ESP_PARTITION_TABLE_SIZE)
#define ESP_PARTITION_TABLE_SIZE 0x1000
#endif

#define GetSignalParams(signal, type) ((type *)ezb_app_signal_get_params(signal))

static const ezb_extaddr_t s_local_device_addr = {.u64 = 0xaaaaaaaaaaaaaaaa};

static void log_nwk_info(const char *status_string)
{
    ezb_extaddr_t extpanid;
    ezb_get_extended_panid(&extpanid);
    ESP_LOGI(TAG, "%s: PAN ID(0x%04hx, EXT: 0x%llx), Channel(%d), Short Address(0x%04hx)",
             status_string, ezb_get_panid(), extpanid.u64, ezb_get_current_channel(), ezb_get_short_address());
}

static bool esp_zigbee_app_signal_handler(const ezb_app_signal_t *app_signal)
{
    union {
        const ezb_bdb_signal_simple_params_t *bdb;
        const ezb_zdo_signal_leave_indication_params_t *leave_ind;
        const ezb_zdo_signal_device_annce_params_t *dev_annce;
        const ezb_zdo_signal_device_update_params_t *dev_upd;
        const ezb_zdo_signal_device_authorized_params_t *dev_auth;
        const ezb_zdo_signal_device_unavailable_params_t *dev_unavail;
        const ezb_nwk_signal_permit_join_status_params_t *permit_join;
        const ezb_nwk_signal_network_status_params_t *nwk_status;
        const void *param;
    } signal = { .param = ezb_app_signal_get_params(app_signal) };
    ezb_app_signal_type_t signal_type = ezb_app_signal_get_type(app_signal);

    switch (signal_type) {
    case EZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Initialize Zigbee stack");
        ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_INITIALIZATION);
        break;
    case EZB_BDB_SIGNAL_DEVICE_FIRST_START:
        ESP_LOGI(TAG, "Device first start");
        /* fallthrough*/
    case EZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (signal.bdb->status == EZB_BDB_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Device started up in%s factory-reset mode", ezb_bdb_is_factory_new() ? "" : " non");
            if (ezb_bdb_is_factory_new()) {
                ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_FORMATION);
            } else {
                ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_STEERING);
                log_nwk_info("Device reboot successfully");
            }
        } else {
            ESP_LOGE(TAG, "%s failed with status(0x%02x), please retry", ezb_app_signal_to_string(signal_type), signal.bdb->status);
        }
        break;
    case EZB_BDB_SIGNAL_FORMATION:
        if (signal.bdb->status == EZB_BDB_STATUS_SUCCESS) {
            log_nwk_info("Formed network successfully");
            ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGE(TAG, "Failed to form network with status(0x%02x)", signal.bdb->status);
        }
        break;
    case EZB_BDB_SIGNAL_STEERING:
        if (signal.bdb->status == EZB_BDB_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Network steering completed");
        } else {
            ESP_LOGW(TAG, "Failed to steering network with status(0x%02x)", signal.bdb->status);
        }
        break;
    case EZB_ZDO_SIGNAL_DEVICE_ANNCE:
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", signal.dev_annce->short_addr);
        break;
    case EZB_ZDO_SIGNAL_LEAVE_INDICATION:
        ESP_LOGI(TAG, "Zigbee Node(0x%04hx) is leaving network", signal.leave_ind->short_addr);
        break;
    case EZB_NWK_SIGNAL_PERMIT_JOIN_STATUS:
        if (signal.permit_join->duration) {
            ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", ezb_nwk_get_panid(), signal.permit_join->duration);
        } else {
            ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", ezb_nwk_get_panid());
        }
        break;
    default:
        ESP_LOGI(TAG, "Zigbee APP Signal: %s(type: 0x%02x)", ezb_app_signal_to_string(signal_type), signal_type);
        break;
    }
    return true;
}

static esp_err_t esp_zigbee_setup_commissioning(void)
{
    ezb_set_extended_address(&s_local_device_addr);
    ezb_aps_secur_enable_distributed_security(false);
    ESP_ERROR_CHECK(ezb_bdb_set_primary_channel_set(ESP_ZIGBEE_PRIMARY_CHANNEL_MASK));
    ESP_ERROR_CHECK(ezb_bdb_set_secondary_channel_set(ESP_ZIGBEE_SECONDARY_CHANNEL_MASK));
    ESP_ERROR_CHECK(ezb_app_signal_add_handler(esp_zigbee_app_signal_handler));

    return ESP_OK;
}

static void esp_zigbee_stack_main_task(void *pvParameters)
{
    /* initialize Zigbee stack */
    esp_zigbee_config_t zb_config = ESP_ZIGBEE_DEFAULT_CONFIG();
    ESP_ERROR_CHECK(esp_zigbee_init(&zb_config));

    ESP_ERROR_CHECK(esp_zigbee_setup_commissioning());

    ESP_ERROR_CHECK(esp_zigbee_setup_zcl_model());

    ESP_ERROR_CHECK(esp_zigbee_start(false));

    esp_zigbee_launch_mainloop();

    esp_zigbee_deinit();

    ESP_LOGI(TAG, "Zigbee stack exited");

    vTaskDelete(NULL);
}

#if CONFIG_ZB_EXAMPLE_RUNTIME_NVS_PARTITION
static esp_err_t register_partition(esp_flash_t *flash_chip, size_t offset, size_t size,
                                    const char *label, esp_partition_type_t type,
                                    esp_partition_subtype_t subtype,
                                    const esp_partition_t **p_partition)
{
    if (flash_chip == NULL) {
        flash_chip = esp_flash_default_chip;
    }

    // If the partition table contains this partition, then use it, otherwise register it.
    *p_partition = esp_partition_find_first(type, subtype, label);
    if ((*p_partition) == NULL) {
        esp_err_t error = esp_partition_register_external(flash_chip, offset, size, label, type, subtype, p_partition);
        if (error != ESP_OK) {
            ESP_LOGE(TAG, "Failed to register %s partition (err=0x%x)", label, error);
            return error;
        }
    }
    ESP_LOGI(TAG, "Use <%s> partition (0x%08" PRIx32 ")", (*p_partition)->label, (*p_partition)->address);
    return ESP_OK;
}

static esp_err_t prepare_nvs_storage(const char *label, size_t size)
{
    esp_err_t ret = ESP_OK;

    uint32_t found_offset = 0;
    size_t found_size = 0;
    size_t required_size = size + NVS_PAGE_SIZE - 1; /* 4KB for alignment, required by NVS */

    ret = partition_utils_find_unallocated(NULL, required_size, ESP_PARTITION_TABLE_OFFSET + ESP_PARTITION_TABLE_SIZE,
                                           &found_offset, &found_size);
    ESP_GOTO_ON_ERROR(ret, exit, TAG, "Failed to find unallocated space");

    ESP_LOGI(TAG, "Found unallocated space at 0x%08lx, size 0x%08zx", found_offset, found_size);

    const esp_partition_t *p_partition = NULL;
    ret = register_partition(NULL, NVS_ALIGNED(found_offset), size, label, ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, &p_partition);
    ESP_GOTO_ON_ERROR(ret, exit, TAG, "Failed to register partition");

    ESP_GOTO_ON_ERROR(nvs_flash_init_partition(label), exit, TAG, "Failed to initialize NVS partition");

    ESP_LOGI(TAG, "NVS partition initialized, label: %s, address: 0x%08lx, size: 0x%08lx",
             label, p_partition->address, p_partition->size);

exit:
    return ret;
}
#endif

static esp_err_t migrate_nvram(void)
{
#define MARKER_NS  "APP"
#define MARKER_KEY "Marker"

    esp_err_t ret = ESP_OK;

    nvs_handle_t nvs_handle;
    uint8_t marker = 1;
    ESP_GOTO_ON_ERROR(nvs_open_from_partition(ESP_ZIGBEE_STORAGE_PARTITION_NAME, MARKER_NS,
                                              NVS_READWRITE, &nvs_handle),
                      exit, TAG, "Failed to open NVS partition");

    ret = nvs_get_u8(nvs_handle, MARKER_KEY, &marker);
    if (ret == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGI(TAG, "App marker not found, perform migration");
    } else {
        ESP_LOGI(TAG, "Find App marker: %s, skip migration", esp_err_to_name(ret));
        goto cleanup_nvs;
    }

    esp_zigbee_nvram_mig_config_t config = {
        .source_partition_name = ESP_ZIGBEE_STORAGE_V1_PART_NAME,
        .destination_partition_name = ESP_ZIGBEE_STORAGE_PARTITION_NAME,
        .ieee_addr = &s_local_device_addr,
    };

    ESP_LOGI(TAG, "Start migration: <%s> -> <%s>", config.source_partition_name, config.destination_partition_name);
    ret = esp_zigbee_nvram_migrate(&config);

    if (ret == ESP_OK) {
        ret = nvs_set_u8(nvs_handle, MARKER_KEY, marker);
    }
    if (ret == ESP_OK) {
        ret = nvs_commit(nvs_handle);
    }

cleanup_nvs:
    nvs_close(nvs_handle);

exit:
    return ret;
}

void app_main(void)
{
#if CONFIG_ZB_EXAMPLE_RUNTIME_NVS_PARTITION
    ESP_ERROR_CHECK(prepare_nvs_storage(ESP_ZIGBEE_STORAGE_PARTITION_NAME, ESP_ZIGBEE_STORAGE_PARTITION_SIZE));
#else
    ESP_ERROR_CHECK(nvs_flash_init());
#endif

    ESP_ERROR_CHECK(migrate_nvram());

    ESP_LOGI(TAG, "Start ESP Zigbee Stack");
    xTaskCreate(esp_zigbee_stack_main_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
