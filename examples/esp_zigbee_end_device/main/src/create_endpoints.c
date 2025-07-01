#include "create_endpoints.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_zigbee_type.h"


static void create_test_endpoint(esp_zb_ep_list_t *ep_list, esp_zb_attribute_list_t *basic_cluster, esp_zb_cluster_list_t *cluster_list)
{
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = 10,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_TEST_DEVICE_ID,
        .app_device_version = 0,
    };

    /* Added attributes */
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)ESP_MANUFACTURER_NAME));
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)ESP_MODEL_IDENTIFIER));
    /* Added clusters */
    /* Added endpoints */
    ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
}

void create_traffic_manager_endpoint(esp_zb_ep_list_t *ep_list, esp_zb_attribute_list_t *basic_cluster, esp_zb_cluster_list_t *cluster_list)
{
    char *esp_manufacturer_name = "\x09""ESPRESSIF";
    char *esp_model_identifier = "esp-c6";
    
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = 70,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = 40,
        .app_device_version = 0,
    };

    

    /* Added attributes */
    // ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID,(void *) ESP_MANUFACTURER_NAME));
    // ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *) ESP_MODEL_IDENTIFIER));
    /* Added clusters */
    /* Added endpoints */
    ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
    /* Register device */

}
