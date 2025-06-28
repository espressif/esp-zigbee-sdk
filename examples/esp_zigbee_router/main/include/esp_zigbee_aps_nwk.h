#include "zcl/esp_zigbee_zcl_common.h"
#include "nwk/esp_zigbee_nwk.h"
#include "aps/esp_zigbee_aps.h"
#include "esp_zigbee_core.h"

static bool deferred_driver_init(void);
static bool zb_apsde_data_indication_handler(esp_zb_apsde_data_ind_t ind);
void esp_zigbee_include_show_tables(void);


static const char rel_name[] = {
        [ESP_ZB_NWK_RELATIONSHIP_PARENT]                = 'P', /* Parent */
        [ESP_ZB_NWK_RELATIONSHIP_CHILD]                 = 'C', /* Child */
        [ESP_ZB_NWK_RELATIONSHIP_SIBLING]               = 'S', /* Sibling */
        [ESP_ZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE]     = 'O', /* Others */
        [ESP_ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD]        = 'c', /* Previous Child */
        [ESP_ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD] = 'u', /* Unauthenticated Child */
    };


static const char *dev_type_name[] = {
     [ESP_ZB_DEVICE_TYPE_COORDINATOR] = "ZC",
     [ESP_ZB_DEVICE_TYPE_ROUTER]      = "ZR",
     [ESP_ZB_DEVICE_TYPE_ED]          = "ZED",
     [ESP_ZB_DEVICE_TYPE_NONE]        = "UNK",
 };

static const char *route_state_name[] = {
    [ESP_ZB_NWK_ROUTE_STATE_ACTIVE] = "Active",
    [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY] = "Disc",
    [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_FAILED] = "Fail",
    [ESP_ZB_NWK_ROUTE_STATE_INACTIVE] = "Inactive",
};


// static const char *write_attr_status_name[] = {
//     [ESP_ZB_ZCL_STATUS_SUCCESS] = "Success",
//     [ESP_ZB_ZCL_STATUS_FAILURE] = "Failure",
//     [ESP_ZB_ZCL_STATUS_NOT_AUTHORIZED] = "Not Authorized",
//     [ESP_ZB_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE] = "Unsupported Attribute",
//     [ESP_ZB_ZCL_STATUS_INVALID_VALUE] = "Invalid Value",
//     [ESP_ZB_ZCL_STATUS_INSUFFICIENT_SPACE] = "Insufficient Space",
//     [ESP_ZB_ZCL_STATUS_NOT_FOUND] = "Not Found",
// };


