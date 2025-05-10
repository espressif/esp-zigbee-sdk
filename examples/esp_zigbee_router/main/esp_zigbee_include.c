#include "esp_check.h"
#include "esp_log.h"
#include "nwk\esp_zigbee_nwk.h"

static const char *TAG_include = "esp_zigbee_include";

static void esp_show_neighbor_table(){
    static const char *titles[] = {"Index", "Age", "NwkAddr", "MacAddr", "Type", "Rel", "Depth", "LQI", "Cost"};
    static const uint8_t widths[] = {5, 5, 8, 20, 5, 3, 5, 5, 6};
    static const char *dev_type_name[] = {
        [ESP_ZB_DEVICE_TYPE_COORDINATOR] = "ZC",
        [ESP_ZB_DEVICE_TYPE_ROUTER]      = "ZR",
        [ESP_ZB_DEVICE_TYPE_ED]          = "ZED",
        [ESP_ZB_DEVICE_TYPE_NONE]        = "UNK",
    };
    static const char rel_name[] = {
        [ESP_ZB_NWK_RELATIONSHIP_PARENT]                = 'P', /* Parent */
        [ESP_ZB_NWK_RELATIONSHIP_CHILD]                 = 'C', /* Child */
        [ESP_ZB_NWK_RELATIONSHIP_SIBLING]               = 'S', /* Sibling */
        [ESP_ZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE]     = 'O', /* Others */
        [ESP_ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD]        = 'c', /* Previous Child */
        [ESP_ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD] = 'u', /* Unauthenticated Child */
    };
    esp_zb_nwk_info_iterator_t itor = ESP_ZB_NWK_INFO_ITERATOR_INIT;
    esp_zb_nwk_neighbor_info_t neighbor = {};

    ESP_LOGI(TAG_include,"nwk");
    while (ESP_OK == esp_zb_nwk_get_next_neighbor(&itor, &neighbor)) {
        ESP_LOGI(TAG_include,"| %3d | %3d | 0x%04hx | 0x%016" PRIx64 " |  %3s | %c | %3d | %3d |  o:%d |",
                    itor, neighbor.age, neighbor.short_addr, *(uint64_t *)neighbor.ieee_addr,
                    dev_type_name[neighbor.device_type], rel_name[neighbor.relationship],
                    neighbor.depth, neighbor.lqi, neighbor.outgoing_cost);
        ESP_LOGI(TAG_include," ");
    }
}

static void esp_show_route_table(){
    // static const char *titles[] = {"Index", "Age", "NwkAddr", "MacAddr", "Type", "Rel", "Depth", "LQI", "Cost"};
    // static const uint8_t widths[] = {5, 5, 8, 20, 5, 3, 5, 5, 6};
    static const char *route_state_name[] = {
        [ESP_ZB_NWK_ROUTE_STATE_ACTIVE] = "Active",
        [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY] = "Disc",
        [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_FAILED] = "Fail",
        [ESP_ZB_NWK_ROUTE_STATE_INACTIVE] = "Inactive",
    };
    esp_zb_nwk_info_iterator_t itor = ESP_ZB_NWK_INFO_ITERATOR_INIT;
    esp_zb_nwk_route_info_t route = {};

    ESP_LOGI(TAG_include,"routes:");
    while (ESP_OK == esp_zb_nwk_get_next_route(&itor, &route)) {
        ESP_LOGI(TAG_include,"| %3d | 0x%04hx%c| 0x%04hx | %4d | %6s | 0x%02x |",
        itor, route.dest_addr, route.flags.group_id ? 'g' : ' ', route.next_hop_addr,
        route.expiry, route_state_name[route.flags.status], *(uint8_t *)&route.flags);
    }
}

typedef enum{
    ADD,
    MINUS
}custom_zb_action_handler_callback_id_t;