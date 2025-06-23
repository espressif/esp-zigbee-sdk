#include "esp_check.h"
#include "esp_log.h"
#include "nwk/esp_zigbee_nwk.h"
#include "switch_driver.h"
#include "switch_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_zigbee_core.h"
#include "esp_zigbee_include.h"
#include "aps/esp_zigbee_aps.h"
#include <memory.h>

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



void esp_zb_aps_data_confirm_handler(esp_zb_apsde_data_confirm_t confirm)
{
     if (confirm.status == 0x00) {
        ESP_LOGI("APSDE CONFIRM",
                "Sent successfully from endpoint %d, source address 0x%04hx to endpoint %d,"
                "destination address 0x%04hx",
                confirm.src_endpoint, esp_zb_get_short_address(), confirm.dst_endpoint, confirm.dst_addr.addr_short);
        ESP_LOG_BUFFER_CHAR_LEVEL("APSDE CONFIRM", confirm.asdu, confirm.asdu_length, ESP_LOG_INFO);
        
    } else {
        ESP_LOGE("APSDE CONFIRM", "Failed to send APSDE-DATA request, error code: %d", confirm.status);
    }
}


void create_network_load(uint16_t dest_addr)
{
    uint32_t data_length = 50;


    esp_zb_apsde_data_req_t req ={
        .dst_addr_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
        .dst_addr.addr_short = dest_addr,
        .dst_endpoint = 10,                          // Example endpoint
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,      // Example profile ID
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_BASIC,  // Example cluster ID (On/Off cluster)
        .src_endpoint = 10,                          // Example source endpoint
        .asdu_length = data_length,                 // Example payload length
        .asdu = malloc(data_length * sizeof(uint8_t)), // Allocate memory for ASDU if needed
        .tx_options = 0,                            // Example transmission options
        .use_alias = false,
        .alias_src_addr = 0,
        .alias_seq_num = 0,
        .radius = 1,                                 // Example radius
    };


    
    uint8_t i=0;

    if (req.asdu == NULL) {
        ESP_LOGE(TAG_include, "Failed to allocate memory for ASDU");
        return;
    }else{
        while (i < data_length) {
            req.asdu[i] = i % 256; // Fill with some data, e.g., incrementing values
            i++;
        }
    }
    ESP_LOGI(TAG_include, "Sending APS data request to 0x%04hx with %ld bytes", dest_addr, data_length);
    esp_zb_lock_acquire(portMAX_DELAY);
    esp_zb_aps_data_request(&req);
    esp_zb_lock_release();
    vTaskDelay(pdMS_TO_TICKS(100)); // Delay to avoid flooding the network
    

}

void create_network_load_64bit(uint64_t dest_addr)
{//TODO: modify to use 64-bit address
    uint32_t data_length = 50;
    esp_zb_ieee_addr_t ieee_addr ;
    memcpy(ieee_addr, &dest_addr, sizeof(esp_zb_ieee_addr_t)); // Copy the 64-bit address into the ieee_addr variable
    // ESP_LOGI(TAG_include, "Sending APS data request to 0x%02hx:0x%02hx:0x%02hx:0x%02hx:0x%02hx:0x%02hx:0x%02hx:0x%02hx with %ld bytes",
    //                          ieee_addr[0], ieee_addr[1], ieee_addr[2], ieee_addr[3], ieee_addr[4], ieee_addr[5], ieee_addr[6], ieee_addr[7], data_length);
    //                          return;
    esp_zb_apsde_data_req_t req = {
        .dst_addr_mode = ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT,
        //Destination address is assingned under strycture definition
        .dst_endpoint = 10,                                 // Example endpoint
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,              // Example profile ID
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_BASIC,          // Example cluster ID (On/Off cluster)
        .src_endpoint = 10,                                 // Example source endpoint
        .asdu_length = data_length,                         // Example payload length
        .asdu = malloc(data_length * sizeof(uint8_t)),      // Allocate memory for ASDU if needed
        .tx_options = 0,                                    // Example transmission options
        .use_alias = false,
        .alias_src_addr = 0,
        .alias_seq_num = 0,
        .radius = 3,                                        // Example radius
    };
    memcpy(req.dst_addr.addr_long, ieee_addr, sizeof(esp_zb_ieee_addr_t)); // Copy the 64-bit address

    
    uint8_t i=0;

    if (req.asdu == NULL) {
        ESP_LOGE(TAG_include, "Failed to allocate memory for ASDU");
        return;
    }else{
        ESP_LOGD(TAG_include, "Filling ASDU with data");
        while (i < data_length) {
            req.asdu[i] = (i+0xf) % 256; 
            i++;
        }
    }
    ESP_LOGI(TAG_include, "Sending APS data request to 0x%016" PRIx64 " %ld bytes" ,
                            dest_addr, data_length);
    esp_zb_lock_acquire(portMAX_DELAY);
    esp_zb_aps_data_request(&req);
    esp_zb_lock_release();
    vTaskDelay(pdMS_TO_TICKS(500)); // Delay to avoid flooding the network
    

}


void button_handler(switch_func_pair_t *button_func_pair)
{
    if(button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
        esp_zigbee_include_show_tables();
        // create_network_load(0x0000);
        // esp_zb_ieee_addr_t router1_address = {0x40, 0x4c, 0xca, 0xff, 0xfe, 0x5f, 0xae, 0x8c};
        create_network_load_64bit(0x404ccafffe5fae8c);
        //esp_zb_ieee_addr_t router2_address = {0x40, 0x4c, 0xca, 0xff, 0xfe, 0x5f, 0xae, 0x8c};
        create_network_load_64bit(0x404ccafffe5f964c);
    }
}

static esp_err_t deferred_driver_init(void)
{
    uint8_t button_num = PAIR_SIZE(button_func_pair);

    bool is_initialized = switch_driver_init(button_func_pair, button_num, button_handler);
    return is_initialized ? ESP_OK : ESP_FAIL;
}


static bool zb_apsde_data_indication_handler(esp_zb_apsde_data_ind_t ind)
{
    bool processed = false;
    if (ind.status == 0x00) {
        if (ind.dst_endpoint == 27 && ind.profile_id == ESP_ZB_AF_HA_PROFILE_ID && ind.cluster_id == ESP_ZB_ZCL_CLUSTER_ID_BASIC) {
            // ESP_LOGD("APSDE INDICATION",
            //         "Received data from endpoint %d, source address 0x%04hx to endpoint %d, destination address 0x%04hx",
            //         ind.src_endpoint, ind.src_short_addr, ind.dst_endpoint, ind.dst_short_addr);    
            create_network_load(ind.src_short_addr); // Respond to the received data
        }
    } else {
        ESP_LOGE("APSDE INDICATION", "Invalid status of APSDE-DATA indication, error code: %d", ind.status);
        processed = false;
    }
    return processed;
}