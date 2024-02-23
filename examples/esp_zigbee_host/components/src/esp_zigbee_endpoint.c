/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "esp_host_zb.h"

esp_err_t esp_host_zb_ep_create(esp_host_zb_endpoint_t *endpoint)
{
    typedef struct {
        uint8_t     endpoint;                               /*!< The application endpoint to be added */
        uint16_t    profileId;                              /*!< The endpoint's application profile */
        uint16_t    deviceId;                               /*!< The endpoint's device ID within the application profile */
        uint8_t     appFlags;                               /*!< The device version and flags indicating description availability */
        uint8_t     inputClusterCount;                      /*!< The number of cluster IDs in inputClusterList */
        uint8_t     outputClusterCount;                     /*!< The number of cluster IDs in outputClusterList */
    } __attribute__ ((packed)) esp_endpoint_t;
 
    uint16_t data_len = 0;
    uint16_t data_head_len = sizeof(esp_endpoint_t);
    uint16_t inputClusterLength = endpoint->inputClusterCount * sizeof(uint16_t);
    uint16_t outputClusterLength = endpoint->outputClusterCount * sizeof(uint16_t);
    uint8_t *input = calloc(1, data_head_len + inputClusterLength + outputClusterLength);

    if (input) {
        esp_endpoint_t esp_endpoint = {
            .endpoint = endpoint->endpoint,
            .profileId = endpoint->profileId,
            .deviceId = endpoint->deviceId,
            .appFlags = endpoint->appFlags,
            .inputClusterCount = endpoint->inputClusterCount,
            .outputClusterCount = endpoint->outputClusterCount,
        };
        data_len = data_head_len + inputClusterLength + outputClusterLength;
        memcpy(input, &esp_endpoint, data_head_len);
        if (inputClusterLength) {
            memcpy(input + data_head_len, endpoint->inputClusterList, inputClusterLength);

        }

        if (outputClusterLength) {
            memcpy(input + data_head_len + inputClusterLength, endpoint->outputClusterList, outputClusterLength);
        }
    }

    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    esp_host_zb_output(ESP_ZNSP_ZCL_ENDPOINT_ADD, input, data_len, &output, &outlen);

    if (input) {
        free(input);
        input = NULL;
    }

    return ESP_OK;
}

