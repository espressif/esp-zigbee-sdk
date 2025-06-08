#include "esp_zigbee_core.h"
#include "zcl_utility.h"
#include "create_endpoints.c"

#define MAX_CHILDREN                      10                                    /* the max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE         false                                 /* enable the install code policy for security */
#define ED_ID                             10                                    /* esp light switch device endpoint */
#define ESP_ZB_PRIMARY_CHANNEL_MASK       ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK  /* Zigbee primary channel mask use in the example */


#define ESP_ZB_ZR_CONFIG()                                                              \
{                                                                                       \
    .esp_zb_role = ESP_ZB_DEVICE_TYPE_ED,                                               \
    .install_code_policy = INSTALLCODE_POLICY_ENABLE,                                   \
    .nwk_cfg.zed_cfg = {                                                                \
        .ed_timeout = 70,                                                               \
        .keep_alive = 600000,                                                       \
    },                                                                                  \
}

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                           \
{                                                               \
    .radio_mode = ZB_RADIO_MODE_NATIVE,                         \
}

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
{                                                               \
    .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,       \
}
/* Zigbee configuration */