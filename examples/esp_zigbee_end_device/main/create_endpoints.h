#include "esp_zigbee_type.h"
#include "esp_zigbee_core.h"

/* Basic manufacturer information */
#define ESP_MANUFACTURER_NAME "\x09""ESPRESSIF"      /* Customized manufacturer name */
#define ESP_MODEL_IDENTIFIER "\x07"CONFIG_IDF_TARGET /* Customized model identifier */


static void create_test_endpoint(esp_zb_ep_list_t *ep_list);


