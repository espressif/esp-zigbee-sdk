#include "esp_zigbee_core.h"
#include "zcl_utility.h"

#define MAX_CHILDREN                      10                                    /* the max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE         false                                 /* enable the install code policy for security */
#define ENDPOINT_ID                       10                                    /* device endpoint */
#define ESP_ZB_PRIMARY_CHANNEL_MASK       (1l << 13)                            /* Zigbee primary channel mask use in the example */

// #define LOG_RESET_COLOR       LOG_ANSI_COLOR_RESET
// #define LOG_COLOR_E           LOG_ANSI_COLOR_REGULAR(LOG_ANSI_COLOR_RED)
// #define LOG_COLOR_W           LOG_ANSI_COLOR_REGULAR(LOG_ANSI_COLOR_YELLOW)
// #define LOG_COLOR_I           LOG_ANSI_COLOR_REGULAR(LOG_ANSI_COLOR_GREEN)
// #define LOG_COLOR_D           LOG_ANSI_COLOR_REGULAR(LOG_ANSI_COLOR_MAGENTA)
// #define LOG_COLOR_V           LOG_ANSI_COLOR_REGULAR(LOG_ANSI_COLOR_BLUE)

/* Zigbee configuration */
#define ESP_ZB_ZR_CONFIG()                                                          \
{                                                                                   \
    .esp_zb_role = ESP_ZB_DEVICE_TYPE_COORDINATOR,                                  \
    .install_code_policy = INSTALLCODE_POLICY_ENABLE,                               \
    .nwk_cfg.zczr_cfg = {                                                           \
        .max_children = MAX_CHILDREN,                                               \
    },                                                                              \
}

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                           \
{                                                               \
    .radio_mode = ZB_RADIO_MODE_NATIVE,                         \
}

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
{                                                               \
    .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,       \
}
