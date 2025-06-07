#include "esp_check.h"
#include "esp_log.h"
#include "nwk/esp_zigbee_nwk.h"
#include "switch_driver.h"
#include "switch_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_zigbee_core.h"
#include "aps/esp_zigbee_aps.h"

static const char *TAG_include = "esp_zigbee_include";

//wyświetla sąsiadów
static void esp_show_neighbor_table(){
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

    ESP_LOGI(TAG_include,"Network Neighbors:");
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

        ESP_LOGI(TAG_include," ");
    }
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
        ESP_LOGI(TAG_include," ");
    }
}

void esp_zigbee_include_show_tables(void) {
    ESP_LOGI(TAG_include, "Zigbee Network Tables:");
    esp_show_neighbor_table();
    esp_show_route_table();
}

static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};


static QueueHandle_t s_aps_data_confirm = NULL;
static QueueHandle_t s_aps_data_indication = NULL;
typedef struct payload_data_s {
    uint8_t *data;
    uint16_t data_length;

} payload_data_t;

static esp_err_t esp_zb_aps_data_request(esp_zb_apsde_data_req_t *req){
    if (req == NULL || req->asdu_length == 0 || req->asdu == NULL) {
        ESP_LOGE(TAG_include, "Invalid APS data request");
        return ESP_ERR_INVALID_ARG;
    }

    esp_zb_apsde_data_confirm_t confirm = {0};
    confirm.status = 0; 
    confirm.dst_addr_mode = req->dst_addr_mode;
    confirm.dst_addr = req->dst_addr;
    confirm.dst_endpoint = req->dst_endpoint;
    confirm.src_endpoint = req->src_endpoint;
    confirm.asdu_length = req->asdu_length;
    confirm.asdu = req->asdu;

    if (!esp_zb_aps_data_confirm_handler(confirm)) {
        ESP_LOGE(TAG_include, "Failed to handle APS data confirm");
        return ESP_FAIL;
    }

    return ESP_OK;
}

static bool esp_zb_aps_data_confirm_handler(esp_zb_apsde_data_confirm_t confirm)
{
    if (confirm.status != 0) {
        return false;
    }

    uint16_t outlen = sizeof(esp_zb_apsde_data_confirm_t) + confirm.asdu_length;

    if (s_aps_data_confirm == NULL) {
        s_aps_data_confirm = xQueueCreate(10, outlen);
    }

    if (s_aps_data_confirm != NULL) {
        xQueueSend(s_aps_data_confirm, &confirm, portMAX_DELAY);
        return true;
    }
    return false;
}




void create_network_load(uint16_t dest_addr)
{
    esp_zb_apsde_data_req_t req ={
        .dst_addr_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
        .dst_addr.addr_short = dest_addr,
        .dst_endpoint = 1, // Example endpoint
        .profile_id = 0x0104, // Example profile ID
        .cluster_id = 0x0006, // Example cluster ID (On/Off cluster)
        .src_endpoint = 1, // Example source endpoint
        .asdu_length = 10, // Example payload length
        .asdu = (uint8_t *)malloc(10), // Allocate memory for payload
        .tx_options = 0, // Example transmission options
        .use_alias = false,
        .alias_src_addr = 0,
        .alias_seq_num = 0,
        .radius = 30 // Example radius
    };

    uint32_t i=0;
    while(i<100){

    }

}




void button_handler(switch_func_pair_t *button_func_pair)
{
    if(button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
        esp_zigbee_include_show_tables();
        create_network_load();

    }
    
}

static esp_err_t deferred_driver_init(void)
{
    uint8_t button_num = PAIR_SIZE(button_func_pair);

    bool is_initialized = switch_driver_init(button_func_pair, button_num, button_handler);
    return is_initialized ? ESP_OK : ESP_FAIL;
}


