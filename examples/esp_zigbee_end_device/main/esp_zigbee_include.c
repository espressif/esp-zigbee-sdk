#include "esp_check.h"
#include "esp_log.h"
#include "nwk/esp_zigbee_nwk.h"
#include "switch_driver.h"
#include "switch_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_zigbee_core.h"

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

typedef enum{
    ESP_LOAD_ZB_DATA_CONFIRM = 0x01,
    ESP_LOAD_ZB_DATA_INDICATION = 0x02,
} esp_load_zb_data_type_t;
typedef struct {
    uint16_t id;        /*!< ID of the APS data */
    uint16_t size;      /*!< Size of the APS data */
    void *data;         /*!< Pointer to the APS data */
} esp_load_zb_ctx_t;

void esp_load_zb_aps_data_handle(uint16_t id, const void *buffer, uint16_t length)
{
    QueueHandle_t event_queue = (id == ESP_LOAD_ZB_DATA_CONFIRM) ? s_aps_data_confirm : s_aps_data_indication;
    if (event_queue) {
        BaseType_t ret = 0;
        esp_load_zb_ctx_t ncp_ctx = {
            .id = id,
            .size = length,
        };

        if (buffer) {
            ncp_ctx.data = calloc(1, length);
            memcpy(ncp_ctx.data, buffer, length);
        }

        if (xPortInIsrContext() == pdTRUE) {
            ret = xQueueSendFromISR(event_queue, &ncp_ctx, NULL);
        } else {
            ret = xQueueSend(event_queue, &ncp_ctx, 0);
        }
        return (ret == pdTRUE) ? ESP_OK : ESP_FAIL ;
    } else {
        esp_ncp_header_t ncp_header = {
            .sn = esp_random() % 0xFF,
            .id = id,
        };
        return 0;
    }
}


void create_network_load(void)
{

    int i=0;
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


