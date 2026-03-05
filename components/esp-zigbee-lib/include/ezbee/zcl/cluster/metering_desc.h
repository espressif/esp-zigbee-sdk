/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>
#include <ezbee/zcl/zcl_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------------------------------------------*
   METERING Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the metering cluster implementation */
#define EZB_ZCL_METERING_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the metering server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_METERING_CURRENT_SUMMATION_DELIVERED_ID       = 0x0000U, /*!< CurrentSummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_SUMMATION_RECEIVED_ID        = 0x0001U, /*!< CurrentSummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MAX_DEMAND_DELIVERED_ID      = 0x0002U, /*!< CurrentMaxDemandDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MAX_DEMAND_RECEIVED_ID       = 0x0003U, /*!< CurrentMaxDemandReceived attribute. */
    EZB_ZCL_ATTR_METERING_DFT_SUMMATION_ID                     = 0x0004U, /*!< DFTSummation attribute. */
    EZB_ZCL_ATTR_METERING_DAILY_FREEZE_TIME_ID                 = 0x0005U, /*!< DailyFreezeTime attribute. */
    EZB_ZCL_ATTR_METERING_POWER_FACTOR_ID                      = 0x0006U, /*!< PowerFactor attribute. */
    EZB_ZCL_ATTR_METERING_READING_SNAP_SHOT_TIME_ID            = 0x0007U, /*!< ReadingSnapShotTime attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MAX_DEMAND_DELIVERED_TIME_ID = 0x0008U, /*!< CurrentMaxDemandDeliveredTime attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MAX_DEMAND_RECEIVED_TIME_ID  = 0x0009U, /*!< CurrentMaxDemandReceivedTime attribute. */
    EZB_ZCL_ATTR_METERING_DEFAULT_UPDATE_PERIOD_ID             = 0x000AU, /*!< DefaultUpdatePeriod attribute. */
    EZB_ZCL_ATTR_METERING_FAST_POLL_UPDATE_PERIOD_ID           = 0x000BU, /*!< FastPollUpdatePeriod attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_BLOCK_PERIOD_CONSUMPTION_DELIVERED_ID =
        0x000CU,                                                       /*!< CurrentBlockPeriodConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_DAILY_CONSUMPTION_TARGET_ID       = 0x000DU, /*!< DailyConsumptionTarget attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_BLOCK_ID                  = 0x000EU, /*!< CurrentBlock attribute. */
    EZB_ZCL_ATTR_METERING_PROFILE_INTERVAL_PERIOD_ID        = 0x000FU, /*!< ProfileIntervalPeriod attribute. */
    EZB_ZCL_ATTR_METERING_PRESET_READING_TIME_ID            = 0x0011U, /*!< PresetReadingTime attribute. */
    EZB_ZCL_ATTR_METERING_SUMMATION_DELIVERED_PER_REPORT_ID = 0x0012U, /*!< SummationDeliveredPerReport attribute. */
    EZB_ZCL_ATTR_METERING_FLOW_RESTRICTION_ID               = 0x0013U, /*!< FlowRestriction attribute. */
    EZB_ZCL_ATTR_METERING_SUPPLY_STATUS_ID                  = 0x0014U, /*!< SupplyStatus attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_INLET_ENERGY_CARRIER_SUMMATION_ID =
        0x0015U, /*!< CurrentInletEnergyCarrierSummation attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_OUTLET_ENERGY_CARRIER_SUMMATION_ID =
        0x0016U, /*!< CurrentOutletEnergyCarrierSummation attribute. */
    EZB_ZCL_ATTR_METERING_INLET_TEMPERATURE_ID                    = 0x0017U, /*!< InletTemperature attribute. */
    EZB_ZCL_ATTR_METERING_OUTLET_TEMPERATURE_ID                   = 0x0018U, /*!< OutletTemperature attribute. */
    EZB_ZCL_ATTR_METERING_CONTROL_TEMPERATURE_ID                  = 0x0019U, /*!< ControlTemperature attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_INLET_ENERGY_CARRIER_DEMAND_ID  = 0x001AU, /*!< CurrentInletEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_OUTLET_ENERGY_CARRIER_DEMAND_ID = 0x001BU, /*!< CurrentOutletEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_BLOCK_PERIOD_CONSUMPTION_DELIVERED_ID =
        0x001CU, /*!< PreviousBlockPeriodConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_BLOCK_PERIOD_CONSUMPTION_RECEIVED_ID =
        0x001DU, /*!< CurrentBlockPeriodConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_BLOCK_RECEIVED_ID              = 0x001EU, /*!< CurrentBlockReceived attribute. */
    EZB_ZCL_ATTR_METERING_DFT_SUMMATION_RECEIVED_ID              = 0x001FU, /*!< DFTSummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_ACTIVE_REGISTER_TIER_DELIVERED_ID      = 0x0020U, /*!< ActiveRegisterTierDelivered attribute. */
    EZB_ZCL_ATTR_METERING_ACTIVE_REGISTER_TIER_RECEIVED_ID       = 0x0021U, /*!< ActiveRegisterTierReceived attribute. */
    EZB_ZCL_ATTR_METERING_LAST_BLOCK_SWITCH_TIME_ID              = 0x0022U, /*!< LastBlockSwitchTime attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_SUMMATION_DELIVERED_ID   = 0x0100U, /*!< CurrentTier1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_SUMMATION_RECEIVED_ID    = 0x0101U, /*!< CurrentTier1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_SUMMATION_DELIVERED_ID   = 0x0102U, /*!< CurrentTier2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_SUMMATION_RECEIVED_ID    = 0x0103U, /*!< CurrentTier2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_SUMMATION_DELIVERED_ID   = 0x0104U, /*!< CurrentTier3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_SUMMATION_RECEIVED_ID    = 0x0105U, /*!< CurrentTier3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_SUMMATION_DELIVERED_ID   = 0x0106U, /*!< CurrentTier4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_SUMMATION_RECEIVED_ID    = 0x0107U, /*!< CurrentTier4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_SUMMATION_DELIVERED_ID   = 0x0108U, /*!< CurrentTier5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_SUMMATION_RECEIVED_ID    = 0x0109U, /*!< CurrentTier5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_SUMMATION_DELIVERED_ID   = 0x010AU, /*!< CurrentTier6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_SUMMATION_RECEIVED_ID    = 0x010BU, /*!< CurrentTier6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_SUMMATION_DELIVERED_ID   = 0x010CU, /*!< CurrentTier7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_SUMMATION_RECEIVED_ID    = 0x010DU, /*!< CurrentTier7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_SUMMATION_DELIVERED_ID   = 0x010EU, /*!< CurrentTier8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_SUMMATION_RECEIVED_ID    = 0x010FU, /*!< CurrentTier8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_SUMMATION_DELIVERED_ID   = 0x0110U, /*!< CurrentTier9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_SUMMATION_RECEIVED_ID    = 0x0111U, /*!< CurrentTier9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_SUMMATION_DELIVERED_ID  = 0x0112U, /*!< CurrentTier10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_SUMMATION_RECEIVED_ID   = 0x0113U, /*!< CurrentTier10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_SUMMATION_DELIVERED_ID  = 0x0114U, /*!< CurrentTier11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_SUMMATION_RECEIVED_ID   = 0x0115U, /*!< CurrentTier11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_SUMMATION_DELIVERED_ID  = 0x0116U, /*!< CurrentTier12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_SUMMATION_RECEIVED_ID   = 0x0117U, /*!< CurrentTier12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_SUMMATION_DELIVERED_ID  = 0x0118U, /*!< CurrentTier13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_SUMMATION_RECEIVED_ID   = 0x0119U, /*!< CurrentTier13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_SUMMATION_DELIVERED_ID  = 0x011AU, /*!< CurrentTier14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_SUMMATION_RECEIVED_ID   = 0x011BU, /*!< CurrentTier14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_SUMMATION_DELIVERED_ID  = 0x011CU, /*!< CurrentTier15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_SUMMATION_RECEIVED_ID   = 0x011DU, /*!< CurrentTier15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER16_SUMMATION_DELIVERED_ID  = 0x011EU, /*!< CurrentTier16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER16_SUMMATION_RECEIVED_ID   = 0x011FU, /*!< CurrentTier16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER17_SUMMATION_DELIVERED_ID  = 0x0120U, /*!< CurrentTier17SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER17_SUMMATION_RECEIVED_ID   = 0x0121U, /*!< CurrentTier17SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER18_SUMMATION_DELIVERED_ID  = 0x0122U, /*!< CurrentTier18SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER18_SUMMATION_RECEIVED_ID   = 0x0123U, /*!< CurrentTier18SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER19_SUMMATION_DELIVERED_ID  = 0x0124U, /*!< CurrentTier19SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER19_SUMMATION_RECEIVED_ID   = 0x0125U, /*!< CurrentTier19SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER20_SUMMATION_DELIVERED_ID  = 0x0126U, /*!< CurrentTier20SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER20_SUMMATION_RECEIVED_ID   = 0x0127U, /*!< CurrentTier20SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER21_SUMMATION_DELIVERED_ID  = 0x0128U, /*!< CurrentTier21SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER21_SUMMATION_RECEIVED_ID   = 0x0129U, /*!< CurrentTier21SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER22_SUMMATION_DELIVERED_ID  = 0x012AU, /*!< CurrentTier22SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER22_SUMMATION_RECEIVED_ID   = 0x012BU, /*!< CurrentTier22SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER23_SUMMATION_DELIVERED_ID  = 0x012CU, /*!< CurrentTier23SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER23_SUMMATION_RECEIVED_ID   = 0x012DU, /*!< CurrentTier23SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER24_SUMMATION_DELIVERED_ID  = 0x012EU, /*!< CurrentTier24SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER24_SUMMATION_RECEIVED_ID   = 0x012FU, /*!< CurrentTier24SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER25_SUMMATION_DELIVERED_ID  = 0x0130U, /*!< CurrentTier25SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER25_SUMMATION_RECEIVED_ID   = 0x0131U, /*!< CurrentTier25SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER26_SUMMATION_DELIVERED_ID  = 0x0132U, /*!< CurrentTier26SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER26_SUMMATION_RECEIVED_ID   = 0x0133U, /*!< CurrentTier26SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER27_SUMMATION_DELIVERED_ID  = 0x0134U, /*!< CurrentTier27SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER27_SUMMATION_RECEIVED_ID   = 0x0135U, /*!< CurrentTier27SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER28_SUMMATION_DELIVERED_ID  = 0x0136U, /*!< CurrentTier28SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER28_SUMMATION_RECEIVED_ID   = 0x0137U, /*!< CurrentTier28SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER29_SUMMATION_DELIVERED_ID  = 0x0138U, /*!< CurrentTier29SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER29_SUMMATION_RECEIVED_ID   = 0x0139U, /*!< CurrentTier29SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER30_SUMMATION_DELIVERED_ID  = 0x013AU, /*!< CurrentTier30SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER30_SUMMATION_RECEIVED_ID   = 0x013BU, /*!< CurrentTier30SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER31_SUMMATION_DELIVERED_ID  = 0x013CU, /*!< CurrentTier31SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER31_SUMMATION_RECEIVED_ID   = 0x013DU, /*!< CurrentTier31SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER32_SUMMATION_DELIVERED_ID  = 0x013EU, /*!< CurrentTier32SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER32_SUMMATION_RECEIVED_ID   = 0x013FU, /*!< CurrentTier32SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER33_SUMMATION_DELIVERED_ID  = 0x0140U, /*!< CurrentTier33SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER33_SUMMATION_RECEIVED_ID   = 0x0141U, /*!< CurrentTier33SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER34_SUMMATION_DELIVERED_ID  = 0x0142U, /*!< CurrentTier34SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER34_SUMMATION_RECEIVED_ID   = 0x0143U, /*!< CurrentTier34SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER35_SUMMATION_DELIVERED_ID  = 0x0144U, /*!< CurrentTier35SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER35_SUMMATION_RECEIVED_ID   = 0x0145U, /*!< CurrentTier35SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER36_SUMMATION_DELIVERED_ID  = 0x0146U, /*!< CurrentTier36SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER36_SUMMATION_RECEIVED_ID   = 0x0147U, /*!< CurrentTier36SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER37_SUMMATION_DELIVERED_ID  = 0x0148U, /*!< CurrentTier37SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER37_SUMMATION_RECEIVED_ID   = 0x0149U, /*!< CurrentTier37SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER38_SUMMATION_DELIVERED_ID  = 0x014AU, /*!< CurrentTier38SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER38_SUMMATION_RECEIVED_ID   = 0x014BU, /*!< CurrentTier38SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER39_SUMMATION_DELIVERED_ID  = 0x014CU, /*!< CurrentTier39SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER39_SUMMATION_RECEIVED_ID   = 0x014DU, /*!< CurrentTier39SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER40_SUMMATION_DELIVERED_ID  = 0x014EU, /*!< CurrentTier40SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER40_SUMMATION_RECEIVED_ID   = 0x014FU, /*!< CurrentTier40SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER41_SUMMATION_DELIVERED_ID  = 0x0150U, /*!< CurrentTier41SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER41_SUMMATION_RECEIVED_ID   = 0x0151U, /*!< CurrentTier41SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER42_SUMMATION_DELIVERED_ID  = 0x0152U, /*!< CurrentTier42SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER42_SUMMATION_RECEIVED_ID   = 0x0153U, /*!< CurrentTier42SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER43_SUMMATION_DELIVERED_ID  = 0x0154U, /*!< CurrentTier43SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER43_SUMMATION_RECEIVED_ID   = 0x0155U, /*!< CurrentTier43SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER44_SUMMATION_DELIVERED_ID  = 0x0156U, /*!< CurrentTier44SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER44_SUMMATION_RECEIVED_ID   = 0x0157U, /*!< CurrentTier44SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER45_SUMMATION_DELIVERED_ID  = 0x0158U, /*!< CurrentTier45SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER45_SUMMATION_RECEIVED_ID   = 0x0159U, /*!< CurrentTier45SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER46_SUMMATION_DELIVERED_ID  = 0x015AU, /*!< CurrentTier46SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER46_SUMMATION_RECEIVED_ID   = 0x015BU, /*!< CurrentTier46SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER47_SUMMATION_DELIVERED_ID  = 0x015CU, /*!< CurrentTier47SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER47_SUMMATION_RECEIVED_ID   = 0x015DU, /*!< CurrentTier47SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER48_SUMMATION_DELIVERED_ID  = 0x015EU, /*!< CurrentTier48SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER48_SUMMATION_RECEIVED_ID   = 0x015FU, /*!< CurrentTier48SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CPP1_SUMMATION_DELIVERED_ID            = 0x01FCU, /*!< CPP1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CPP2_SUMMATION_DELIVERED_ID            = 0x01FEU, /*!< CPP2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_STATUS_ID                              = 0x0200U, /*!< Status attribute. */
    EZB_ZCL_ATTR_METERING_REMAINING_BATTERY_LIFE_ID              = 0x0201U, /*!< RemainingBatteryLife attribute. */
    EZB_ZCL_ATTR_METERING_HOURS_IN_OPERATION_ID                  = 0x0202U, /*!< HoursInOperation attribute. */
    EZB_ZCL_ATTR_METERING_HOURS_IN_FAULT_ID                      = 0x0203U, /*!< HoursInFault attribute. */
    EZB_ZCL_ATTR_METERING_EXTENDED_STATUS_ID                     = 0x0204U, /*!< ExtendedStatus attribute. */
    EZB_ZCL_ATTR_METERING_REMAINING_BATTERY_LIFE_IN_DAYS_ID      = 0x0205U, /*!< RemainingBatteryLifeInDays attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_METER_ID_ID                    = 0x0206U, /*!< CurrentMeterID attribute. */
    EZB_ZCL_ATTR_METERING_AMBIENT_CONSUMPTION_INDICATOR_ID       = 0x0207U, /*!< AmbientConsumptionIndicator attribute. */
    EZB_ZCL_ATTR_METERING_UNIT_OF_MEASURE_ID                     = 0x0300U, /*!< UnitOfMeasure attribute. */
    EZB_ZCL_ATTR_METERING_MULTIPLIER_ID                          = 0x0301U, /*!< Multiplier attribute. */
    EZB_ZCL_ATTR_METERING_DIVISOR_ID                             = 0x0302U, /*!< Divisor attribute. */
    EZB_ZCL_ATTR_METERING_SUMMATION_FORMATTING_ID                = 0x0303U, /*!< SummationFormatting attribute. */
    EZB_ZCL_ATTR_METERING_DEMAND_FORMATTING_ID                   = 0x0304U, /*!< DemandFormatting attribute. */
    EZB_ZCL_ATTR_METERING_HISTORICAL_CONSUMPTION_FORMATTING_ID   = 0x0305U, /*!< HistoricalConsumptionFormatting attribute. */
    EZB_ZCL_ATTR_METERING_METERING_DEVICE_TYPE_ID                = 0x0306U, /*!< MeteringDeviceType attribute. */
    EZB_ZCL_ATTR_METERING_SITE_ID_ID                             = 0x0307U, /*!< SiteID attribute. */
    EZB_ZCL_ATTR_METERING_METER_SERIAL_NUMBER_ID                 = 0x0308U, /*!< MeterSerialNumber attribute. */
    EZB_ZCL_ATTR_METERING_ENERGY_CARRIER_UNIT_OF_MEASURE_ID      = 0x0309U, /*!< EnergyCarrierUnitOfMeasure attribute. */
    EZB_ZCL_ATTR_METERING_ENERGY_CARRIER_SUMMATION_FORMATTING_ID = 0x030AU, /*!< EnergyCarrierSummationFormatting attribute. */
    EZB_ZCL_ATTR_METERING_ENERGY_CARRIER_DEMAND_FORMATTING_ID    = 0x030BU, /*!< EnergyCarrierDemandFormatting attribute. */
    EZB_ZCL_ATTR_METERING_TEMPERATURE_UNIT_OF_MEASURE_ID         = 0x030CU, /*!< TemperatureUnitOfMeasure attribute. */
    EZB_ZCL_ATTR_METERING_TEMPERATURE_FORMATTING_ID              = 0x030DU, /*!< TemperatureFormatting attribute. */
    EZB_ZCL_ATTR_METERING_MODULE_SERIAL_NUMBER_ID                = 0x030EU, /*!< ModuleSerialNumber attribute. */
    EZB_ZCL_ATTR_METERING_OPERATING_TARIFF_LABEL_DELIVERED_ID    = 0x030FU, /*!< OperatingTariffLabelDelivered attribute. */
    EZB_ZCL_ATTR_METERING_OPERATING_TARIFF_LABEL_RECEIVED_ID     = 0x0310U, /*!< OperatingTariffLabelReceived attribute. */
    EZB_ZCL_ATTR_METERING_CUSTOMER_ID_NUMBER_ID                  = 0x0311U, /*!< CustomerIDNumber attribute. */
    EZB_ZCL_ATTR_METERING_ALTERNATIVE_UNIT_OF_ID                 = 0x0312U, /*!< AlternativeUnitOf attribute. */
    EZB_ZCL_ATTR_METERING_ALTERNATIVE_DEMAND_FORMATTING_ID       = 0x0313U, /*!< AlternativeDemandFormatting attribute. */
    EZB_ZCL_ATTR_METERING_ALTERNATIVE_CONSUMPTION_FORMATTING_ID  = 0x0314U, /*!< AlternativeConsumptionFormatting attribute. */
    EZB_ZCL_ATTR_METERING_INSTANTANEOUS_DEMAND_ID                = 0x0400U, /*!< InstantaneousDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_CONSUMPTION_DELIVERED_ID   = 0x0401U, /*!< CurrentDayConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_CONSUMPTION_RECEIVED_ID    = 0x0402U, /*!< CurrentDayConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_CONSUMPTION_DELIVERED_ID  = 0x0403U, /*!< PreviousDayConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_CONSUMPTION_RECEIVED_ID   = 0x0404U, /*!< PreviousDayConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_PARTIAL_PROFILE_INTERVAL_START_TIME_DELIVERED_ID =
        0x0405U, /*!< CurrentPartialProfileIntervalStartTimeDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_PARTIAL_PROFILE_INTERVAL_START_TIME_RECEIVED_ID =
        0x0406U, /*!< CurrentPartialProfileIntervalStartTimeReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_PARTIAL_PROFILE_INTERVAL_VALUE_DELIVERED_ID =
        0x0407U, /*!< CurrentPartialProfileIntervalValueDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_PARTIAL_PROFILE_INTERVAL_VALUE_RECEIVED_ID =
        0x0408U,                                                  /*!< CurrentPartialProfileIntervalValueReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_MAX_PRESSURE_ID  = 0x0409U, /*!< CurrentDayMaxPressure attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_MIN_PRESSURE_ID  = 0x040AU, /*!< CurrentDayMinPressure attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_MAX_PRESSURE_ID = 0x040BU, /*!< PreviousDayMaxPressure attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_MIN_PRESSURE_ID = 0x040CU, /*!< PreviousDayMinPressure attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_MAX_DEMAND_ID    = 0x040DU, /*!< CurrentDayMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_MAX_DEMAND_ID   = 0x040EU, /*!< PreviousDayMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_MAX_DEMAND_ID  = 0x040FU, /*!< CurrentMonthMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_YEAR_MAX_DEMAND_ID   = 0x0410U, /*!< CurrentYearMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_MAX_ENERGY_CARRIER_DEMAND_ID =
        0x0411U, /*!< CurrentDayMaxEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_MAX_ENERGY_CARRIER_DEMAND_ID =
        0x0412U, /*!< PreviousDayMaxEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_MAX_ENERGY_CARRIER_DEMAND_ID =
        0x0413U, /*!< CurrentMonthMaxEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_MIN_ENERGY_CARRIER_DEMAND_ID =
        0x0414U, /*!< CurrentMonthMinEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_YEAR_MAX_ENERGY_CARRIER_DEMAND_ID =
        0x0415U, /*!< CurrentYearMaxEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_YEAR_MIN_ENERGY_CARRIER_DEMAND_ID =
        0x0416U,                                                            /*!< CurrentYearMinEnergyCarrierDemand attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY2_CONSUMPTION_DELIVERED_ID = 0x0420U, /*!< PreviousDay2ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY2_CONSUMPTION_RECEIVED_ID  = 0x0421U, /*!< PreviousDay2ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY3_CONSUMPTION_DELIVERED_ID = 0x0422U, /*!< PreviousDay3ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY3_CONSUMPTION_RECEIVED_ID  = 0x0423U, /*!< PreviousDay3ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY4_CONSUMPTION_DELIVERED_ID = 0x0424U, /*!< PreviousDay4ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY4_CONSUMPTION_RECEIVED_ID  = 0x0425U, /*!< PreviousDay4ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY5_CONSUMPTION_DELIVERED_ID = 0x0426U, /*!< PreviousDay5ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY5_CONSUMPTION_RECEIVED_ID  = 0x0427U, /*!< PreviousDay5ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY6_CONSUMPTION_DELIVERED_ID = 0x0428U, /*!< PreviousDay6ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY6_CONSUMPTION_RECEIVED_ID  = 0x0429U, /*!< PreviousDay6ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY7_CONSUMPTION_DELIVERED_ID = 0x042AU, /*!< PreviousDay7ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY7_CONSUMPTION_RECEIVED_ID  = 0x042BU, /*!< PreviousDay7ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY8_CONSUMPTION_DELIVERED_ID = 0x042CU, /*!< PreviousDay8ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY8_CONSUMPTION_RECEIVED_ID  = 0x042DU, /*!< PreviousDay8ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_WEEK_CONSUMPTION_DELIVERED_ID  = 0x0430U, /*!< CurrentWeekConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_WEEK_CONSUMPTION_RECEIVED_ID   = 0x0431U, /*!< CurrentWeekConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK_CONSUMPTION_DELIVERED_ID = 0x0432U, /*!< PreviousWeekConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK_CONSUMPTION_RECEIVED_ID  = 0x0433U, /*!< PreviousWeekConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK2_CONSUMPTION_DELIVERED_ID =
        0x0434U,                                                            /*!< PreviousWeek2ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK2_CONSUMPTION_RECEIVED_ID = 0x0435U, /*!< PreviousWeek2ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK3_CONSUMPTION_DELIVERED_ID =
        0x0436U,                                                            /*!< PreviousWeek3ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK3_CONSUMPTION_RECEIVED_ID = 0x0437U, /*!< PreviousWeek3ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK4_CONSUMPTION_DELIVERED_ID =
        0x0438U,                                                            /*!< PreviousWeek4ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK4_CONSUMPTION_RECEIVED_ID = 0x0439U, /*!< PreviousWeek4ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK5_CONSUMPTION_DELIVERED_ID =
        0x043AU,                                                            /*!< PreviousWeek5ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK5_CONSUMPTION_RECEIVED_ID = 0x043BU, /*!< PreviousWeek5ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_CONSUMPTION_DELIVERED_ID = 0x0440U, /*!< CurrentMonthConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_CONSUMPTION_RECEIVED_ID  = 0x0441U, /*!< CurrentMonthConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH_CONSUMPTION_DELIVERED_ID =
        0x0442U,                                                            /*!< PreviousMonthConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH_CONSUMPTION_RECEIVED_ID = 0x0443U, /*!< PreviousMonthConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH2_CONSUMPTION_DELIVERED_ID =
        0x0444U, /*!< PreviousMonth2ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH2_CONSUMPTION_RECEIVED_ID =
        0x0445U, /*!< PreviousMonth2ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH3_CONSUMPTION_DELIVERED_ID =
        0x0446U, /*!< PreviousMonth3ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH3_CONSUMPTION_RECEIVED_ID =
        0x0447U, /*!< PreviousMonth3ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH4_CONSUMPTION_DELIVERED_ID =
        0x0448U, /*!< PreviousMonth4ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH4_CONSUMPTION_RECEIVED_ID =
        0x0449U, /*!< PreviousMonth4ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH5_CONSUMPTION_DELIVERED_ID =
        0x044AU, /*!< PreviousMonth5ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH5_CONSUMPTION_RECEIVED_ID =
        0x044BU, /*!< PreviousMonth5ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH6_CONSUMPTION_DELIVERED_ID =
        0x044CU, /*!< PreviousMonth6ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH6_CONSUMPTION_RECEIVED_ID =
        0x044DU, /*!< PreviousMonth6ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH7_CONSUMPTION_DELIVERED_ID =
        0x044EU, /*!< PreviousMonth7ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH7_CONSUMPTION_RECEIVED_ID =
        0x044FU, /*!< PreviousMonth7ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH8_CONSUMPTION_DELIVERED_ID =
        0x0450U, /*!< PreviousMonth8ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH8_CONSUMPTION_RECEIVED_ID =
        0x0451U, /*!< PreviousMonth8ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH9_CONSUMPTION_DELIVERED_ID =
        0x0452U, /*!< PreviousMonth9ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH9_CONSUMPTION_RECEIVED_ID =
        0x0453U, /*!< PreviousMonth9ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH10_CONSUMPTION_DELIVERED_ID =
        0x0454U, /*!< PreviousMonth10ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH10_CONSUMPTION_RECEIVED_ID =
        0x0455U, /*!< PreviousMonth10ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH11_CONSUMPTION_DELIVERED_ID =
        0x0456U, /*!< PreviousMonth11ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH11_CONSUMPTION_RECEIVED_ID =
        0x0457U, /*!< PreviousMonth11ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH12_CONSUMPTION_DELIVERED_ID =
        0x0458U, /*!< PreviousMonth12ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH12_CONSUMPTION_RECEIVED_ID =
        0x0459U, /*!< PreviousMonth12ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH13_CONSUMPTION_DELIVERED_ID =
        0x045AU, /*!< PreviousMonth13ConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH13_CONSUMPTION_RECEIVED_ID =
        0x045BU,                                                        /*!< PreviousMonth13ConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_HISTORICAL_FREEZE_TIME_ID          = 0x045CU, /*!< HistoricalFreezeTime attribute. */
    EZB_ZCL_ATTR_METERING_MAX_NUMBER_OF_PERIODS_DELIVERED_ID = 0x0500U, /*!< MaxNumberOfPeriodsDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DEMAND_DELIVERED_ID        = 0x0600U, /*!< CurrentDemandDelivered attribute. */
    EZB_ZCL_ATTR_METERING_DEMAND_LIMIT_ID                    = 0x0601U, /*!< DemandLimit attribute. */
    EZB_ZCL_ATTR_METERING_DEMAND_INTEGRATION_PERIOD_ID       = 0x0602U, /*!< DemandIntegrationPeriod attribute. */
    EZB_ZCL_ATTR_METERING_NUMBER_OF_DEMAND_SUB_INTERVALS_ID  = 0x0603U, /*!< NumberOfDemandSubIntervals attribute. */
    EZB_ZCL_ATTR_METERING_DEMAND_LIMIT_ARM_DURATION_ID       = 0x0604U, /*!< DemandLimitArmDuration attribute. */
    EZB_ZCL_ATTR_METERING_LOAD_LIMIT_SUPPLY_STATE_ID         = 0x0605U, /*!< LoadLimitSupplyState attribute. */
    EZB_ZCL_ATTR_METERING_LOAD_LIMIT_COUNTER_ID              = 0x0606U, /*!< LoadLimitCounter attribute. */
    EZB_ZCL_ATTR_METERING_SUPPLY_TAMPER_STATE_ID             = 0x0607U, /*!< SupplyTamperState attribute. */
    EZB_ZCL_ATTR_METERING_SUPPLY_DEPLETION_STATE_ID          = 0x0608U, /*!< SupplyDepletionState attribute. */
    EZB_ZCL_ATTR_METERING_SUPPLY_UNCONTROLLED_FLOW_STATE_ID  = 0x0609U, /*!< SupplyUncontrolledFlowState attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0700U, /*!< CurrentNoTierBlock1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0701U, /*!< CurrentNoTierBlock2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0702U, /*!< CurrentNoTierBlock3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0703U, /*!< CurrentNoTierBlock4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0704U, /*!< CurrentNoTierBlock5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0705U, /*!< CurrentNoTierBlock6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0706U, /*!< CurrentNoTierBlock7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0707U, /*!< CurrentNoTierBlock8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0708U, /*!< CurrentNoTierBlock9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0709U, /*!< CurrentNoTierBlock10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK11_SUMMATION_DELIVERED_ID =
        0x070AU, /*!< CurrentNoTierBlock11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK12_SUMMATION_DELIVERED_ID =
        0x070BU, /*!< CurrentNoTierBlock12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK13_SUMMATION_DELIVERED_ID =
        0x070CU, /*!< CurrentNoTierBlock13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK14_SUMMATION_DELIVERED_ID =
        0x070DU, /*!< CurrentNoTierBlock14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK15_SUMMATION_DELIVERED_ID =
        0x070EU, /*!< CurrentNoTierBlock15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK16_SUMMATION_DELIVERED_ID =
        0x070FU, /*!< CurrentNoTierBlock16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0710U, /*!< CurrentTier1Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0711U, /*!< CurrentTier1Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0712U, /*!< CurrentTier1Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0713U, /*!< CurrentTier1Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0714U, /*!< CurrentTier1Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0715U, /*!< CurrentTier1Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0716U, /*!< CurrentTier1Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0717U, /*!< CurrentTier1Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0718U, /*!< CurrentTier1Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0719U, /*!< CurrentTier1Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK11_SUMMATION_DELIVERED_ID =
        0x071AU, /*!< CurrentTier1Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK12_SUMMATION_DELIVERED_ID =
        0x071BU, /*!< CurrentTier1Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK13_SUMMATION_DELIVERED_ID =
        0x071CU, /*!< CurrentTier1Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK14_SUMMATION_DELIVERED_ID =
        0x071DU, /*!< CurrentTier1Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK15_SUMMATION_DELIVERED_ID =
        0x071EU, /*!< CurrentTier1Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK16_SUMMATION_DELIVERED_ID =
        0x071FU, /*!< CurrentTier1Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0720U, /*!< CurrentTier2Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0721U, /*!< CurrentTier2Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0722U, /*!< CurrentTier2Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0723U, /*!< CurrentTier2Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0724U, /*!< CurrentTier2Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0725U, /*!< CurrentTier2Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0726U, /*!< CurrentTier2Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0727U, /*!< CurrentTier2Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0728U, /*!< CurrentTier2Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0729U, /*!< CurrentTier2Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK11_SUMMATION_DELIVERED_ID =
        0x072AU, /*!< CurrentTier2Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK12_SUMMATION_DELIVERED_ID =
        0x072BU, /*!< CurrentTier2Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK13_SUMMATION_DELIVERED_ID =
        0x072CU, /*!< CurrentTier2Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK14_SUMMATION_DELIVERED_ID =
        0x072DU, /*!< CurrentTier2Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK15_SUMMATION_DELIVERED_ID =
        0x072EU, /*!< CurrentTier2Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK16_SUMMATION_DELIVERED_ID =
        0x072FU, /*!< CurrentTier2Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0730U, /*!< CurrentTier3Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0731U, /*!< CurrentTier3Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0732U, /*!< CurrentTier3Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0733U, /*!< CurrentTier3Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0734U, /*!< CurrentTier3Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0735U, /*!< CurrentTier3Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0736U, /*!< CurrentTier3Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0737U, /*!< CurrentTier3Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0738U, /*!< CurrentTier3Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0739U, /*!< CurrentTier3Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK11_SUMMATION_DELIVERED_ID =
        0x073AU, /*!< CurrentTier3Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK12_SUMMATION_DELIVERED_ID =
        0x073BU, /*!< CurrentTier3Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK13_SUMMATION_DELIVERED_ID =
        0x073CU, /*!< CurrentTier3Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK14_SUMMATION_DELIVERED_ID =
        0x073DU, /*!< CurrentTier3Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK15_SUMMATION_DELIVERED_ID =
        0x073EU, /*!< CurrentTier3Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK16_SUMMATION_DELIVERED_ID =
        0x073FU, /*!< CurrentTier3Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0740U, /*!< CurrentTier4Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0741U, /*!< CurrentTier4Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0742U, /*!< CurrentTier4Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0743U, /*!< CurrentTier4Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0744U, /*!< CurrentTier4Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0745U, /*!< CurrentTier4Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0746U, /*!< CurrentTier4Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0747U, /*!< CurrentTier4Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0748U, /*!< CurrentTier4Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0749U, /*!< CurrentTier4Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK11_SUMMATION_DELIVERED_ID =
        0x074AU, /*!< CurrentTier4Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK12_SUMMATION_DELIVERED_ID =
        0x074BU, /*!< CurrentTier4Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK13_SUMMATION_DELIVERED_ID =
        0x074CU, /*!< CurrentTier4Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK14_SUMMATION_DELIVERED_ID =
        0x074DU, /*!< CurrentTier4Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK15_SUMMATION_DELIVERED_ID =
        0x074EU, /*!< CurrentTier4Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK16_SUMMATION_DELIVERED_ID =
        0x074FU, /*!< CurrentTier4Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0750U, /*!< CurrentTier5Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0751U, /*!< CurrentTier5Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0752U, /*!< CurrentTier5Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0753U, /*!< CurrentTier5Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0754U, /*!< CurrentTier5Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0755U, /*!< CurrentTier5Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0756U, /*!< CurrentTier5Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0757U, /*!< CurrentTier5Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0758U, /*!< CurrentTier5Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0759U, /*!< CurrentTier5Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK11_SUMMATION_DELIVERED_ID =
        0x075AU, /*!< CurrentTier5Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK12_SUMMATION_DELIVERED_ID =
        0x075BU, /*!< CurrentTier5Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK13_SUMMATION_DELIVERED_ID =
        0x075CU, /*!< CurrentTier5Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK14_SUMMATION_DELIVERED_ID =
        0x075DU, /*!< CurrentTier5Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK15_SUMMATION_DELIVERED_ID =
        0x075EU, /*!< CurrentTier5Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK16_SUMMATION_DELIVERED_ID =
        0x075FU, /*!< CurrentTier5Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0760U, /*!< CurrentTier6Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0761U, /*!< CurrentTier6Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0762U, /*!< CurrentTier6Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0763U, /*!< CurrentTier6Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0764U, /*!< CurrentTier6Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0765U, /*!< CurrentTier6Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0766U, /*!< CurrentTier6Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0767U, /*!< CurrentTier6Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0768U, /*!< CurrentTier6Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0769U, /*!< CurrentTier6Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK11_SUMMATION_DELIVERED_ID =
        0x076AU, /*!< CurrentTier6Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK12_SUMMATION_DELIVERED_ID =
        0x076BU, /*!< CurrentTier6Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK13_SUMMATION_DELIVERED_ID =
        0x076CU, /*!< CurrentTier6Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK14_SUMMATION_DELIVERED_ID =
        0x076DU, /*!< CurrentTier6Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK15_SUMMATION_DELIVERED_ID =
        0x076EU, /*!< CurrentTier6Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK16_SUMMATION_DELIVERED_ID =
        0x076FU, /*!< CurrentTier6Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0770U, /*!< CurrentTier7Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0771U, /*!< CurrentTier7Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0772U, /*!< CurrentTier7Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0773U, /*!< CurrentTier7Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0774U, /*!< CurrentTier7Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0775U, /*!< CurrentTier7Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0776U, /*!< CurrentTier7Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0777U, /*!< CurrentTier7Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0778U, /*!< CurrentTier7Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0779U, /*!< CurrentTier7Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK11_SUMMATION_DELIVERED_ID =
        0x077AU, /*!< CurrentTier7Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK12_SUMMATION_DELIVERED_ID =
        0x077BU, /*!< CurrentTier7Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK13_SUMMATION_DELIVERED_ID =
        0x077CU, /*!< CurrentTier7Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK14_SUMMATION_DELIVERED_ID =
        0x077DU, /*!< CurrentTier7Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK15_SUMMATION_DELIVERED_ID =
        0x077EU, /*!< CurrentTier7Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK16_SUMMATION_DELIVERED_ID =
        0x077FU, /*!< CurrentTier7Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0780U, /*!< CurrentTier8Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0781U, /*!< CurrentTier8Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0782U, /*!< CurrentTier8Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0783U, /*!< CurrentTier8Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0784U, /*!< CurrentTier8Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0785U, /*!< CurrentTier8Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0786U, /*!< CurrentTier8Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0787U, /*!< CurrentTier8Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0788U, /*!< CurrentTier8Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0789U, /*!< CurrentTier8Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK11_SUMMATION_DELIVERED_ID =
        0x078AU, /*!< CurrentTier8Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK12_SUMMATION_DELIVERED_ID =
        0x078BU, /*!< CurrentTier8Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK13_SUMMATION_DELIVERED_ID =
        0x078CU, /*!< CurrentTier8Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK14_SUMMATION_DELIVERED_ID =
        0x078DU, /*!< CurrentTier8Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK15_SUMMATION_DELIVERED_ID =
        0x078EU, /*!< CurrentTier8Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK16_SUMMATION_DELIVERED_ID =
        0x078FU, /*!< CurrentTier8Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK1_SUMMATION_DELIVERED_ID =
        0x0790U, /*!< CurrentTier9Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK2_SUMMATION_DELIVERED_ID =
        0x0791U, /*!< CurrentTier9Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK3_SUMMATION_DELIVERED_ID =
        0x0792U, /*!< CurrentTier9Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK4_SUMMATION_DELIVERED_ID =
        0x0793U, /*!< CurrentTier9Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK5_SUMMATION_DELIVERED_ID =
        0x0794U, /*!< CurrentTier9Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK6_SUMMATION_DELIVERED_ID =
        0x0795U, /*!< CurrentTier9Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK7_SUMMATION_DELIVERED_ID =
        0x0796U, /*!< CurrentTier9Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK8_SUMMATION_DELIVERED_ID =
        0x0797U, /*!< CurrentTier9Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK9_SUMMATION_DELIVERED_ID =
        0x0798U, /*!< CurrentTier9Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK10_SUMMATION_DELIVERED_ID =
        0x0799U, /*!< CurrentTier9Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK11_SUMMATION_DELIVERED_ID =
        0x079AU, /*!< CurrentTier9Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK12_SUMMATION_DELIVERED_ID =
        0x079BU, /*!< CurrentTier9Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK13_SUMMATION_DELIVERED_ID =
        0x079CU, /*!< CurrentTier9Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK14_SUMMATION_DELIVERED_ID =
        0x079DU, /*!< CurrentTier9Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK15_SUMMATION_DELIVERED_ID =
        0x079EU, /*!< CurrentTier9Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK16_SUMMATION_DELIVERED_ID =
        0x079FU, /*!< CurrentTier9Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK1_SUMMATION_DELIVERED_ID =
        0x07A0U, /*!< CurrentTier10Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK2_SUMMATION_DELIVERED_ID =
        0x07A1U, /*!< CurrentTier10Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK3_SUMMATION_DELIVERED_ID =
        0x07A2U, /*!< CurrentTier10Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK4_SUMMATION_DELIVERED_ID =
        0x07A3U, /*!< CurrentTier10Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK5_SUMMATION_DELIVERED_ID =
        0x07A4U, /*!< CurrentTier10Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK6_SUMMATION_DELIVERED_ID =
        0x07A5U, /*!< CurrentTier10Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK7_SUMMATION_DELIVERED_ID =
        0x07A6U, /*!< CurrentTier10Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK8_SUMMATION_DELIVERED_ID =
        0x07A7U, /*!< CurrentTier10Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK9_SUMMATION_DELIVERED_ID =
        0x07A8U, /*!< CurrentTier10Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK10_SUMMATION_DELIVERED_ID =
        0x07A9U, /*!< CurrentTier10Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK11_SUMMATION_DELIVERED_ID =
        0x07AAU, /*!< CurrentTier10Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK12_SUMMATION_DELIVERED_ID =
        0x07ABU, /*!< CurrentTier10Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK13_SUMMATION_DELIVERED_ID =
        0x07ACU, /*!< CurrentTier10Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK14_SUMMATION_DELIVERED_ID =
        0x07ADU, /*!< CurrentTier10Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK15_SUMMATION_DELIVERED_ID =
        0x07AEU, /*!< CurrentTier10Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK16_SUMMATION_DELIVERED_ID =
        0x07AFU, /*!< CurrentTier10Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK1_SUMMATION_DELIVERED_ID =
        0x07B0U, /*!< CurrentTier11Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK2_SUMMATION_DELIVERED_ID =
        0x07B1U, /*!< CurrentTier11Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK3_SUMMATION_DELIVERED_ID =
        0x07B2U, /*!< CurrentTier11Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK4_SUMMATION_DELIVERED_ID =
        0x07B3U, /*!< CurrentTier11Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK5_SUMMATION_DELIVERED_ID =
        0x07B4U, /*!< CurrentTier11Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK6_SUMMATION_DELIVERED_ID =
        0x07B5U, /*!< CurrentTier11Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK7_SUMMATION_DELIVERED_ID =
        0x07B6U, /*!< CurrentTier11Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK8_SUMMATION_DELIVERED_ID =
        0x07B7U, /*!< CurrentTier11Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK9_SUMMATION_DELIVERED_ID =
        0x07B8U, /*!< CurrentTier11Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK10_SUMMATION_DELIVERED_ID =
        0x07B9U, /*!< CurrentTier11Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK11_SUMMATION_DELIVERED_ID =
        0x07BAU, /*!< CurrentTier11Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK12_SUMMATION_DELIVERED_ID =
        0x07BBU, /*!< CurrentTier11Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK13_SUMMATION_DELIVERED_ID =
        0x07BCU, /*!< CurrentTier11Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK14_SUMMATION_DELIVERED_ID =
        0x07BDU, /*!< CurrentTier11Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK15_SUMMATION_DELIVERED_ID =
        0x07BEU, /*!< CurrentTier11Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK16_SUMMATION_DELIVERED_ID =
        0x07BFU, /*!< CurrentTier11Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK1_SUMMATION_DELIVERED_ID =
        0x07C0U, /*!< CurrentTier12Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK2_SUMMATION_DELIVERED_ID =
        0x07C1U, /*!< CurrentTier12Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK3_SUMMATION_DELIVERED_ID =
        0x07C2U, /*!< CurrentTier12Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK4_SUMMATION_DELIVERED_ID =
        0x07C3U, /*!< CurrentTier12Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK5_SUMMATION_DELIVERED_ID =
        0x07C4U, /*!< CurrentTier12Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK6_SUMMATION_DELIVERED_ID =
        0x07C5U, /*!< CurrentTier12Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK7_SUMMATION_DELIVERED_ID =
        0x07C6U, /*!< CurrentTier12Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK8_SUMMATION_DELIVERED_ID =
        0x07C7U, /*!< CurrentTier12Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK9_SUMMATION_DELIVERED_ID =
        0x07C8U, /*!< CurrentTier12Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK10_SUMMATION_DELIVERED_ID =
        0x07C9U, /*!< CurrentTier12Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK11_SUMMATION_DELIVERED_ID =
        0x07CAU, /*!< CurrentTier12Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK12_SUMMATION_DELIVERED_ID =
        0x07CBU, /*!< CurrentTier12Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK13_SUMMATION_DELIVERED_ID =
        0x07CCU, /*!< CurrentTier12Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK14_SUMMATION_DELIVERED_ID =
        0x07CDU, /*!< CurrentTier12Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK15_SUMMATION_DELIVERED_ID =
        0x07CEU, /*!< CurrentTier12Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK16_SUMMATION_DELIVERED_ID =
        0x07CFU, /*!< CurrentTier12Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK1_SUMMATION_DELIVERED_ID =
        0x07D0U, /*!< CurrentTier13Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK2_SUMMATION_DELIVERED_ID =
        0x07D1U, /*!< CurrentTier13Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK3_SUMMATION_DELIVERED_ID =
        0x07D2U, /*!< CurrentTier13Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK4_SUMMATION_DELIVERED_ID =
        0x07D3U, /*!< CurrentTier13Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK5_SUMMATION_DELIVERED_ID =
        0x07D4U, /*!< CurrentTier13Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK6_SUMMATION_DELIVERED_ID =
        0x07D5U, /*!< CurrentTier13Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK7_SUMMATION_DELIVERED_ID =
        0x07D6U, /*!< CurrentTier13Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK8_SUMMATION_DELIVERED_ID =
        0x07D7U, /*!< CurrentTier13Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK9_SUMMATION_DELIVERED_ID =
        0x07D8U, /*!< CurrentTier13Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK10_SUMMATION_DELIVERED_ID =
        0x07D9U, /*!< CurrentTier13Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK11_SUMMATION_DELIVERED_ID =
        0x07DAU, /*!< CurrentTier13Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK12_SUMMATION_DELIVERED_ID =
        0x07DBU, /*!< CurrentTier13Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK13_SUMMATION_DELIVERED_ID =
        0x07DCU, /*!< CurrentTier13Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK14_SUMMATION_DELIVERED_ID =
        0x07DDU, /*!< CurrentTier13Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK15_SUMMATION_DELIVERED_ID =
        0x07DEU, /*!< CurrentTier13Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK16_SUMMATION_DELIVERED_ID =
        0x07DFU, /*!< CurrentTier13Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK1_SUMMATION_DELIVERED_ID =
        0x07E0U, /*!< CurrentTier14Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK2_SUMMATION_DELIVERED_ID =
        0x07E1U, /*!< CurrentTier14Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK3_SUMMATION_DELIVERED_ID =
        0x07E2U, /*!< CurrentTier14Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK4_SUMMATION_DELIVERED_ID =
        0x07E3U, /*!< CurrentTier14Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK5_SUMMATION_DELIVERED_ID =
        0x07E4U, /*!< CurrentTier14Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK6_SUMMATION_DELIVERED_ID =
        0x07E5U, /*!< CurrentTier14Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK7_SUMMATION_DELIVERED_ID =
        0x07E6U, /*!< CurrentTier14Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK8_SUMMATION_DELIVERED_ID =
        0x07E7U, /*!< CurrentTier14Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK9_SUMMATION_DELIVERED_ID =
        0x07E8U, /*!< CurrentTier14Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK10_SUMMATION_DELIVERED_ID =
        0x07E9U, /*!< CurrentTier14Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK11_SUMMATION_DELIVERED_ID =
        0x07EAU, /*!< CurrentTier14Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK12_SUMMATION_DELIVERED_ID =
        0x07EBU, /*!< CurrentTier14Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK13_SUMMATION_DELIVERED_ID =
        0x07ECU, /*!< CurrentTier14Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK14_SUMMATION_DELIVERED_ID =
        0x07EDU, /*!< CurrentTier14Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK15_SUMMATION_DELIVERED_ID =
        0x07EEU, /*!< CurrentTier14Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK16_SUMMATION_DELIVERED_ID =
        0x07EFU, /*!< CurrentTier14Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK1_SUMMATION_DELIVERED_ID =
        0x07F0U, /*!< CurrentTier15Block1SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK2_SUMMATION_DELIVERED_ID =
        0x07F1U, /*!< CurrentTier15Block2SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK3_SUMMATION_DELIVERED_ID =
        0x07F2U, /*!< CurrentTier15Block3SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK4_SUMMATION_DELIVERED_ID =
        0x07F3U, /*!< CurrentTier15Block4SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK5_SUMMATION_DELIVERED_ID =
        0x07F4U, /*!< CurrentTier15Block5SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK6_SUMMATION_DELIVERED_ID =
        0x07F5U, /*!< CurrentTier15Block6SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK7_SUMMATION_DELIVERED_ID =
        0x07F6U, /*!< CurrentTier15Block7SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK8_SUMMATION_DELIVERED_ID =
        0x07F7U, /*!< CurrentTier15Block8SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK9_SUMMATION_DELIVERED_ID =
        0x07F8U, /*!< CurrentTier15Block9SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK10_SUMMATION_DELIVERED_ID =
        0x07F9U, /*!< CurrentTier15Block10SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK11_SUMMATION_DELIVERED_ID =
        0x07FAU, /*!< CurrentTier15Block11SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK12_SUMMATION_DELIVERED_ID =
        0x07FBU, /*!< CurrentTier15Block12SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK13_SUMMATION_DELIVERED_ID =
        0x07FCU, /*!< CurrentTier15Block13SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK14_SUMMATION_DELIVERED_ID =
        0x07FDU, /*!< CurrentTier15Block14SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK15_SUMMATION_DELIVERED_ID =
        0x07FEU, /*!< CurrentTier15Block15SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK16_SUMMATION_DELIVERED_ID =
        0x07FFU, /*!< CurrentTier15Block16SummationDelivered attribute. */
    EZB_ZCL_ATTR_METERING_GENERIC_ALARM_MASK_ID                   = 0x0800U, /*!< GenericAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_ELECTRICITY_ALARM_MASK_ID               = 0x0801U, /*!< ElectricityAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_GENERIC_FLOW_PRESSURE_ALARM_MASK_ID     = 0x0802U, /*!< GenericFlowPressureAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_WATER_SPECIFIC_ALARM_MASK_ID            = 0x0803U, /*!< WaterSpecificAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_HEAT_AND_COOLING_SPECIFIC_ALARM_MASK_ID = 0x0804U, /*!< HeatAndCoolingSpecificAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_GAS_SPECIFIC_ALARM_MASK_ID              = 0x0805U, /*!< GasSpecificAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_EXTENDED_GENERIC_ALARM_MASK_ID          = 0x0806U, /*!< ExtendedGenericAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_MANUFACTURER_ALARM_MASK_ID              = 0x0807U, /*!< ManufacturerAlarmMask attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0900U, /*!< CurrentNoTierBlock1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0901U, /*!< CurrentNoTierBlock2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0902U, /*!< CurrentNoTierBlock3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0903U, /*!< CurrentNoTierBlock4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0904U, /*!< CurrentNoTierBlock5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0905U, /*!< CurrentNoTierBlock6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0906U, /*!< CurrentNoTierBlock7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0907U, /*!< CurrentNoTierBlock8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0908U, /*!< CurrentNoTierBlock9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0909U, /*!< CurrentNoTierBlock10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK11_SUMMATION_RECEIVED_ID =
        0x090AU, /*!< CurrentNoTierBlock11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK12_SUMMATION_RECEIVED_ID =
        0x090BU, /*!< CurrentNoTierBlock12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK13_SUMMATION_RECEIVED_ID =
        0x090CU, /*!< CurrentNoTierBlock13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK14_SUMMATION_RECEIVED_ID =
        0x090DU, /*!< CurrentNoTierBlock14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK15_SUMMATION_RECEIVED_ID =
        0x090EU, /*!< CurrentNoTierBlock15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_NO_TIER_BLOCK16_SUMMATION_RECEIVED_ID =
        0x090FU, /*!< CurrentNoTierBlock16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0910U, /*!< CurrentTier1Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0911U, /*!< CurrentTier1Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0912U, /*!< CurrentTier1Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0913U, /*!< CurrentTier1Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0914U, /*!< CurrentTier1Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0915U, /*!< CurrentTier1Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0916U, /*!< CurrentTier1Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0917U, /*!< CurrentTier1Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0918U, /*!< CurrentTier1Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0919U, /*!< CurrentTier1Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK11_SUMMATION_RECEIVED_ID =
        0x091AU, /*!< CurrentTier1Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK12_SUMMATION_RECEIVED_ID =
        0x091BU, /*!< CurrentTier1Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK13_SUMMATION_RECEIVED_ID =
        0x091CU, /*!< CurrentTier1Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK14_SUMMATION_RECEIVED_ID =
        0x091DU, /*!< CurrentTier1Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK15_SUMMATION_RECEIVED_ID =
        0x091EU, /*!< CurrentTier1Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER1_BLOCK16_SUMMATION_RECEIVED_ID =
        0x091FU, /*!< CurrentTier1Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0920U, /*!< CurrentTier2Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0921U, /*!< CurrentTier2Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0922U, /*!< CurrentTier2Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0923U, /*!< CurrentTier2Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0924U, /*!< CurrentTier2Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0925U, /*!< CurrentTier2Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0926U, /*!< CurrentTier2Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0927U, /*!< CurrentTier2Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0928U, /*!< CurrentTier2Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0929U, /*!< CurrentTier2Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK11_SUMMATION_RECEIVED_ID =
        0x092AU, /*!< CurrentTier2Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK12_SUMMATION_RECEIVED_ID =
        0x092BU, /*!< CurrentTier2Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK13_SUMMATION_RECEIVED_ID =
        0x092CU, /*!< CurrentTier2Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK14_SUMMATION_RECEIVED_ID =
        0x092DU, /*!< CurrentTier2Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK15_SUMMATION_RECEIVED_ID =
        0x092EU, /*!< CurrentTier2Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER2_BLOCK16_SUMMATION_RECEIVED_ID =
        0x092FU, /*!< CurrentTier2Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0930U, /*!< CurrentTier3Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0931U, /*!< CurrentTier3Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0932U, /*!< CurrentTier3Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0933U, /*!< CurrentTier3Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0934U, /*!< CurrentTier3Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0935U, /*!< CurrentTier3Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0936U, /*!< CurrentTier3Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0937U, /*!< CurrentTier3Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0938U, /*!< CurrentTier3Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0939U, /*!< CurrentTier3Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK11_SUMMATION_RECEIVED_ID =
        0x093AU, /*!< CurrentTier3Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK12_SUMMATION_RECEIVED_ID =
        0x093BU, /*!< CurrentTier3Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK13_SUMMATION_RECEIVED_ID =
        0x093CU, /*!< CurrentTier3Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK14_SUMMATION_RECEIVED_ID =
        0x093DU, /*!< CurrentTier3Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK15_SUMMATION_RECEIVED_ID =
        0x093EU, /*!< CurrentTier3Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER3_BLOCK16_SUMMATION_RECEIVED_ID =
        0x093FU, /*!< CurrentTier3Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0940U, /*!< CurrentTier4Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0941U, /*!< CurrentTier4Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0942U, /*!< CurrentTier4Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0943U, /*!< CurrentTier4Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0944U, /*!< CurrentTier4Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0945U, /*!< CurrentTier4Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0946U, /*!< CurrentTier4Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0947U, /*!< CurrentTier4Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0948U, /*!< CurrentTier4Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0949U, /*!< CurrentTier4Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK11_SUMMATION_RECEIVED_ID =
        0x094AU, /*!< CurrentTier4Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK12_SUMMATION_RECEIVED_ID =
        0x094BU, /*!< CurrentTier4Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK13_SUMMATION_RECEIVED_ID =
        0x094CU, /*!< CurrentTier4Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK14_SUMMATION_RECEIVED_ID =
        0x094DU, /*!< CurrentTier4Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK15_SUMMATION_RECEIVED_ID =
        0x094EU, /*!< CurrentTier4Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER4_BLOCK16_SUMMATION_RECEIVED_ID =
        0x094FU, /*!< CurrentTier4Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0950U, /*!< CurrentTier5Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0951U, /*!< CurrentTier5Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0952U, /*!< CurrentTier5Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0953U, /*!< CurrentTier5Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0954U, /*!< CurrentTier5Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0955U, /*!< CurrentTier5Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0956U, /*!< CurrentTier5Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0957U, /*!< CurrentTier5Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0958U, /*!< CurrentTier5Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0959U, /*!< CurrentTier5Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK11_SUMMATION_RECEIVED_ID =
        0x095AU, /*!< CurrentTier5Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK12_SUMMATION_RECEIVED_ID =
        0x095BU, /*!< CurrentTier5Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK13_SUMMATION_RECEIVED_ID =
        0x095CU, /*!< CurrentTier5Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK14_SUMMATION_RECEIVED_ID =
        0x095DU, /*!< CurrentTier5Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK15_SUMMATION_RECEIVED_ID =
        0x095EU, /*!< CurrentTier5Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER5_BLOCK16_SUMMATION_RECEIVED_ID =
        0x095FU, /*!< CurrentTier5Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0960U, /*!< CurrentTier6Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0961U, /*!< CurrentTier6Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0962U, /*!< CurrentTier6Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0963U, /*!< CurrentTier6Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0964U, /*!< CurrentTier6Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0965U, /*!< CurrentTier6Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0966U, /*!< CurrentTier6Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0967U, /*!< CurrentTier6Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0968U, /*!< CurrentTier6Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0969U, /*!< CurrentTier6Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK11_SUMMATION_RECEIVED_ID =
        0x096AU, /*!< CurrentTier6Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK12_SUMMATION_RECEIVED_ID =
        0x096BU, /*!< CurrentTier6Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK13_SUMMATION_RECEIVED_ID =
        0x096CU, /*!< CurrentTier6Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK14_SUMMATION_RECEIVED_ID =
        0x096DU, /*!< CurrentTier6Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK15_SUMMATION_RECEIVED_ID =
        0x096EU, /*!< CurrentTier6Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER6_BLOCK16_SUMMATION_RECEIVED_ID =
        0x096FU, /*!< CurrentTier6Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0970U, /*!< CurrentTier7Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0971U, /*!< CurrentTier7Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0972U, /*!< CurrentTier7Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0973U, /*!< CurrentTier7Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0974U, /*!< CurrentTier7Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0975U, /*!< CurrentTier7Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0976U, /*!< CurrentTier7Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0977U, /*!< CurrentTier7Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0978U, /*!< CurrentTier7Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0979U, /*!< CurrentTier7Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK11_SUMMATION_RECEIVED_ID =
        0x097AU, /*!< CurrentTier7Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK12_SUMMATION_RECEIVED_ID =
        0x097BU, /*!< CurrentTier7Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK13_SUMMATION_RECEIVED_ID =
        0x097CU, /*!< CurrentTier7Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK14_SUMMATION_RECEIVED_ID =
        0x097DU, /*!< CurrentTier7Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK15_SUMMATION_RECEIVED_ID =
        0x097EU, /*!< CurrentTier7Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER7_BLOCK16_SUMMATION_RECEIVED_ID =
        0x097FU, /*!< CurrentTier7Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0980U, /*!< CurrentTier8Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0981U, /*!< CurrentTier8Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0982U, /*!< CurrentTier8Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0983U, /*!< CurrentTier8Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0984U, /*!< CurrentTier8Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0985U, /*!< CurrentTier8Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0986U, /*!< CurrentTier8Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0987U, /*!< CurrentTier8Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0988U, /*!< CurrentTier8Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0989U, /*!< CurrentTier8Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK11_SUMMATION_RECEIVED_ID =
        0x098AU, /*!< CurrentTier8Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK12_SUMMATION_RECEIVED_ID =
        0x098BU, /*!< CurrentTier8Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK13_SUMMATION_RECEIVED_ID =
        0x098CU, /*!< CurrentTier8Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK14_SUMMATION_RECEIVED_ID =
        0x098DU, /*!< CurrentTier8Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK15_SUMMATION_RECEIVED_ID =
        0x098EU, /*!< CurrentTier8Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER8_BLOCK16_SUMMATION_RECEIVED_ID =
        0x098FU, /*!< CurrentTier8Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK1_SUMMATION_RECEIVED_ID =
        0x0990U, /*!< CurrentTier9Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK2_SUMMATION_RECEIVED_ID =
        0x0991U, /*!< CurrentTier9Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK3_SUMMATION_RECEIVED_ID =
        0x0992U, /*!< CurrentTier9Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK4_SUMMATION_RECEIVED_ID =
        0x0993U, /*!< CurrentTier9Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK5_SUMMATION_RECEIVED_ID =
        0x0994U, /*!< CurrentTier9Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK6_SUMMATION_RECEIVED_ID =
        0x0995U, /*!< CurrentTier9Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK7_SUMMATION_RECEIVED_ID =
        0x0996U, /*!< CurrentTier9Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK8_SUMMATION_RECEIVED_ID =
        0x0997U, /*!< CurrentTier9Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK9_SUMMATION_RECEIVED_ID =
        0x0998U, /*!< CurrentTier9Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK10_SUMMATION_RECEIVED_ID =
        0x0999U, /*!< CurrentTier9Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK11_SUMMATION_RECEIVED_ID =
        0x099AU, /*!< CurrentTier9Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK12_SUMMATION_RECEIVED_ID =
        0x099BU, /*!< CurrentTier9Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK13_SUMMATION_RECEIVED_ID =
        0x099CU, /*!< CurrentTier9Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK14_SUMMATION_RECEIVED_ID =
        0x099DU, /*!< CurrentTier9Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK15_SUMMATION_RECEIVED_ID =
        0x099EU, /*!< CurrentTier9Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER9_BLOCK16_SUMMATION_RECEIVED_ID =
        0x099FU, /*!< CurrentTier9Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK1_SUMMATION_RECEIVED_ID =
        0x09A0U, /*!< CurrentTier10Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK2_SUMMATION_RECEIVED_ID =
        0x09A1U, /*!< CurrentTier10Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK3_SUMMATION_RECEIVED_ID =
        0x09A2U, /*!< CurrentTier10Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK4_SUMMATION_RECEIVED_ID =
        0x09A3U, /*!< CurrentTier10Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK5_SUMMATION_RECEIVED_ID =
        0x09A4U, /*!< CurrentTier10Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK6_SUMMATION_RECEIVED_ID =
        0x09A5U, /*!< CurrentTier10Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK7_SUMMATION_RECEIVED_ID =
        0x09A6U, /*!< CurrentTier10Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK8_SUMMATION_RECEIVED_ID =
        0x09A7U, /*!< CurrentTier10Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK9_SUMMATION_RECEIVED_ID =
        0x09A8U, /*!< CurrentTier10Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK10_SUMMATION_RECEIVED_ID =
        0x09A9U, /*!< CurrentTier10Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK11_SUMMATION_RECEIVED_ID =
        0x09AAU, /*!< CurrentTier10Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK12_SUMMATION_RECEIVED_ID =
        0x09ABU, /*!< CurrentTier10Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK13_SUMMATION_RECEIVED_ID =
        0x09ACU, /*!< CurrentTier10Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK14_SUMMATION_RECEIVED_ID =
        0x09ADU, /*!< CurrentTier10Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK15_SUMMATION_RECEIVED_ID =
        0x09AEU, /*!< CurrentTier10Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER10_BLOCK16_SUMMATION_RECEIVED_ID =
        0x09AFU, /*!< CurrentTier10Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK1_SUMMATION_RECEIVED_ID =
        0x09B0U, /*!< CurrentTier11Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK2_SUMMATION_RECEIVED_ID =
        0x09B1U, /*!< CurrentTier11Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK3_SUMMATION_RECEIVED_ID =
        0x09B2U, /*!< CurrentTier11Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK4_SUMMATION_RECEIVED_ID =
        0x09B3U, /*!< CurrentTier11Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK5_SUMMATION_RECEIVED_ID =
        0x09B4U, /*!< CurrentTier11Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK6_SUMMATION_RECEIVED_ID =
        0x09B5U, /*!< CurrentTier11Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK7_SUMMATION_RECEIVED_ID =
        0x09B6U, /*!< CurrentTier11Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK8_SUMMATION_RECEIVED_ID =
        0x09B7U, /*!< CurrentTier11Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK9_SUMMATION_RECEIVED_ID =
        0x09B8U, /*!< CurrentTier11Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK10_SUMMATION_RECEIVED_ID =
        0x09B9U, /*!< CurrentTier11Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK11_SUMMATION_RECEIVED_ID =
        0x09BAU, /*!< CurrentTier11Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK12_SUMMATION_RECEIVED_ID =
        0x09BBU, /*!< CurrentTier11Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK13_SUMMATION_RECEIVED_ID =
        0x09BCU, /*!< CurrentTier11Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK14_SUMMATION_RECEIVED_ID =
        0x09BDU, /*!< CurrentTier11Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK15_SUMMATION_RECEIVED_ID =
        0x09BEU, /*!< CurrentTier11Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER11_BLOCK16_SUMMATION_RECEIVED_ID =
        0x09BFU, /*!< CurrentTier11Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK1_SUMMATION_RECEIVED_ID =
        0x09C0U, /*!< CurrentTier12Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK2_SUMMATION_RECEIVED_ID =
        0x09C1U, /*!< CurrentTier12Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK3_SUMMATION_RECEIVED_ID =
        0x09C2U, /*!< CurrentTier12Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK4_SUMMATION_RECEIVED_ID =
        0x09C3U, /*!< CurrentTier12Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK5_SUMMATION_RECEIVED_ID =
        0x09C4U, /*!< CurrentTier12Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK6_SUMMATION_RECEIVED_ID =
        0x09C5U, /*!< CurrentTier12Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK7_SUMMATION_RECEIVED_ID =
        0x09C6U, /*!< CurrentTier12Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK8_SUMMATION_RECEIVED_ID =
        0x09C7U, /*!< CurrentTier12Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK9_SUMMATION_RECEIVED_ID =
        0x09C8U, /*!< CurrentTier12Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK10_SUMMATION_RECEIVED_ID =
        0x09C9U, /*!< CurrentTier12Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK11_SUMMATION_RECEIVED_ID =
        0x09CAU, /*!< CurrentTier12Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK12_SUMMATION_RECEIVED_ID =
        0x09CBU, /*!< CurrentTier12Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK13_SUMMATION_RECEIVED_ID =
        0x09CCU, /*!< CurrentTier12Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK14_SUMMATION_RECEIVED_ID =
        0x09CDU, /*!< CurrentTier12Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK15_SUMMATION_RECEIVED_ID =
        0x09CEU, /*!< CurrentTier12Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER12_BLOCK16_SUMMATION_RECEIVED_ID =
        0x09CFU, /*!< CurrentTier12Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK1_SUMMATION_RECEIVED_ID =
        0x09D0U, /*!< CurrentTier13Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK2_SUMMATION_RECEIVED_ID =
        0x09D1U, /*!< CurrentTier13Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK3_SUMMATION_RECEIVED_ID =
        0x09D2U, /*!< CurrentTier13Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK4_SUMMATION_RECEIVED_ID =
        0x09D3U, /*!< CurrentTier13Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK5_SUMMATION_RECEIVED_ID =
        0x09D4U, /*!< CurrentTier13Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK6_SUMMATION_RECEIVED_ID =
        0x09D5U, /*!< CurrentTier13Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK7_SUMMATION_RECEIVED_ID =
        0x09D6U, /*!< CurrentTier13Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK8_SUMMATION_RECEIVED_ID =
        0x09D7U, /*!< CurrentTier13Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK9_SUMMATION_RECEIVED_ID =
        0x09D8U, /*!< CurrentTier13Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK10_SUMMATION_RECEIVED_ID =
        0x09D9U, /*!< CurrentTier13Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK11_SUMMATION_RECEIVED_ID =
        0x09DAU, /*!< CurrentTier13Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK12_SUMMATION_RECEIVED_ID =
        0x09DBU, /*!< CurrentTier13Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK13_SUMMATION_RECEIVED_ID =
        0x09DCU, /*!< CurrentTier13Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK14_SUMMATION_RECEIVED_ID =
        0x09DDU, /*!< CurrentTier13Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK15_SUMMATION_RECEIVED_ID =
        0x09DEU, /*!< CurrentTier13Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER13_BLOCK16_SUMMATION_RECEIVED_ID =
        0x09DFU, /*!< CurrentTier13Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK1_SUMMATION_RECEIVED_ID =
        0x09E0U, /*!< CurrentTier14Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK2_SUMMATION_RECEIVED_ID =
        0x09E1U, /*!< CurrentTier14Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK3_SUMMATION_RECEIVED_ID =
        0x09E2U, /*!< CurrentTier14Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK4_SUMMATION_RECEIVED_ID =
        0x09E3U, /*!< CurrentTier14Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK5_SUMMATION_RECEIVED_ID =
        0x09E4U, /*!< CurrentTier14Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK6_SUMMATION_RECEIVED_ID =
        0x09E5U, /*!< CurrentTier14Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK7_SUMMATION_RECEIVED_ID =
        0x09E6U, /*!< CurrentTier14Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK8_SUMMATION_RECEIVED_ID =
        0x09E7U, /*!< CurrentTier14Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK9_SUMMATION_RECEIVED_ID =
        0x09E8U, /*!< CurrentTier14Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK10_SUMMATION_RECEIVED_ID =
        0x09E9U, /*!< CurrentTier14Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK11_SUMMATION_RECEIVED_ID =
        0x09EAU, /*!< CurrentTier14Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK12_SUMMATION_RECEIVED_ID =
        0x09EBU, /*!< CurrentTier14Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK13_SUMMATION_RECEIVED_ID =
        0x09ECU, /*!< CurrentTier14Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK14_SUMMATION_RECEIVED_ID =
        0x09EDU, /*!< CurrentTier14Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK15_SUMMATION_RECEIVED_ID =
        0x09EEU, /*!< CurrentTier14Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER14_BLOCK16_SUMMATION_RECEIVED_ID =
        0x09EFU, /*!< CurrentTier14Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK1_SUMMATION_RECEIVED_ID =
        0x09F0U, /*!< CurrentTier15Block1SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK2_SUMMATION_RECEIVED_ID =
        0x09F1U, /*!< CurrentTier15Block2SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK3_SUMMATION_RECEIVED_ID =
        0x09F2U, /*!< CurrentTier15Block3SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK4_SUMMATION_RECEIVED_ID =
        0x09F3U, /*!< CurrentTier15Block4SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK5_SUMMATION_RECEIVED_ID =
        0x09F4U, /*!< CurrentTier15Block5SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK6_SUMMATION_RECEIVED_ID =
        0x09F5U, /*!< CurrentTier15Block6SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK7_SUMMATION_RECEIVED_ID =
        0x09F6U, /*!< CurrentTier15Block7SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK8_SUMMATION_RECEIVED_ID =
        0x09F7U, /*!< CurrentTier15Block8SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK9_SUMMATION_RECEIVED_ID =
        0x09F8U, /*!< CurrentTier15Block9SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK10_SUMMATION_RECEIVED_ID =
        0x09F9U, /*!< CurrentTier15Block10SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK11_SUMMATION_RECEIVED_ID =
        0x09FAU, /*!< CurrentTier15Block11SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK12_SUMMATION_RECEIVED_ID =
        0x09FBU, /*!< CurrentTier15Block12SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK13_SUMMATION_RECEIVED_ID =
        0x09FCU, /*!< CurrentTier15Block13SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK14_SUMMATION_RECEIVED_ID =
        0x09FDU, /*!< CurrentTier15Block14SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK15_SUMMATION_RECEIVED_ID =
        0x09FEU, /*!< CurrentTier15Block15SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_TIER15_BLOCK16_SUMMATION_RECEIVED_ID =
        0x09FFU, /*!< CurrentTier15Block16SummationReceived attribute. */
    EZB_ZCL_ATTR_METERING_BILL_TO_DATE_DELIVERED_ID              = 0x0A00U, /*!< BillToDateDelivered attribute. */
    EZB_ZCL_ATTR_METERING_BILL_TO_DATE_TIME_STAMP_DELIVERED_ID   = 0x0A01U, /*!< BillToDateTimeStampDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PROJECTED_BILL_DELIVERED_ID            = 0x0A02U, /*!< ProjectedBillDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PROJECTED_BILL_TIME_STAMP_DELIVERED_ID = 0x0A03U, /*!< ProjectedBillTimeStampDelivered attribute. */
    EZB_ZCL_ATTR_METERING_BILL_DELIVERED_TRAILING_DIGIT_MAP_ID   = 0x0A04U, /*!< BillDeliveredTrailingDigitMap attribute. */
    EZB_ZCL_ATTR_METERING_BILL_TO_DATE_RECEIVED_ID               = 0x0A10U, /*!< BillToDateReceived attribute. */
    EZB_ZCL_ATTR_METERING_BILL_TO_DATE_TIME_STAMP_RECEIVED_ID    = 0x0A11U, /*!< BillToDateTimeStampReceived attribute. */
    EZB_ZCL_ATTR_METERING_PROJECTED_BILL_RECEIVED_ID             = 0x0A12U, /*!< ProjectedBillReceived attribute. */
    EZB_ZCL_ATTR_METERING_PROJECTED_BILL_TIME_STAMP_RECEIVED_ID  = 0x0A13U, /*!< ProjectedBillTimeStampReceived attribute. */
    EZB_ZCL_ATTR_METERING_BILL_RECEIVED_TRAILING_DIGIT_MAP_ID    = 0x0A14U, /*!< BillReceivedTrailingDigitMap attribute. */
    EZB_ZCL_ATTR_METERING_PROPOSED_CHANGE_SUPPLY_IMPLEMENTATION_TIME_ID =
        0x0B00U,                                                      /*!< ProposedChangeSupplyImplementationTime attribute. */
    EZB_ZCL_ATTR_METERING_PROPOSED_CHANGE_SUPPLY_STATUS_ID = 0x0B01U, /*!< ProposedChangeSupplyStatus attribute. */
    EZB_ZCL_ATTR_METERING_UNCONTROLLED_FLOW_THRESHOLD_ID   = 0x0B10U, /*!< UncontrolledFlowThreshold attribute. */
    EZB_ZCL_ATTR_METERING_UNCONTROLLED_FLOW_THRESHOLD_UNIT_OF_MEASURE_ID =
        0x0B11U, /*!< UncontrolledFlowThresholdUnitOfMeasure attribute. */
    EZB_ZCL_ATTR_METERING_UNCONTROLLED_FLOW_MULTIPLIER_ID     = 0x0B12U, /*!< UncontrolledFlowMultiplier attribute. */
    EZB_ZCL_ATTR_METERING_UNCONTROLLED_FLOW_DIVISOR_ID        = 0x0B13U, /*!< UncontrolledFlowDivisor attribute. */
    EZB_ZCL_ATTR_METERING_FLOW_STABILISATION_PERIOD_ID        = 0x0B14U, /*!< FlowStabilisationPeriod attribute. */
    EZB_ZCL_ATTR_METERING_FLOW_MEASUREMENT_PERIOD_ID          = 0x0B15U, /*!< FlowMeasurementPeriod attribute. */
    EZB_ZCL_ATTR_METERING_ALTERNATIVE_INSTANTANEOUS_DEMAND_ID = 0x0C00U, /*!< AlternativeInstantaneousDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C01U, /*!< CurrentDayAlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C02U, /*!< CurrentDayAlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C03U, /*!< PreviousDayAlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C04U, /*!< PreviousDayAlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_ALTERNATIVE_PARTIAL_PROFILE_INTERVAL_START_TIME_DELIVERED_ID =
        0x0C05U, /*!< CurrentAlternativePartialProfileIntervalStartTimeDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_ALTERNATIVE_PARTIAL_PROFILE_INTERVAL_START_TIME_RECEIVED_ID =
        0x0C06U, /*!< CurrentAlternativePartialProfileIntervalStartTimeReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_ALTERNATIVE_PARTIAL_PROFILE_INTERVAL_VALUE_DELIVERED_ID =
        0x0C07U, /*!< CurrentAlternativePartialProfileIntervalValueDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_ALTERNATIVE_PARTIAL_PROFILE_INTERVAL_VALUE_RECEIVED_ID =
        0x0C08U, /*!< CurrentAlternativePartialProfileIntervalValueReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_ALTERNATIVE_MAX_PRESSURE_ID = 0x0C09U, /*!< CurrentDayAlternativeMaxPressure attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_ALTERNATIVE_MIN_PRESSURE_ID = 0x0C0AU, /*!< CurrentDayAlternativeMinPressure attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_ALTERNATIVE_MAX_PRESSURE_ID =
        0x0C0BU, /*!< PreviousDayAlternativeMaxPressure attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_ALTERNATIVE_MIN_PRESSURE_ID =
        0x0C0CU, /*!< PreviousDayAlternativeMinPressure attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_DAY_ALTERNATIVE_MAX_DEMAND_ID   = 0x0C0DU, /*!< CurrentDayAlternativeMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY_ALTERNATIVE_MAX_DEMAND_ID  = 0x0C0EU, /*!< PreviousDayAlternativeMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_ALTERNATIVE_MAX_DEMAND_ID = 0x0C0FU, /*!< CurrentMonthAlternativeMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_YEAR_ALTERNATIVE_MAX_DEMAND_ID  = 0x0C10U, /*!< CurrentYearAlternativeMaxDemand attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY2_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C20U, /*!< PreviousDay2AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY2_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C21U, /*!< PreviousDay2AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY3_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C22U, /*!< PreviousDay3AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY3_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C23U, /*!< PreviousDay3AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY4_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C24U, /*!< PreviousDay4AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY4_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C25U, /*!< PreviousDay4AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY5_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C26U, /*!< PreviousDay5AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY5_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C27U, /*!< PreviousDay5AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY6_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C28U, /*!< PreviousDay6AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY6_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C29U, /*!< PreviousDay6AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY7_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C2AU, /*!< PreviousDay7AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY7_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C2BU, /*!< PreviousDay7AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY8_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C2CU, /*!< PreviousDay8AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_DAY8_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C2DU, /*!< PreviousDay8AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_WEEK_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C30U, /*!< CurrentWeekAlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_WEEK_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C31U, /*!< CurrentWeekAlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C32U, /*!< PreviousWeekAlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C33U, /*!< PreviousWeekAlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK2_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C34U, /*!< PreviousWeek2AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK2_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C35U, /*!< PreviousWeek2AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK3_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C36U, /*!< PreviousWeek3AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK3_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C37U, /*!< PreviousWeek3AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK4_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C38U, /*!< PreviousWeek4AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK4_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C39U, /*!< PreviousWeek4AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK5_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C3AU, /*!< PreviousWeek5AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_WEEK5_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C3BU, /*!< PreviousWeek5AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C40U, /*!< CurrentMonthAlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_CURRENT_MONTH_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C41U, /*!< CurrentMonthAlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C42U, /*!< PreviousMonthAlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C43U, /*!< PreviousMonthAlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH2_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C44U, /*!< PreviousMonth2AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH2_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C45U, /*!< PreviousMonth2AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH3_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C46U, /*!< PreviousMonth3AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH3_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C47U, /*!< PreviousMonth3AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH4_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C48U, /*!< PreviousMonth4AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH4_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C49U, /*!< PreviousMonth4AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH5_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C4AU, /*!< PreviousMonth5AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH5_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C4BU, /*!< PreviousMonth5AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH6_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C4CU, /*!< PreviousMonth6AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH6_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C4DU, /*!< PreviousMonth6AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH7_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C4EU, /*!< PreviousMonth7AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH7_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C4FU, /*!< PreviousMonth7AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH8_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C50U, /*!< PreviousMonth8AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH8_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C51U, /*!< PreviousMonth8AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH9_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C52U, /*!< PreviousMonth9AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH9_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C53U, /*!< PreviousMonth9AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH10_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C54U, /*!< PreviousMonth10AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH10_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C55U, /*!< PreviousMonth10AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH11_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C56U, /*!< PreviousMonth11AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH11_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C57U, /*!< PreviousMonth11AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH12_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C58U, /*!< PreviousMonth12AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH12_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C59U, /*!< PreviousMonth12AlternativeConsumptionReceived attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH13_ALTERNATIVE_CONSUMPTION_DELIVERED_ID =
        0x0C5AU, /*!< PreviousMonth13AlternativeConsumptionDelivered attribute. */
    EZB_ZCL_ATTR_METERING_PREVIOUS_MONTH13_ALTERNATIVE_CONSUMPTION_RECEIVED_ID =
        0x0C5BU, /*!< PreviousMonth13AlternativeConsumptionReceived attribute. */
} ezb_zcl_metering_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Metering server cluster.
 */
typedef struct ezb_zcl_metering_cluster_server_config_s {
    uint64_t current_summation_delivered; /*!< Configurable mandatory CurrentSummationDelivered attribute */
    uint8_t  status;                      /*!< Configurable mandatory Status attribute */
    uint8_t  unit_of_measure;             /*!< Configurable mandatory UnitOfMeasure attribute */
    uint8_t  summation_formatting;        /*!< Configurable mandatory SummationFormatting attribute */
    uint8_t  metering_device_type;        /*!< Configurable mandatory MeteringDeviceType attribute */
} ezb_zcl_metering_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL CurrentBlock attribute of Metering.
 */
typedef enum {
    EZB_ZCL_METERING_CURRENT_BLOCK_NO_BLOCKS_IN_USE = 0x00U, /*!< NoBlocksInUse */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK1           = 0x01U, /*!< Block1 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK2           = 0x02U, /*!< Block2 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK3           = 0x03U, /*!< Block3 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK4           = 0x04U, /*!< Block4 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK5           = 0x05U, /*!< Block5 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK6           = 0x06U, /*!< Block6 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK7           = 0x07U, /*!< Block7 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK8           = 0x08U, /*!< Block8 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK9           = 0x09U, /*!< Block9 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK10          = 0x0AU, /*!< Block10 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK11          = 0x0BU, /*!< Block11 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK12          = 0x0CU, /*!< Block12 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK13          = 0x0DU, /*!< Block13 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK14          = 0x0EU, /*!< Block14 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK15          = 0x0FU, /*!< Block15 */
    EZB_ZCL_METERING_CURRENT_BLOCK_BLOCK16          = 0x10U, /*!< Block16 */
} ezb_zcl_metering_server_current_block_t;

/**
 * @brief Enumeration for ZCL SupplyStatus attribute of Metering.
 */
typedef enum {
    EZB_ZCL_METERING_SUPPLY_STATUS_OFF       = 0x00U, /*!< Off */
    EZB_ZCL_METERING_SUPPLY_STATUS_OFF_ARMED = 0x01U, /*!< OffArmed */
    EZB_ZCL_METERING_SUPPLY_STATUS_ON        = 0x02U, /*!< On */
} ezb_zcl_metering_server_supply_status_t;

/** @brief Default value of DailyFreezeTime in Metering cluster */
#define EZB_ZCL_METERING_DAILY_FREEZE_TIME_DEFAULT_VALUE (0x0000)

/** @brief Default value of PowerFactor in Metering cluster */
#define EZB_ZCL_METERING_POWER_FACTOR_DEFAULT_VALUE (0x00)

/** @brief Default value of DefaultUpdatePeriod in Metering cluster */
#define EZB_ZCL_METERING_DEFAULT_UPDATE_PERIOD_DEFAULT_VALUE (0x1E)

/** @brief Default value of FastPollUpdatePeriod in Metering cluster */
#define EZB_ZCL_METERING_FAST_POLL_UPDATE_PERIOD_DEFAULT_VALUE (0x05)

/** @brief Default value of PresetReadingTime in Metering cluster */
#define EZB_ZCL_METERING_PRESET_READING_TIME_DEFAULT_VALUE (0x0000)

/** @brief Default value of Status in Metering cluster */
#define EZB_ZCL_METERING_STATUS_DEFAULT_VALUE (0x00)

/** @brief Default value of UnitOfMeasure in Metering cluster */
#define EZB_ZCL_METERING_UNIT_OF_MEASURE_DEFAULT_VALUE (0x00)

/** @brief Default value of AlternativeUnitOf in Metering cluster */
#define EZB_ZCL_METERING_ALTERNATIVE_UNIT_OF_DEFAULT_VALUE (0x00)

/** @brief Default value of InstantaneousDemand in Metering cluster */
#define EZB_ZCL_METERING_INSTANTANEOUS_DEMAND_DEFAULT_VALUE (0x00)

/** @brief Default value of HistoricalFreezeTime in Metering cluster */
#define EZB_ZCL_METERING_HISTORICAL_FREEZE_TIME_DEFAULT_VALUE (0x0000)

/** @brief Default value of MaxNumberOfPeriodsDelivered in Metering cluster */
#define EZB_ZCL_METERING_MAX_NUMBER_OF_PERIODS_DELIVERED_DEFAULT_VALUE (0x18)

/** @brief Default value of DemandIntegrationPeriod in Metering cluster */
#define EZB_ZCL_METERING_DEMAND_INTEGRATION_PERIOD_DEFAULT_VALUE (0x01)

/** @brief Default value of NumberOfDemandSubIntervals in Metering cluster */
#define EZB_ZCL_METERING_NUMBER_OF_DEMAND_SUB_INTERVALS_DEFAULT_VALUE (0x01)

/** @brief Default value of DemandLimitArmDuration in Metering cluster */
#define EZB_ZCL_METERING_DEMAND_LIMIT_ARM_DURATION_DEFAULT_VALUE (0x003C)

/** @brief Default value of LoadLimitSupplyState in Metering cluster */
#define EZB_ZCL_METERING_LOAD_LIMIT_SUPPLY_STATE_DEFAULT_VALUE (0x00)

/** @brief Default value of LoadLimitCounter in Metering cluster */
#define EZB_ZCL_METERING_LOAD_LIMIT_COUNTER_DEFAULT_VALUE (0x01)

/** @brief Default value of SupplyTamperState in Metering cluster */
#define EZB_ZCL_METERING_SUPPLY_TAMPER_STATE_DEFAULT_VALUE (0x00)

/** @brief Default value of SupplyDepletionState in Metering cluster */
#define EZB_ZCL_METERING_SUPPLY_DEPLETION_STATE_DEFAULT_VALUE (0x00)

/** @brief Default value of SupplyUncontrolledFlowState in Metering cluster */
#define EZB_ZCL_METERING_SUPPLY_UNCONTROLLED_FLOW_STATE_DEFAULT_VALUE (0x00)

/** @brief Default value of CurrentTier1Block1SummationDelivered in Metering cluster */
#define EZB_ZCL_METERING_CURRENT_TIER1_BLOCK1_SUMMATION_DELIVERED_DEFAULT_VALUE (0x000000000000)

/** @brief Default value of GenericAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_GENERIC_ALARM_MASK_DEFAULT_VALUE (0xFFFF)

/** @brief Default value of ElectricityAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_ELECTRICITY_ALARM_MASK_DEFAULT_VALUE (0xFFFFFFFF)

/** @brief Default value of GenericFlowPressureAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_GENERIC_FLOW_PRESSURE_ALARM_MASK_DEFAULT_VALUE (0xFFFF)

/** @brief Default value of WaterSpecificAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_WATER_SPECIFIC_ALARM_MASK_DEFAULT_VALUE (0xFFFF)

/** @brief Default value of HeatAndCoolingSpecificAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_HEAT_AND_COOLING_SPECIFIC_ALARM_MASK_DEFAULT_VALUE (0xFFFF)

/** @brief Default value of GasSpecificAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_GAS_SPECIFIC_ALARM_MASK_DEFAULT_VALUE (0xFFFF)

/** @brief Default value of ExtendedGenericAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_EXTENDED_GENERIC_ALARM_MASK_DEFAULT_VALUE (0xFFFFFFFFFFFF)

/** @brief Default value of ManufacturerAlarmMask in Metering cluster */
#define EZB_ZCL_METERING_MANUFACTURER_ALARM_MASK_DEFAULT_VALUE (0xFFFF)

/** @brief Default value of BillToDateDelivered in Metering cluster */
#define EZB_ZCL_METERING_BILL_TO_DATE_DELIVERED_DEFAULT_VALUE (0x00000000)

/** @brief Default value of BillToDateTimeStampDelivered in Metering cluster */
#define EZB_ZCL_METERING_BILL_TO_DATE_TIME_STAMP_DELIVERED_DEFAULT_VALUE (0x00)

/** @brief Default value of ProjectedBillDelivered in Metering cluster */
#define EZB_ZCL_METERING_PROJECTED_BILL_DELIVERED_DEFAULT_VALUE (0x00000000)

/** @brief Default value of ProjectedBillTimeStampDelivered in Metering cluster */
#define EZB_ZCL_METERING_PROJECTED_BILL_TIME_STAMP_DELIVERED_DEFAULT_VALUE (0x00)

/** @brief Default value of BillToDateReceived in Metering cluster */
#define EZB_ZCL_METERING_BILL_TO_DATE_RECEIVED_DEFAULT_VALUE (0x00000000)

/** @brief Default value of BillToDateTimeStampReceived in Metering cluster */
#define EZB_ZCL_METERING_BILL_TO_DATE_TIME_STAMP_RECEIVED_DEFAULT_VALUE (0x00)

/** @brief Default value of ProjectedBillReceived in Metering cluster */
#define EZB_ZCL_METERING_PROJECTED_BILL_RECEIVED_DEFAULT_VALUE (0x00000000)

/** @brief Default value of ProjectedBillTimeStampReceived in Metering cluster */
#define EZB_ZCL_METERING_PROJECTED_BILL_TIME_STAMP_RECEIVED_DEFAULT_VALUE (0x00)

/** @brief Default value of UncontrolledFlowMultiplier in Metering cluster */
#define EZB_ZCL_METERING_UNCONTROLLED_FLOW_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Default value of UncontrolledFlowDivisor in Metering cluster */
#define EZB_ZCL_METERING_UNCONTROLLED_FLOW_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Default value of AlternativeInstantaneousDemand in Metering cluster */
#define EZB_ZCL_METERING_ALTERNATIVE_INSTANTANEOUS_DEMAND_DEFAULT_VALUE (0x00)

/**
 * @brief Received Command identifiers for the Metering cluster.
 */
typedef enum {
    EZB_ZCL_CMD_METERING_GET_PROFILE_RESPONSE_ID            = 0x00U, /*!< GetProfileResponse command. */
    EZB_ZCL_CMD_METERING_REQUEST_MIRROR_ID                  = 0x01U, /*!< RequestMirror command. */
    EZB_ZCL_CMD_METERING_REMOVE_MIRROR_ID                   = 0x02U, /*!< RemoveMirror command. */
    EZB_ZCL_CMD_METERING_REQUEST_FAST_POLL_MODE_RESPONSE_ID = 0x03U, /*!< RequestFastPollModeResponse command. */
    EZB_ZCL_CMD_METERING_SCHEDULE_SNAPSHOT_RESPONSE_ID      = 0x04U, /*!< ScheduleSnapshotResponse command. */
    EZB_ZCL_CMD_METERING_TAKE_SNAPSHOT_RESPONSE_ID          = 0x05U, /*!< TakeSnapshotResponse command. */
    EZB_ZCL_CMD_METERING_PUBLISH_SNAPSHOT_ID                = 0x06U, /*!< PublishSnapshot command. */
    EZB_ZCL_CMD_METERING_GET_SAMPLED_DATA_RESPONSE_ID       = 0x07U, /*!< GetSampledDataResponse command. */
    EZB_ZCL_CMD_METERING_CONFIGURE_MIRROR_ID                = 0x08U, /*!< ConfigureMirror command. */
    EZB_ZCL_CMD_METERING_CONFIGURE_NOTIFICATION_SCHEME_ID   = 0x09U, /*!< ConfigureNotificationScheme command. */
    EZB_ZCL_CMD_METERING_CONFIGURE_NOTIFICATION_FLAG_ID     = 0x0AU, /*!< ConfigureNotificationFlag command. */
    EZB_ZCL_CMD_METERING_GET_NOTIFIED_MESSAGE_ID            = 0x0BU, /*!< GetNotifiedMessage command. */
    EZB_ZCL_CMD_METERING_SUPPLY_STATUS_RESPONSE_ID          = 0x0CU, /*!< SupplyStatusResponse command. */
    EZB_ZCL_CMD_METERING_START_SAMPLING_RESPONSE_ID         = 0x0DU, /*!< StartSamplingResponse command. */
} ezb_zcl_metering_server_cmd_id_t;

/**
 * @brief Attribute identifiers for the metering client cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_METERING_FUNCTIONAL_NOTIFICATION_FLAGS_ID = 0x0000U, /*!< FunctionalNotificationFlags attribute. */
    EZB_ZCL_ATTR_METERING_NOTIFICATION_FLAGS2_ID           = 0x0001U, /*!< NotificationFlags2 attribute. */
    EZB_ZCL_ATTR_METERING_NOTIFICATION_FLAGS3_ID           = 0x0002U, /*!< NotificationFlags3 attribute. */
    EZB_ZCL_ATTR_METERING_NOTIFICATION_FLAGS4_ID           = 0x0003U, /*!< NotificationFlags4 attribute. */
    EZB_ZCL_ATTR_METERING_NOTIFICATION_FLAGS5_ID           = 0x0004U, /*!< NotificationFlags5 attribute. */
    EZB_ZCL_ATTR_METERING_NOTIFICATION_FLAGS6_ID           = 0x0005U, /*!< NotificationFlags6 attribute. */
    EZB_ZCL_ATTR_METERING_NOTIFICATION_FLAGS7_ID           = 0x0006U, /*!< NotificationFlags7 attribute. */
    EZB_ZCL_ATTR_METERING_NOTIFICATION_FLAGS8_ID           = 0x0007U, /*!< NotificationFlags8 attribute. */
} ezb_zcl_metering_client_attr_t;

/** @brief Default value of FunctionalNotificationFlags in Metering cluster */
#define EZB_ZCL_METERING_FUNCTIONAL_NOTIFICATION_FLAGS_DEFAULT_VALUE (0x00000000)

/** @brief Default value of NotificationFlags2 in Metering cluster */
#define EZB_ZCL_METERING_NOTIFICATION_FLAGS2_DEFAULT_VALUE (0x00000000)

/** @brief Default value of NotificationFlags3 in Metering cluster */
#define EZB_ZCL_METERING_NOTIFICATION_FLAGS3_DEFAULT_VALUE (0x00000000)

/** @brief Default value of NotificationFlags4 in Metering cluster */
#define EZB_ZCL_METERING_NOTIFICATION_FLAGS4_DEFAULT_VALUE (0x00000000)

/** @brief Default value of NotificationFlags5 in Metering cluster */
#define EZB_ZCL_METERING_NOTIFICATION_FLAGS5_DEFAULT_VALUE (0x00000000)

/** @brief Default value of NotificationFlags6 in Metering cluster */
#define EZB_ZCL_METERING_NOTIFICATION_FLAGS6_DEFAULT_VALUE (0x00000000)

/** @brief Default value of NotificationFlags7 in Metering cluster */
#define EZB_ZCL_METERING_NOTIFICATION_FLAGS7_DEFAULT_VALUE (0x00000000)

/** @brief Default value of NotificationFlags8 in Metering cluster */
#define EZB_ZCL_METERING_NOTIFICATION_FLAGS8_DEFAULT_VALUE (0x00000000)

/**
 * @brief Received Command identifiers for the Metering cluster.
 */
typedef enum {
    EZB_ZCL_CMD_METERING_GET_PROFILE_ID                      = 0x00U, /*!< GetProfile command. */
    EZB_ZCL_CMD_METERING_REQUEST_MIRROR_RESPONSE_ID          = 0x01U, /*!< RequestMirrorResponse command. */
    EZB_ZCL_CMD_METERING_MIRROR_REMOVED_ID                   = 0x02U, /*!< MirrorRemoved command. */
    EZB_ZCL_CMD_METERING_REQUEST_FAST_POLL_MODE_ID           = 0x03U, /*!< RequestFastPollMode command. */
    EZB_ZCL_CMD_METERING_SCHEDULE_SNAPSHOT_ID                = 0x04U, /*!< ScheduleSnapshot command. */
    EZB_ZCL_CMD_METERING_TAKE_SNAPSHOT_ID                    = 0x05U, /*!< TakeSnapshot command. */
    EZB_ZCL_CMD_METERING_GET_SNAPSHOT_ID                     = 0x06U, /*!< GetSnapshot command. */
    EZB_ZCL_CMD_METERING_START_SAMPLING_ID                   = 0x07U, /*!< StartSampling command. */
    EZB_ZCL_CMD_METERING_GET_SAMPLED_DATA_ID                 = 0x08U, /*!< GetSampledData command. */
    EZB_ZCL_CMD_METERING_MIRROR_REPORT_ATTRIBUTE_RESPONSE_ID = 0x09U, /*!< MirrorReportAttributeResponse command. */
    EZB_ZCL_CMD_METERING_RESET_LOAD_LIMIT_COUNTER_ID         = 0x0AU, /*!< ResetLoadLimitCounter command. */
    EZB_ZCL_CMD_METERING_CHANGE_SUPPLY_ID                    = 0x0BU, /*!< ChangeSupply command. */
    EZB_ZCL_CMD_METERING_LOCAL_CHANGE_SUPPLY_ID              = 0x0CU, /*!< LocalChangeSupply command. */
    EZB_ZCL_CMD_METERING_SET_SUPPLY_STATUS_ID                = 0x0DU, /*!< SetSupplyStatus command. */
    EZB_ZCL_CMD_METERING_SET_UNCONTROLLED_FLOW_THRESHOLD_ID  = 0x0EU, /*!< SetUncontrolledFlowThreshold command. */
} ezb_zcl_metering_client_cmd_id_t;

typedef ezb_zcl_metering_cluster_server_config_t ezb_zcl_metering_cluster_config_t;

/**
 * @brief Add an attribute to an metering cluster descriptor.
 *
 * @param cluster_desc Pointer to the metering cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_metering_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an metering cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the metering cluster configuration structure, refer to
 * ezb_zcl_metering_cluster_server_config_t or ezb_zcl_metering_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_metering_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Metering cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_metering_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Metering cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_metering_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_METERING_CLIENT_ROLE_INIT ezb_zcl_metering_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_METERING_SERVER_ROLE_INIT ezb_zcl_metering_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
