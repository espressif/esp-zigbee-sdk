/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/core_types.h>

#include <ezbee/zcl/zcl_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EZB_AF_ENDPOINT_BROADCAST_ID 0xFFU /*!< Zigbee broadcast endpoint value. */

#define EZB_INVALID_DESC NULL /*!< Invalid descriptor. */

/**
 * @brief Enumeration of Zigbee application profile IDs.
 * @anchor ezb_af_profile_id_e
 */
enum ezb_af_profile_id_e {
    EZB_AF_ZDP_PROFILE_ID = 0x0000U, /*!< ZDO profile ID */
    EZB_AF_HA_PROFILE_ID  = 0x0104U, /*!< HA profile ID */
    EZB_AF_SE_PROFILE_ID  = 0x0109U, /*!< SE profile ID */
    EZB_AF_TL_PROFILE_ID  = 0xC05EU, /*!< Touchlink profile ID */
    EZB_AF_GP_PROFILE_ID  = 0xA1E0U, /*!< GreenPower profile ID */
};

/**
 * @brief Represents the application profile ID. See @ref ezb_af_profile_id_e.
 * @anchor ezb_af_profile_id_t
 */
typedef uint16_t ezb_af_profile_id_t;

/**
 * @brief Values of the current power mode of the node power descriptor
 * @anchor ezb_af_node_power_mode_t
 */
typedef enum {
    EZB_AF_NODE_POWER_MODE_SYNC_ON_WHEN_IDLE = 0U,    /*!< Receiver synchronized with the receiver on when idle subfield of the
                                                           node descriptor */
    EZB_AF_NODE_POWER_MODE_COME_ON_PERIODICALLY = 1U, /*!< Receiver comes on periodically as defined by the node
                                                           power descriptor */
    EZB_AF_NODE_POWER_MODE_COME_ON_WHEN_SIMULATED = 2U, /*!< Receiver comes on when stimulated, for example, by a user pressing
                                                             a button */
} ezb_af_node_power_mode_t;

/**
 * @brief Values of the power sources of the node power descriptor
 * @anchor ezb_af_node_power_source_t
 */
typedef enum {
    EZB_AF_NODE_POWER_SOURCE_CONSTANT_POWER       = 1U, /*!< Constant (mains) power */
    EZB_AF_NODE_POWER_SOURCE_RECHARGEABLE_BATTERY = 2U, /*!< Rechargeable battery */
    EZB_AF_NODE_POWER_SOURCE_DISPOSABLE_BATTERY   = 4U, /*!< Disposable battery */
} ezb_af_node_power_source_t;

/**
 * @brief Values of the current power source level of the node power descriptor
 * @anchor ezb_af_node_power_source_level_t
 */
typedef enum {
    EZB_AF_NODE_POWER_SOURCE_LEVEL_CRITICAL    = 0U,  /*!< Charge Level: Critical */
    EZB_AF_NODE_POWER_SOURCE_LEVEL_33_PERCENT  = 4U,  /*!< Charge Level: 33% */
    EZB_AF_NODE_POWER_SOURCE_LEVEL_66_PERCENT  = 8U,  /*!< Charge Level: 66% */
    EZB_AF_NODE_POWER_SOURCE_LEVEL_100_PERCENT = 12U, /*!< Charge Level: 100% */
} ezb_af_node_power_source_level_t;

/**
 * @brief Enumeration of server mask for AF Node Descriptor
 */
enum ezb_af_server_mask_s {
    EZB_AF_SERVER_MASK_PRIMARY_TC = 0x0001U, /*!< Bit 0, Primary Trust Center */
    EZB_AF_SERVER_MASK_BACKUP_TC  = 0x0002U, /*!< Bit 1, Backup Trust Center */
    EZB_AF_SERVER_MASK_DEPRECATED = 0x003CU, /*!< Bit 2..5, Deprecated */
    EZB_AF_SERVER_MASK_NWK_MGR    = 0x0040U, /*!< Bit 6, Network Manager */
    EZB_AF_SERVER_MASK_RESERVED   = 0x0180U, /*!< Bit 7..8, Reserved */
    EZB_AF_SERVER_MASK_STACK_REV  = 0xFE00U, /*!< Bit 9..15, Stack Revision */
};

/**
 * @brief Server mask of Application Framework
 * @anchor ezb_af_server_mask_t
 */
typedef uint16_t ezb_af_server_mask_t;

/**
 * @brief Structure to define Zigbee AF Node Power Descriptor.
 */
union ezb_af_node_power_desc_u {
    struct {
        uint8_t current_power_mode : 4;         /*!< Current power mode, see @ref ezb_af_node_power_mode_t */
        uint8_t available_power_sources : 4;    /*!< Available power sources, see @ref ezb_af_node_power_source_t */
        uint8_t current_power_source : 4;       /*!< Current power source, see @ref ezb_af_node_power_source_t */
        uint8_t current_power_source_level : 4; /*!< Current power source level, see @ref ezb_af_node_power_source_level_t */
    } EZB_PACKED_FIELD;
    uint16_t u16; /*!< The raw data of the node power descriptor. */
};

/**
 * @brief Represents the node power descriptor. See @ref ezb_af_node_power_desc_u.
 * @anchor ezb_af_node_power_desc_t
 */
typedef union ezb_af_node_power_desc_u ezb_af_node_power_desc_t;

/**
 * @brief Structure to define Zigbee AF Simple Descriptor.
 */
typedef struct ezb_af_simple_desc_s {
    uint8_t   ep_id;                    /*!< Endpoint identifier. */
    uint16_t  app_profile_id;           /*!< Application profile identifier. */
    uint16_t  app_device_id;            /*!< Application device identifier. */
    uint8_t   app_device_version : 4;   /*!< Application device version. */
    uint8_t   reserved : 4;             /*!< Reserved bits. */
    uint8_t   app_input_cluster_count;  /*!< Number of input clusters. */
    uint8_t   app_output_cluster_count; /*!< Number of output clusters. */
    uint16_t *app_cluster_list;         /*!< Pointer to an array of uint16_t cluster IDs whose total length is
                                             (app_input_cluster_count + app_output_cluster_count).
                                             Input cluster IDs start from index 0.
                                             Output cluster IDs start from index app_input_cluster_count. */
} ezb_af_simple_desc_t;

/**
 * @brief Structure to define Zigbee AF Node Descriptor.
 */
typedef struct ezb_af_node_desc_s {
    uint16_t node_flags;                 /*!< Node flags */
    uint8_t  mac_capability_flags;       /*!< MAC capability flags */
    uint16_t manufacturer_code;          /*!< Manufacturer code */
    uint8_t  max_buf_size;               /*!< Maximum buffer size */
    uint16_t max_incoming_transfer_size; /*!< Maximum incoming transfer size */
    uint16_t server_mask;                /*!< Server mask */
    uint16_t max_outgoing_transfer_size; /*!< Maximum outgoing transfer size */
    uint8_t  desc_capability_field;      /*!< Descriptor capability field */
} ezb_af_node_desc_t;

/**
 * @brief Zigbee endpoint descriptor.
 * @anchor ezb_af_ep_desc_t
 */
typedef void *ezb_af_ep_desc_t;

/**
 * @brief Invalid endpoint descriptor.
 */
#define EZB_INVALID_AF_EP_DESC EZB_INVALID_DESC

/**
 * @brief Zigbee device descriptor.
 * @anchor ezb_af_device_desc_t
 */
typedef void *ezb_af_device_desc_t;

/**
 * @brief Invalid device descriptor.
 */
#define EZB_INVALID_AF_DEVICE_DESC EZB_INVALID_DESC

/**
 * @brief Linked list node for Zigbee endpoint list (opaque type).
 *
 * This type represents a list of endpoints associated with a device.
 */
typedef void *ezb_af_ep_list_t;

/**
 * @brief Invalid endpoint list.
 */
#define EZB_INVALID_ZCL_EP_LIST EZB_INVALID_DESC

/** @brief Endpoint identifier. */
typedef uint8_t ezb_af_ep_id_t;

/**
 * @brief A callback for getting the default attribute value from application
 *
 * @param[in] ep_id  The identifier of the endpoint to which the attribute belongs.
 * @param[in] cluster_id The identifier of the cluster to which the attribute belongs.
 * @param[in] cluster_role The role of the cluster to which the attribute belongs.
 * @param[in] attr_id The identifier of the attribute to which the @p attr_value should be reset.
 * @param[out] attr_value The default value that will be set to the attribute after reset.
 */
typedef void (*ezb_af_endpoint_get_default_attr_value_callback_t)(uint8_t  ep_id,
                                                                  uint16_t cluster_id,
                                                                  uint8_t  cluster_role,
                                                                  uint16_t attr_id,
                                                                  void    *attr_value);

/**
 * @brief Structure for Zigbee endpoint configuration.
 */
typedef struct ezb_af_ep_config_s {
    uint8_t  ep_id;                  /*!< Identifier of the endpoint. */
    uint16_t app_profile_id;         /*!< Identifier of the application profile. */
    uint16_t app_device_id;          /*!< Identifier of the application device. */
    uint8_t  app_device_version : 4; /*!< Version of the application device. */
    uint8_t  reserved : 4;           /*!< Reserved bits. */
} ezb_af_ep_config_t;

/**
 * @brief User data confirmation structure for Zigbee AF requests.
 *
 * This confirm does not distinguish between profiles. Users should select the appropriate confirm structure based on the
 * specific profile ID, rather than using it directly in application.
 */
typedef struct ezb_af_user_cnf_s {
    uint8_t       status;     /*!< Status of the AF data request. */
    uint8_t       tsn;        /*!< Transaction sequence number. */
    ezb_address_t dst_addr;   /*!< Address of the destination device. */
    uint8_t       src_ep;     /*!< Identifier of the source endpoint. */
    uint8_t       dst_ep;     /*!< Identifier of the destination endpoint. */
    uint16_t      cluster_id; /*!< Identifier of the cluster to which the data request belongs. */
    uint16_t      profile_id; /*!< Identifier of the application profile to which the data request belongs. */
} ezb_af_user_cnf_t;

/**
 * @brief A callback type for Zigbee AF user data confirmation.
 * @anchor ezb_af_user_cnf_callback_t
 */
typedef void (*ezb_af_user_cnf_callback_t)(ezb_af_user_cnf_t *cnf, void *user_ctx);

/**
 * @brief Context for AF user data confirm.
 */
typedef struct ezb_af_user_cnf_ctx_s {
    ezb_af_user_cnf_callback_t cb;       /*!< User callback for AF user data confirmation. See @ref ezb_af_user_cnf_callback_t */
    void                      *user_ctx; /*!< User argument of request will be passed to user callback. */
} ezb_af_user_cnf_ctx_t;

/**
 * @brief Set the manufacturer code of the node descriptor.
 *
 * @param[in] manuf_code Manufacturer code to set.
 */
void ezb_af_node_desc_set_manuf_code(uint16_t manuf_code);

/**
 * @brief Get the node descriptor of the Zigbee device.
 *
 * @return The pointer to the node descriptor structure. See @ref ezb_af_node_desc_s
 */
const ezb_af_node_desc_t *ezb_af_get_node_desc(void);

/**
 * @brief Set the node power descriptor of the Zigbee device.
 *
 * @param[in] desc The pointer to the node power descriptor structure. See @ref ezb_af_node_power_desc_t
 *
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_set_node_power_desc(const ezb_af_node_power_desc_t *desc);

/**
 * @brief Get the node power descriptor of the Zigbee device.
 *
 * @return The pointer to the node power descriptor structure. See @ref ezb_af_node_power_desc_t
 */
const ezb_af_node_power_desc_t *ezb_af_get_node_power_desc(void);

/**
 * @brief Get the simple descriptor for a specific endpoint.
 *
 * @param[in] ep_id  The identifier of the endpoint to get the simple descriptor for.
 *
 * @return The pointer to the simple descriptor structure. See @ref ezb_af_simple_desc_s, or NULL if not found
 */
const ezb_af_simple_desc_t *ezb_af_get_simple_desc(uint8_t ep_id);

/**
 * @brief Get the next simple descriptor in the iteration.
 *
 * @note This function iterates through the simple descriptors and returns the next simple descriptor in the iteration.
 *       If the @p simple_desc is NULL, it returns the first simple descriptor in the iteration.
 *
 * @param[in] simple_desc The pointer to the simple descriptor used to retrieve the next simple descriptor.
 *
 * @return The pointer to the next simple descriptor structure. See @ref ezb_af_simple_desc_s, or NULL if no more descriptors
 */
const ezb_af_simple_desc_t *ezb_af_get_next_simple_desc(const ezb_af_simple_desc_t *simple_desc);

/**
 * @brief Set the maximum number of endpoints for the device.
 *
 * @param[in] num The maximum number of endpoints to set.
 *
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_dev_set_max_endpoint_num(uint8_t num);

/**
 * @brief Get the maximum number of endpoints for the device.
 *
 * @return The maximum number of endpoints.
 */
uint8_t ezb_af_dev_get_max_endpoint_num(void);

/**
 * @brief Create a new Zigbee device descriptor.
 *
 * This function allocates and initializes a new device descriptor structure,
 * which can be used to manage endpoints and context for a Zigbee device.
 *
 * @return The newly created device descriptor, or EZB_INVALID_AF_DEVICE_DESC on failure.
 */
ezb_af_device_desc_t ezb_af_create_device_desc(void);

/**
 * @brief Free a Zigbee device descriptor.
 *
 * This function frees the memory allocated for a device descriptor.
 *
 * @param[in] dev_desc The device descriptor to free.
 */
void ezb_af_free_device_desc(ezb_af_device_desc_t dev_desc);

/**
 * @brief Add an endpoint descriptor to a Zigbee device descriptor.
 *
 * This function links an endpoint descriptor to a device descriptor, allowing the device to manage multiple endpoints.
 *
 * @param[in] dev_desc The device descriptor to add the endpoint descriptor to.
 * @param[in] ep_desc  The endpoint descriptor to add to the device descriptor.
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_device_add_endpoint_desc(ezb_af_device_desc_t dev_desc, ezb_af_ep_desc_t ep_desc);

/**
 * @brief Remove an endpoint descriptor from a Zigbee device descriptor.
 *
 * @param[in] dev_desc The device descriptor to remove the endpoint descriptor from.
 * @param[in] ep_id    The identifier of the endpoint to remove.
 * @return The endpoint descriptor removed, or EZB_INVALID_AF_EP_DESC if endpoint is not found.
 */
ezb_af_ep_desc_t ezb_af_device_remove_endpoint_desc(ezb_af_device_desc_t dev_desc, uint8_t ep_id);

/**
 * @brief Get an endpoint descriptor from a Zigbee device descriptor.
 *
 * This function retrieves an endpoint descriptor from a device descriptor based on the specified endpoint ID.
 *
 * @param[in] dev_desc The device descriptor to get the endpoint descriptor from.
 * @param[in] ep_id    The identifier of the endpoint to get the endpoint descriptor for.
 * @return The endpoint descriptor, or EZB_INVALID_AF_EP_DESC if not found.
 */
ezb_af_ep_desc_t ezb_af_device_get_endpoint_desc(ezb_af_device_desc_t dev_desc, uint8_t ep_id);

/**
 * @brief Register an application Zigbee device descriptor for the stack.
 *
 * @param[in] dev_desc The device descriptor to register.
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_device_desc_register(ezb_af_device_desc_t dev_desc);

/**
 * @brief Create a Zigbee endpoint descriptor from configuration.
 *
 * This function allocates and initializes a new endpoint descriptor structure using the provided configuration.
 *
 * @param[in] ep_config The pointer to the endpoint configuration structure. See @ref ezb_af_ep_config_s
 * @return The newly created endpoint descriptor, or EZB_INVALID_AF_EP_DESC on failure.
 */
ezb_af_ep_desc_t ezb_af_create_endpoint_desc(const ezb_af_ep_config_t *ep_config);

/**
 * @brief Free a Zigbee endpoint descriptor.
 *
 * This function frees the memory allocated for a endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to free.
 */
void ezb_af_free_endpoint_desc(ezb_af_ep_desc_t ep_desc);

/**
 * @brief Add a cluster descriptor to a Zigbee endpoint descriptor.
 *
 * This function links a cluster descriptor to an endpoint descriptor, allowing the endpoint to manage multiple clusters.
 *
 * @param[in] ep_desc      The endpoint descriptor to add the cluster descriptor to.
 * @param[in] cluster_desc The cluster descriptor to add to the endpoint descriptor.
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_endpoint_add_cluster_desc(ezb_af_ep_desc_t ep_desc, ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Remove a cluster descriptor from a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc      The endpoint descriptor to remove the cluster descriptor from.
 * @param[in] cluster_id   The identifier of the cluster to remove.
 * @param[in] role_mask    The role mask of the cluster to remove.
 * @param[in] manuf_code   The manufacturer code of the cluster to remove.
 * @return The cluster descriptor removed, or EZB_INVALID_ZCL_CLUSTER_DESC if cluster is not found.
 */
ezb_zcl_cluster_desc_t ezb_af_endpoint_remove_cluster_desc(ezb_af_ep_desc_t ep_desc,
                                                           uint16_t         cluster_id,
                                                           uint8_t          role_mask,
                                                           uint16_t         manuf_code);

/**
 * @brief Create a gateway endpoint descriptor.
 *
 * This function allocates and initializes a new gateway endpoint descriptor structure using the provided configuration.
 *
 * @param[in] ep_config The pointer to the endpoint configuration structure. See @ref ezb_af_ep_config_s
 * @return The newly created gateway endpoint descriptor, or EZB_INVALID_AF_EP_DESC on failure.
 */
ezb_af_ep_desc_t ezb_af_create_gateway_endpoint(const ezb_af_ep_config_t *ep_config);

/**
 * @brief Get the endpoint ID of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to get the identifier of the endpoint from.
 * @return The identifier of the endpoint.
 */
uint8_t ezb_af_ep_desc_get_ep_id(const ezb_af_ep_desc_t ep_desc);

/**
 * @brief Get the profile ID of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to get the profile ID from.
 * @return The identifier of the application profile. See @ref ezb_af_profile_id_t
 */
ezb_af_profile_id_t ezb_af_ep_desc_get_profile_id(const ezb_af_ep_desc_t ep_desc);

/**
 * @brief Set the profile ID of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to set the profile ID for.
 * @param[in] profile_id The identifier of the application profile to set.
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_ep_desc_set_profile_id(ezb_af_ep_desc_t ep_desc, uint16_t profile_id);

/**
 * @brief Get the application version of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to get the application version from.
 * @return The version of the application device.
 */
uint8_t ezb_af_ep_desc_get_app_version(const ezb_af_ep_desc_t ep_desc);

/**
 * @brief Set the application version of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to set the application version for.
 * @param[in] app_version The version of the application device to set.
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_ep_desc_set_app_version(ezb_af_ep_desc_t ep_desc, uint8_t app_version);

/**
 * @brief Get the application device ID of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to get the application device ID from.
 * @return The identifier of the application device.
 */
uint16_t ezb_af_ep_desc_get_app_device_id(const ezb_af_ep_desc_t ep_desc);

/**
 * @brief Set the application device ID of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to set the application device ID for.
 * @param[in] app_device_id The identifier of the application device to set.
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_ep_desc_set_app_device_id(ezb_af_ep_desc_t ep_desc, uint16_t app_device_id);

/**
 * @brief Get the simple descriptor of a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc The endpoint descriptor to get the simple descriptor from.
 * @return The pointer to the simple descriptor structure. See @ref ezb_af_simple_desc_s, or NULL if not found.
 */
const ezb_af_simple_desc_t *ezb_af_ep_desc_get_simple_desc(const ezb_af_ep_desc_t ep_desc);

/**
 * @brief Get the next endpoint descriptor from a Zigbee device descriptor.
 *
 * @param[in] dev_desc The device descriptor to get the next endpoint descriptor from.
 * @param[in] ep_desc  The endpoint descriptor used to retrieve the next endpoint descriptor.
 * @return The pointer to the next endpoint descriptor. See @ref ezb_af_ep_desc_t, or EZB_INVALID_AF_EP_DESC if not found.
 */
ezb_af_ep_desc_t ezb_af_device_desc_get_next_endpoint_desc(const ezb_af_device_desc_t dev_desc, const ezb_af_ep_desc_t ep_desc);

/**
 * @brief Get the next cluster descriptor from a Zigbee endpoint descriptor.
 *
 * @param[in] ep_desc      The endpoint descriptor to get the next cluster descriptor from.
 * @param[in] cluster_desc The cluster descriptor used to retrieve the next cluster descriptor.
 * @return The pointer to the next cluster descriptor. See @ref ezb_zcl_cluster_desc_t, or EZB_INVALID_ZCL_CLUSTER_DESC if not found.
 */
ezb_zcl_cluster_desc_t ezb_af_ep_desc_get_next_cluster_desc(const ezb_af_ep_desc_t       ep_desc,
                                                            const ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the endpoint descriptor.
 *
 * This function retrieves the endpoint descriptor for a registered endpoint.
 * The endpoint must have been previously registered using ezb_af_device_register().
 *
 * @param[in] ep_id The identifier of the endpoint to get the endpoint descriptor for.
 * @return The endpoint descriptor, or EZB_INVALID_AF_EP_DESC if not found.
 */
ezb_af_ep_desc_t ezb_af_get_ep_desc(uint8_t ep_id);

/**
 * @brief Get a cluster descriptor from an endpoint descriptor.
 *
 * @param[in] ep_desc    The endpoint descriptor to get the cluster descriptor from.
 * @param[in] cluster_id The identifier of the cluster to get the cluster descriptor for.
 * @param[in] role       The role of the cluster to get the cluster descriptor for.
 * @return The pointer to the cluster descriptor. See @ref ezb_zcl_cluster_desc_t, or EZB_INVALID_ZCL_CLUSTER_DESC if not found.
 */
ezb_zcl_cluster_desc_t ezb_af_endpoint_get_cluster_desc(const ezb_af_ep_desc_t ep_desc, uint16_t cluster_id, uint8_t role);

/**
 * @brief Reset the endpoint to default.
 *
 * The function is used to reset the endpoint to the default value from the @p get_default_value callback.
 *
 * @param[in] ep_id             The endpoint identifier that to be reset.
 * @param[in] get_default_value The callback to get the default attribute value from application.
 * @return The error code. See @ref ezb_err_t
 */
ezb_err_t ezb_af_endpoint_reset(uint8_t ep_id, ezb_af_endpoint_get_default_attr_value_callback_t get_default_value);

#ifdef __cplusplus
} /*  extern "C" */
#endif
