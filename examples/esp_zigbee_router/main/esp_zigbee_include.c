#include "esp_check.h"
#include "esp_log.h"
#include "nwk/esp_zigbee_nwk.h"
#include "aps/esp_zigbee_aps.h"
#include "esp_zigbee_core.h"
#include "zcl/esp_zigbee_zcl_common.h"
#include "switch_driver.h"

static const char *TAG_include = "esp_zigbee_include";

static bool zb_apsde_data_indication_handler(esp_zb_apsde_data_ind_t ind)
{
    bool processed = false;
    if (ind.status == 0x00) {
            if (ind.dst_endpoint == 10 && ind.profile_id == ESP_ZB_AF_HA_PROFILE_ID && ind.cluster_id == ESP_ZB_ZCL_CLUSTER_ID_BASIC) {
            ESP_LOGI("APSDE INDICATION",
                    "Received APSDE-DATA %s request with a length of %ld from endpoint %d, source address 0x%04hx to "
                    "endpoint %d, destination address 0x%04hx, rx_time %d, lqi %d, security status %s",
                    ind.dst_addr_mode == 0x01 ? "group" : "unicast", ind.asdu_length, ind.src_endpoint,
                    ind.src_short_addr, ind.dst_endpoint, ind.dst_short_addr, ind.rx_time, ind.lqi,
                    ind.security_status == 0 ? "unsecured network" : "secured network");
            //ESP_LOG_BUFFER_HEX_LEVEL("APSDE INDICATION", ind.asdu, ind.asdu_length, ESP_LOG_INFO);
            processed = true;
            
        }
    } else {
        ESP_LOGE("APSDE INDICATION", "Invalid status of APSDE-DATA indication, error code: %d", ind.status);
        processed = false;
    }
    return processed;
}

//wyświetla sąsiadów
static void esp_show_neighbor_table(){
    static const char *dev_type_name[] = {
        [ESP_ZB_DEVICE_TYPE_COORDINATOR] = "ZC",
        [ESP_ZB_DEVICE_TYPE_ROUTER]      = "ZR",
        [ESP_ZB_DEVICE_TYPE_ED]          = "ZED",
        [ESP_ZB_DEVICE_TYPE_NONE]        = "UNK",
    };
    static const char rel_name[] = {
        [ESP_ZB_NWK_RELATIONSHIP_PARENT]                = 'P',  /* Parent */
        [ESP_ZB_NWK_RELATIONSHIP_CHILD]                 = 'C',  /* Child */
        [ESP_ZB_NWK_RELATIONSHIP_SIBLING]               = 'S',  /* Sibling */
        [ESP_ZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE]     = 'O',  /* Others */
        [ESP_ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD]        = 'c', /* Previous Child */
        [ESP_ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD] = 'U', /* Unauthenticated Child */
    };
    esp_zb_nwk_info_iterator_t itor = ESP_ZB_NWK_INFO_ITERATOR_INIT;
    esp_zb_nwk_neighbor_info_t neighbor = {};

    ESP_LOGI(TAG_include,"ZigBee Network Neighbors:");
    while (ESP_OK == esp_zb_nwk_get_next_neighbor(&itor, &neighbor)) {
        ESP_LOGI(TAG_include,"Index: %3d", itor);
        ESP_LOGI(TAG_include,"  Age: %3d", neighbor.age);
        ESP_LOGI(TAG_include,"  Neighbor: 0x%04hx", neighbor.short_addr);
        ESP_LOGI(TAG_include,"  IEEE: 0x%016" PRIx64, *(uint64_t *)neighbor.ieee_addr);
        ESP_LOGI(TAG_include,"  Type: %3s", dev_type_name[neighbor.device_type]);   
        ESP_LOGI(TAG_include,"  Rel: %c", rel_name[neighbor.relationship]);
        ESP_LOGI(TAG_include,"  Depth: %3d", neighbor.depth);
        ESP_LOGI(TAG_include,"  LQI: %3d", neighbor.lqi);
        ESP_LOGI(TAG_include,"  Cost: o:%d", neighbor.outgoing_cost);

    }
    ESP_LOGI(TAG_include," ");
}

//wyswietla trasy
static void esp_show_route_table(){
    static const char *route_state_name[] = {
        [ESP_ZB_NWK_ROUTE_STATE_ACTIVE] = "Active",
        [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY] = "Disc",
        [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_FAILED] = "Fail",
        [ESP_ZB_NWK_ROUTE_STATE_INACTIVE] = "Inactive",
    };
    esp_zb_nwk_info_iterator_t itor = ESP_ZB_NWK_INFO_ITERATOR_INIT;
    esp_zb_nwk_route_info_t route = {};

    ESP_LOGI(TAG_include, "Zigbee Network Routes:");
    while (ESP_OK == esp_zb_nwk_get_next_route(&itor, &route)) {
        ESP_LOGI(TAG_include,"Index: %3d", itor);
        ESP_LOGI(TAG_include, "  DestAddr: 0x%04hx", route.dest_addr);
        ESP_LOGI(TAG_include, "  NextHop: 0x%04hx", route.next_hop_addr);
        ESP_LOGI(TAG_include, "  Expiry: %4d", route.expiry);
        ESP_LOGI(TAG_include, "  State: %6s", route_state_name[route.flags.status]);
        ESP_LOGI(TAG_include, "  Flags: 0x%02x", *(uint8_t *)&route.flags);
    }
    ESP_LOGI(TAG_include," ");

}
    //TODO trace
void esp_zigbee_include_show_tables(void) {
    ESP_LOGI(TAG_include, "Zigbee Network Tables:");
    esp_show_neighbor_table();
    esp_show_route_table();
}

static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};

void button_handler(switch_func_pair_t *button_func_pair)
{
    if(button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
        esp_zigbee_include_show_tables();
        esp_zb_bdb_open_network(30);
    }
    
}

static esp_err_t deferred_driver_init(void)
{
    uint8_t button_num = PAIR_SIZE(button_func_pair);

    bool is_initialized = switch_driver_init(button_func_pair, button_num, button_handler);
    return is_initialized ? ESP_OK : ESP_FAIL;
}