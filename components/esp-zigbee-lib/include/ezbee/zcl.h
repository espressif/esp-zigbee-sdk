/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>
#include <ezbee/zcl/zcl_core.h>
#include <ezbee/zcl/zcl_desc.h>
#include <ezbee/zcl/zcl_reporting.h>
#include <ezbee/zcl/zcl_general_cmd.h>
#include <ezbee/zcl/cluster/basic.h>
#include <ezbee/zcl/cluster/identify.h>
#include <ezbee/zcl/cluster/power_config.h>
#include <ezbee/zcl/cluster/custom.h>
#include <ezbee/zcl/cluster/device_temp_config.h>
#include <ezbee/zcl/cluster/dehumidification_control.h>
#include <ezbee/zcl/cluster/meter_identification.h>
#include <ezbee/zcl/cluster/occupancy_sensing.h>
#include <ezbee/zcl/cluster/on_off_switch_config.h>
#include <ezbee/zcl/cluster/shade_config.h>
#include <ezbee/zcl/cluster/window_covering.h>
#include <ezbee/zcl/cluster/electrical_measurement.h>
#include <ezbee/zcl/cluster/door_lock.h>
#include <ezbee/zcl/cluster/groups.h>
#include <ezbee/zcl/cluster/scenes.h>
#include <ezbee/zcl/cluster/on_off.h>
#include <ezbee/zcl/cluster/alarms.h>
#include <ezbee/zcl/cluster/time.h>
#include <ezbee/zcl/cluster/analog_input.h>
#include <ezbee/zcl/cluster/analog_output.h>
#include <ezbee/zcl/cluster/analog_value.h>
#include <ezbee/zcl/cluster/binary_input.h>
#include <ezbee/zcl/cluster/binary_output.h>
#include <ezbee/zcl/cluster/binary_value.h>
#include <ezbee/zcl/cluster/multistate_input.h>
#include <ezbee/zcl/cluster/multistate_output.h>
#include <ezbee/zcl/cluster/multistate_value.h>
#include <ezbee/zcl/cluster/price.h>
#include <ezbee/zcl/cluster/simple_measurement.h>
#include <ezbee/zcl/cluster/metering.h>
#include <ezbee/zcl/cluster/ias_wd.h>
#include <ezbee/zcl/cluster/ias_zone.h>
#include <ezbee/zcl/cluster/ias_ace.h>
#include <ezbee/zcl/cluster/level.h>
#include <ezbee/zcl/cluster/color_control.h>
#include <ezbee/zcl/cluster/fan_control.h>
#include <ezbee/zcl/cluster/thermostat.h>
#include <ezbee/zcl/cluster/thermostat_ui_config.h>
#include <ezbee/zcl/cluster/poll_control.h>
#include <ezbee/zcl/cluster/ota_upgrade.h>
#include <ezbee/zcl/cluster/touchlink_commissioning.h>
