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
   BASIC Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the basic cluster implementation */
#define EZB_ZCL_BASIC_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the basic server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_BASIC_ZCL_VERSION_ID                  = 0x0000U, /*!< ZCLVersion attribute. */
    EZB_ZCL_ATTR_BASIC_APPLICATION_VERSION_ID          = 0x0001U, /*!< ApplicationVersion attribute. */
    EZB_ZCL_ATTR_BASIC_STACK_VERSION_ID                = 0x0002U, /*!< StackVersion attribute. */
    EZB_ZCL_ATTR_BASIC_HW_VERSION_ID                   = 0x0003U, /*!< HWVersion attribute. */
    EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID            = 0x0004U, /*!< ManufacturerName attribute. */
    EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID             = 0x0005U, /*!< ModelIdentifier attribute. */
    EZB_ZCL_ATTR_BASIC_DATE_CODE_ID                    = 0x0006U, /*!< DateCode attribute. */
    EZB_ZCL_ATTR_BASIC_POWER_SOURCE_ID                 = 0x0007U, /*!< PowerSource attribute. */
    EZB_ZCL_ATTR_BASIC_GENERIC_DEVICE_CLASS_ID         = 0x0008U, /*!< GenericDevice-Class attribute. */
    EZB_ZCL_ATTR_BASIC_GENERIC_DEVICE_TYPE_ID          = 0x0009U, /*!< GenericDevice-Type attribute. */
    EZB_ZCL_ATTR_BASIC_PRODUCT_CODE_ID                 = 0x000aU, /*!< ProductCode attribute. */
    EZB_ZCL_ATTR_BASIC_PRODUCT_URL_ID                  = 0x000bU, /*!< ProductURL attribute. */
    EZB_ZCL_ATTR_BASIC_MANUFACTURER_VERSION_DETAILS_ID = 0x000cU, /*!< ManufacturerVersionDetails attribute. */
    EZB_ZCL_ATTR_BASIC_SERIAL_NUMBER_ID                = 0x000dU, /*!< SerialNumber attribute. */
    EZB_ZCL_ATTR_BASIC_PRODUCT_LABEL_ID                = 0x000eU, /*!< ProductLabel attribute. */
    EZB_ZCL_ATTR_BASIC_LOCATION_DESCRIPTION_ID         = 0x0010U, /*!< LocationDescription attribute. */
    EZB_ZCL_ATTR_BASIC_PHYSICAL_ENVIRONMENT_ID         = 0x0011U, /*!< PhysicalEnvironment attribute. */
    EZB_ZCL_ATTR_BASIC_DEVICE_ENABLED_ID               = 0x0012U, /*!< DeviceEnabled attribute. */
    EZB_ZCL_ATTR_BASIC_ALARM_MASK_ID                   = 0x0013U, /*!< AlarmMask attribute. */
    EZB_ZCL_ATTR_BASIC_DISABLE_LOCAL_CONFIG_ID         = 0x0014U, /*!< DisableLocalConfig attribute. */
    EZB_ZCL_ATTR_BASIC_SW_BUILD_ID_ID                  = 0x4000U, /*!< SWBuildID attribute. */
} ezb_zcl_basic_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Basic server cluster.
 */
typedef struct ezb_zcl_basic_cluster_server_config_s {
    uint8_t zcl_version;  /*!< Configurable mandatory ZCLVersion attribute */
    uint8_t power_source; /*!< Configurable mandatory PowerSource attribute */
} ezb_zcl_basic_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL PowerSource attribute of Basic.
 */
typedef enum {
    EZB_ZCL_BASIC_POWER_SOURCE_UNKNOWN                                = 0x00U, /*!< Unknown */
    EZB_ZCL_BASIC_POWER_SOURCE_SINGLE_PHASE_MAINS                     = 0x01U, /*!< SinglePhaseMains */
    EZB_ZCL_BASIC_POWER_SOURCE_THREE_PHASE_MAINS                      = 0x02U, /*!< ThreePhaseMains */
    EZB_ZCL_BASIC_POWER_SOURCE_BATTERY                                = 0x03U, /*!< Battery */
    EZB_ZCL_BASIC_POWER_SOURCE_DC_SOURCE                              = 0x04U, /*!< DCSource */
    EZB_ZCL_BASIC_POWER_SOURCE_EMERGENCY_MAINS_CONSTANTLY_POWERED     = 0x05U, /*!< EmergencyMainsConstantlyPowered */
    EZB_ZCL_BASIC_POWER_SOURCE_EMERGENCY_MAINS_AND_TRANSFER_SWITCH    = 0x06U, /*!< EmergencyMainsAndTransferSwitch */
    EZB_ZCL_BASIC_POWER_SOURCE_UNKNOWN_WITH_BATTERY_BACKUP            = 0x80U, /*!< UnknownWithBatteryBackup */
    EZB_ZCL_BASIC_POWER_SOURCE_SINGLE_PHASE_MAINS_WITH_BATTERY_BACKUP = 0x81U, /*!< SinglePhaseMainsWithBatteryBackup */
    EZB_ZCL_BASIC_POWER_SOURCE_THREE_PHASE_MAINS_WITH_BATTERY_BACKUP  = 0x82U, /*!< ThreePhaseMainsWithBatteryBackup */
    EZB_ZCL_BASIC_POWER_SOURCE_BATTERY_WITH_BATTERY_BACKUP            = 0x83U, /*!< BatteryWithBatteryBackup */
    EZB_ZCL_BASIC_POWER_SOURCE_DC_SOURCE_WITH_BATTERY_BACKUP          = 0x84U, /*!< DCSourceWithBatteryBackup */
    EZB_ZCL_BASIC_POWER_SOURCE_EMERGENCY_MAINS_CONSTANTLY_POWERED_WITH_BATTERY_BACKUP =
        0x85U, /*!< EmergencyMainsConstantlyPoweredWithBatteryBackup */
    EZB_ZCL_BASIC_POWER_SOURCE_EMERGENCY_MAINS_AND_TRANSFER_SWITCH_WITH_BATTERY_BACKUP =
        0x86U, /*!< EmergencyMainsAndTransferSwitchWithBatteryBackup */
} ezb_zcl_basic_server_power_source_t;

/**
 * @brief Enumeration for ZCL GenericDevice-Class attribute of Basic.
 */
typedef enum {
    EZB_ZCL_BASIC_GENERIC_DEVICE_CLASS_LIGHTING = 0x00U, /*!< Lighting */
} ezb_zcl_basic_server_generic_device_class_t;

/**
 * @brief Enumeration for ZCL GenericDevice-Type attribute of Basic.
 */
typedef enum {
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_INCANDESCENT       = 0x00U, /*!< Incandescent */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_SPOTLIGHT_HALOGEN  = 0x01U, /*!< SpotlightHalogen */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_HALOGEN_BULB       = 0x02U, /*!< HalogenBulb */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_CFL                = 0x03U, /*!< CFL */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_LINEAR_FLUORESCENT = 0x04U, /*!< LinearFluorescent */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_LED_BULB           = 0x05U, /*!< LEDBulb */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_SPOTLIGHT_LED      = 0x06U, /*!< SpotlightLED */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_LED_STRIP          = 0x07U, /*!< LEDStrip */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_LED_TUBE           = 0x08U, /*!< LEDTube */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_GENERIC_INDOOR_LUMINAIRE_OR_LIGHT_FIXTURE =
        0x09U, /*!< GenericIndoorLuminaireOrLightFixture */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_GENERIC_OUTDOOR_LUMINAIRE_OR_LIGHT_FIXTURE =
        0x0aU,                                                                    /*!< GenericOutdoorLuminaireOrLightFixture */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_PENDANT_LUMINAIRE_OR_LIGHT_FIXTURE = 0x0bU, /*!< PendantLuminaireOrLightFixture */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_FLOOR_STANDING_LUMINAIRE_OR_LIGHT_FIXTURE =
        0x0cU,                                                               /*!< FloorStandingLuminaireOrLightFixture */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_GENERIC_CONTROLLER            = 0xe0U, /*!< GenericController */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_WALL_SWITCH                   = 0xe1U, /*!< WallSwitch */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_PORTABLE_REMOTE_CONTROLLER    = 0xe2U, /*!< PortableRemoteController */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_MOTION_SENSOR_OR_LIGHT_SENSOR = 0xe3U, /*!< MotionSensorOrLightSensor */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_GENERIC_ACTUATOR              = 0xf0U, /*!< GenericActuator */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_WALL_SOCKET                   = 0xf1U, /*!< WallSocket */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_GATEWAY_OR_BRIDGE             = 0xf2U, /*!< GatewayOrBridge */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_PLUG_IN_UNIT                  = 0xf3U, /*!< PlugInUnit */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_RETROFIT_ACTUATOR             = 0xf4U, /*!< RetrofitActuator */
    EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_UNSPECIFIED                   = 0xffU, /*!< Unspecified */
} ezb_zcl_basic_server_generic_device_type_t;

/**
 * @brief Enumeration for ZCL PhysicalEnvironment attribute of Basic.
 */
typedef enum {
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_UNSPECIFIED_ENVIRONMENT = 0x00U, /*!< UnspecifiedEnvironment */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DEPRECATED              = 0x01U, /*!< Deprecated */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BAR                     = 0x02U, /*!< Bar */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_COURTYARD               = 0x03U, /*!< Courtyard */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BATHROOM                = 0x04U, /*!< Bathroom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BEDROOM                 = 0x05U, /*!< Bedroom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BILLIARD_ROOM           = 0x06U, /*!< BilliardRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_UTILITY_ROOM            = 0x07U, /*!< UtilityRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_CELLAR                  = 0x08U, /*!< Cellar */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_STORAGE_CLOSET          = 0x09U, /*!< StorageCloset */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_THEATER                 = 0x0aU, /*!< Theater */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_OFFICE1                 = 0x0bU, /*!< Office1 */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DECK                    = 0x0cU, /*!< Deck */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DEN                     = 0x0dU, /*!< Den */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DINING_ROOM             = 0x0eU, /*!< DiningRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_ELECTRICAL_ROOM         = 0x0fU, /*!< ElectricalRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_ELEVATOR                = 0x10U, /*!< Elevator */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_ENTRY                   = 0x11U, /*!< Entry */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_FAMILY_ROOM             = 0x12U, /*!< FamilyRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_MAIN_FLOOR              = 0x13U, /*!< MainFloor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_UPSTAIRS                = 0x14U, /*!< Upstairs */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DOWNSTAIRS              = 0x15U, /*!< Downstairs */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BASEMENT_LOWER_LEVEL    = 0x16U, /*!< Basement/LowerLevel */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_GALLERY                 = 0x17U, /*!< Gallery */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_GAME_ROOM               = 0x18U, /*!< GameRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_GARAGE                  = 0x19U, /*!< Garage */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_GYM                     = 0x1aU, /*!< Gym */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_HALLWAY                 = 0x1bU, /*!< Hallway */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_HOUSE                   = 0x1cU, /*!< House */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_KITCHEN                 = 0x1dU, /*!< Kitchen */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_LAUNDRY_ROOM            = 0x1eU, /*!< LaundryRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_LIBRARY                 = 0x1fU, /*!< Library */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_MASTER_BEDROOM          = 0x20U, /*!< MasterBedroom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_MUD_ROOM                = 0x21U, /*!< MudRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_NURSERY                 = 0x22U, /*!< Nursery */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_PANTRY                  = 0x23U, /*!< Pantry */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_OFFICE0                 = 0x24U, /*!< Office0 */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_OUTSIDE                 = 0x25U, /*!< Outside */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_POOL                    = 0x26U, /*!< Pool */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_PORCH                   = 0x27U, /*!< Porch */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SEWING_ROOM             = 0x28U, /*!< SewingRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SITTING_ROOM            = 0x29U, /*!< SittingRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_STAIRWAY                = 0x2aU, /*!< Stairway */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_YARD                    = 0x2bU, /*!< Yard */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_ATTIC                   = 0x2cU, /*!< Attic */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_HOT_TUB                 = 0x2dU, /*!< HotTub */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_LIVING_ROOM1            = 0x2eU, /*!< LivingRoom1 */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SAUNA                   = 0x2fU, /*!< Sauna */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SHOP_OR_WORKSHOP        = 0x30U, /*!< ShopOrWorkshop */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_GUEST_BEDROOM           = 0x31U, /*!< GuestBedroom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_GUEST_BATH              = 0x32U, /*!< GuestBath */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_POWDER_ROOM             = 0x33U, /*!< PowderRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BACK_YARD               = 0x34U, /*!< BackYard */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_FRONT_YARD              = 0x35U, /*!< FrontYard */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_PATIO                   = 0x36U, /*!< Patio */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DRIVEWAY                = 0x37U, /*!< Driveway */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SUN_ROOM                = 0x38U, /*!< SunRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_LIVING_ROOM0            = 0x39U, /*!< LivingRoom0 */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SPA                     = 0x3aU, /*!< Spa */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_WHIRLPOOL               = 0x3bU, /*!< Whirlpool */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SHED                    = 0x3cU, /*!< Shed */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_EQUIPMENT_STORAGE       = 0x3dU, /*!< EquipmentStorage */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_HOBBY_OR_CRAFT_ROOM     = 0x3eU, /*!< HobbyOrCraftRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_FOUNTAIN                = 0x3fU, /*!< Fountain */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_POND                    = 0x40U, /*!< Pond */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_RECEPTION_ROOM          = 0x41U, /*!< ReceptionRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BREAKFAST_ROOM          = 0x42U, /*!< BreakfastRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_NOOK                    = 0x43U, /*!< Nook */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_GARDEN                  = 0x44U, /*!< Garden */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BALCONY                 = 0x45U, /*!< Balcony */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_PANIC_ROOM              = 0x46U, /*!< PanicRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_TERRACE                 = 0x47U, /*!< Terrace */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_ROOF                    = 0x48U, /*!< Roof */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_TOILET                  = 0x49U, /*!< Toilet */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_TOILET_MAIN             = 0x4aU, /*!< ToiletMain */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_OUTSIDE_TOILET          = 0x4bU, /*!< OutsideToilet */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_SHOWER_ROOM             = 0x4cU, /*!< ShowerRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_STUDY                   = 0x4dU, /*!< Study */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_FRONT_GARDEN            = 0x4eU, /*!< FrontGarden */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BACK_GARDEN             = 0x4fU, /*!< BackGarden */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_KETTLE                  = 0x50U, /*!< Kettle */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_TELEVISION              = 0x51U, /*!< Television */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_STOVE                   = 0x52U, /*!< Stove */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_MICROWAVE               = 0x53U, /*!< Microwave */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_TOASTER                 = 0x54U, /*!< Toaster */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_VACUUM                  = 0x55U, /*!< Vacuum */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_APPLIANCE               = 0x56U, /*!< Appliance */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_FRONT_DOOR              = 0x57U, /*!< FrontDoor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_BACK_DOOR               = 0x58U, /*!< BackDoor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_FRIDGE_DOOR             = 0x59U, /*!< FridgeDoor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_MEDICATION_CABINET_DOOR = 0x60U, /*!< MedicationCabinetDoor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_WARDROBE_DOOR           = 0x61U, /*!< WardrobeDoor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_FRONT_CUPBOARD_DOOR     = 0x62U, /*!< FrontCupboardDoor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_OTHER_DOOR              = 0x63U, /*!< OtherDoor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_WAITING_ROOM            = 0x64U, /*!< WaitingRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_TRIAGE_ROOM             = 0x65U, /*!< TriageRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DOCTORS_OFFICE          = 0x66U, /*!< DoctorsOffice */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_PATIENTS_PRIVATE_ROOM   = 0x67U, /*!< PatientsPrivateRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_CONSULTATION_ROOM       = 0x68U, /*!< ConsultationRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_NURSE_STATION           = 0x69U, /*!< NurseStation */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_WARD                    = 0x6aU, /*!< Ward */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_CORRIDOR                = 0x6bU, /*!< Corridor */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_OPERATING_THEATRE       = 0x6cU, /*!< OperatingTheatre */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DENTAL_SURGERY_ROOM     = 0x6dU, /*!< DentalSurgeryRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_MEDICAL_IMAGING_ROOM    = 0x6eU, /*!< MedicalImagingRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DECONTAMINATION_ROOM    = 0x6fU, /*!< DecontaminationRoom */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_ATRIUM                  = 0x70U, /*!< Atrium */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_MIRROR                  = 0x71U, /*!< Mirror */
    EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_UNKNOWN_ENVIRONMENT     = 0xffU, /*!< UnknownEnvironment */
} ezb_zcl_basic_server_physical_environment_t;

/**
 * @brief Bitmap for ZCL AlarmMask attribute of Basic.
 */
typedef enum {
    EZB_ZCL_BASIC_ALARM_MASK_GENERAL_HARDWARE_FAULT = 01U, /*!< GeneralHardwareFault */
    EZB_ZCL_BASIC_ALARM_MASK_GENERAL_SOFTWARE_FAULT = 02U, /*!< GeneralSoftwareFault */
} ezb_zcl_basic_server_alarm_mask_t;

/**
 * @brief Bitmap for ZCL DisableLocalConfig attribute of Basic.
 */
typedef enum {
    EZB_ZCL_BASIC_DISABLE_LOCAL_CONFIG_DISABLE_RESET_TO_FACTORY_DEFAULTS = 01U, /*!< DisableResetToFactoryDefaults */
    EZB_ZCL_BASIC_DISABLE_LOCAL_CONFIG_DISABLE_DEVICE_CONFIGURATION      = 02U, /*!< DisableDeviceConfiguration */
} ezb_zcl_basic_server_disable_local_config_t;

/** @brief Default value of ZCLVersion in Basic cluster */
#define EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE (0x08)

/** @brief Minimum value of ZCLVersion in Basic cluster */
#define EZB_ZCL_BASIC_ZCL_VERSION_MIN_VALUE (0x00)

/** @brief Maximum value of ZCLVersion in Basic cluster */
#define EZB_ZCL_BASIC_ZCL_VERSION_MAX_VALUE (0xff)
/** @brief Default value of ApplicationVersion in Basic cluster */
#define EZB_ZCL_BASIC_APPLICATION_VERSION_DEFAULT_VALUE (0x00)

/** @brief Minimum value of ApplicationVersion in Basic cluster */
#define EZB_ZCL_BASIC_APPLICATION_VERSION_MIN_VALUE (0x00)

/** @brief Maximum value of ApplicationVersion in Basic cluster */
#define EZB_ZCL_BASIC_APPLICATION_VERSION_MAX_VALUE (0xff)
/** @brief Default value of StackVersion in Basic cluster */
#define EZB_ZCL_BASIC_STACK_VERSION_DEFAULT_VALUE (0x00)

/** @brief Minimum value of StackVersion in Basic cluster */
#define EZB_ZCL_BASIC_STACK_VERSION_MIN_VALUE (0x00)

/** @brief Maximum value of StackVersion in Basic cluster */
#define EZB_ZCL_BASIC_STACK_VERSION_MAX_VALUE (0xff)
/** @brief Default value of HWVersion in Basic cluster */
#define EZB_ZCL_BASIC_HW_VERSION_DEFAULT_VALUE (0x00)

/** @brief Minimum value of HWVersion in Basic cluster */
#define EZB_ZCL_BASIC_HW_VERSION_MIN_VALUE (0x00)

/** @brief Maximum value of HWVersion in Basic cluster */
#define EZB_ZCL_BASIC_HW_VERSION_MAX_VALUE (0xff)

/** @brief Default value of PowerSource in Basic cluster */
#define EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE (0x00)

/** @brief Default value of GenericDevice-Class in Basic cluster */
#define EZB_ZCL_BASIC_GENERIC_DEVICE_CLASS_DEFAULT_VALUE (0xff)

/** @brief Minimum value of GenericDevice-Class in Basic cluster */
#define EZB_ZCL_BASIC_GENERIC_DEVICE_CLASS_MIN_VALUE (0x00)

/** @brief Maximum value of GenericDevice-Class in Basic cluster */
#define EZB_ZCL_BASIC_GENERIC_DEVICE_CLASS_MAX_VALUE (0xff)
/** @brief Default value of GenericDevice-Type in Basic cluster */
#define EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_DEFAULT_VALUE (0xff)

/** @brief Minimum value of GenericDevice-Type in Basic cluster */
#define EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_MIN_VALUE (0x00)

/** @brief Maximum value of GenericDevice-Type in Basic cluster */
#define EZB_ZCL_BASIC_GENERIC_DEVICE_TYPE_MAX_VALUE (0xff)

/** @brief Default value of PhysicalEnvironment in Basic cluster */
#define EZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DEFAULT_VALUE (0x00)

/** @brief Default value of DeviceEnabled in Basic cluster */
#define EZB_ZCL_BASIC_DEVICE_ENABLED_DEFAULT_VALUE (true)

/** @brief Default value of AlarmMask in Basic cluster */
#define EZB_ZCL_BASIC_ALARM_MASK_DEFAULT_VALUE (0x00)

/** @brief Default value of DisableLocalConfig in Basic cluster */
#define EZB_ZCL_BASIC_DISABLE_LOCAL_CONFIG_DEFAULT_VALUE (0x00)

/**
 * @brief Received Command identifiers for the Basic cluster.
 */
typedef enum {
    EZB_ZCL_CMD_BASIC_RESET_TO_FACTORY_DEFAULTS_ID = 0x00U, /*!< ResetToFactoryDefaults command. */
} ezb_zcl_basic_server_cmd_id_t;

typedef ezb_zcl_basic_cluster_server_config_t ezb_zcl_basic_cluster_config_t;

/**
 * @brief Add an attribute to an basic cluster descriptor.
 *
 * @param cluster_desc Pointer to the basic cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_basic_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an basic cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the basic cluster configuration structure, refer to ezb_zcl_basic_cluster_server_config_t or
 * ezb_zcl_basic_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_basic_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Basic cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_basic_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Basic cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_basic_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_BASIC_CLIENT_ROLE_INIT ezb_zcl_basic_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_BASIC_SERVER_ROLE_INIT ezb_zcl_basic_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
