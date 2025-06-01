#include "create_endpoints.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_zigbee_type.h"


static void create_test_endpoint(esp_zb_ep_list_t *ep_list)
{
    char *esp_manufacturer_name = "ESPRESSIF";
    char *esp_model_identifier = "esp-c6";
    
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = 10,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_TEST_DEVICE_ID,
        .app_device_version = 0,
    };

    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(NULL);

    /* Added attributes */
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID,(void *) esp_manufacturer_name));
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *) esp_model_identifier));
    /* Added clusters */
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
    /* Added endpoints */
    ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
    /* Register device */

}
