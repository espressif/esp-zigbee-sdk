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
   PRICE Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the price cluster implementation */
#define EZB_ZCL_PRICE_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the price server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_PRICE_TIER1_PRICE_LABEL_ID                     = 0x0000U, /*!< Tier1PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_PRICE_LABEL_ID                     = 0x0001U, /*!< Tier2PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_PRICE_LABEL_ID                     = 0x0002U, /*!< Tier3PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_PRICE_LABEL_ID                     = 0x0003U, /*!< Tier4PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_PRICE_LABEL_ID                     = 0x0004U, /*!< Tier5PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_PRICE_LABEL_ID                     = 0x0005U, /*!< Tier6PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_PRICE_LABEL_ID                     = 0x0006U, /*!< Tier7PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_PRICE_LABEL_ID                     = 0x0007U, /*!< Tier8PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_PRICE_LABEL_ID                     = 0x0008U, /*!< Tier9PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_PRICE_LABEL_ID                    = 0x0009U, /*!< Tier10PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_PRICE_LABEL_ID                    = 0x000AU, /*!< Tier11PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_PRICE_LABEL_ID                    = 0x000BU, /*!< Tier12PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_PRICE_LABEL_ID                    = 0x000CU, /*!< Tier13PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_PRICE_LABEL_ID                    = 0x000DU, /*!< Tier14PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_PRICE_LABEL_ID                    = 0x000EU, /*!< Tier15PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER16_PRICE_LABEL_ID                    = 0x000FU, /*!< Tier16PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER17_PRICE_LABEL_ID                    = 0x0010U, /*!< Tier17PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER18_PRICE_LABEL_ID                    = 0x0011U, /*!< Tier18PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER19_PRICE_LABEL_ID                    = 0x0012U, /*!< Tier19PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER20_PRICE_LABEL_ID                    = 0x0013U, /*!< Tier20PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER21_PRICE_LABEL_ID                    = 0x0014U, /*!< Tier21PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER22_PRICE_LABEL_ID                    = 0x0015U, /*!< Tier22PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER23_PRICE_LABEL_ID                    = 0x0016U, /*!< Tier23PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER24_PRICE_LABEL_ID                    = 0x0017U, /*!< Tier24PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER25_PRICE_LABEL_ID                    = 0x0018U, /*!< Tier25PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER26_PRICE_LABEL_ID                    = 0x0019U, /*!< Tier26PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER27_PRICE_LABEL_ID                    = 0x001AU, /*!< Tier27PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER28_PRICE_LABEL_ID                    = 0x001BU, /*!< Tier28PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER29_PRICE_LABEL_ID                    = 0x001CU, /*!< Tier29PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER30_PRICE_LABEL_ID                    = 0x001DU, /*!< Tier30PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER31_PRICE_LABEL_ID                    = 0x001EU, /*!< Tier31PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER32_PRICE_LABEL_ID                    = 0x001FU, /*!< Tier32PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER33_PRICE_LABEL_ID                    = 0x0020U, /*!< Tier33PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER34_PRICE_LABEL_ID                    = 0x0021U, /*!< Tier34PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER35_PRICE_LABEL_ID                    = 0x0022U, /*!< Tier35PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER36_PRICE_LABEL_ID                    = 0x0023U, /*!< Tier36PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER37_PRICE_LABEL_ID                    = 0x0024U, /*!< Tier37PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER38_PRICE_LABEL_ID                    = 0x0025U, /*!< Tier38PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER39_PRICE_LABEL_ID                    = 0x0026U, /*!< Tier39PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER40_PRICE_LABEL_ID                    = 0x0027U, /*!< Tier40PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER41_PRICE_LABEL_ID                    = 0x0028U, /*!< Tier41PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER42_PRICE_LABEL_ID                    = 0x0029U, /*!< Tier42PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER43_PRICE_LABEL_ID                    = 0x002AU, /*!< Tier43PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER44_PRICE_LABEL_ID                    = 0x002BU, /*!< Tier44PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER45_PRICE_LABEL_ID                    = 0x002CU, /*!< Tier45PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER46_PRICE_LABEL_ID                    = 0x002DU, /*!< Tier46PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER47_PRICE_LABEL_ID                    = 0x002EU, /*!< Tier47PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_TIER48_PRICE_LABEL_ID                    = 0x002FU, /*!< Tier48PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK1_THRESHOLD_ID                      = 0x0100U, /*!< Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK2_THRESHOLD_ID                      = 0x0101U, /*!< Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK3_THRESHOLD_ID                      = 0x0102U, /*!< Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK4_THRESHOLD_ID                      = 0x0103U, /*!< Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK5_THRESHOLD_ID                      = 0x0104U, /*!< Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK6_THRESHOLD_ID                      = 0x0105U, /*!< Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK7_THRESHOLD_ID                      = 0x0106U, /*!< Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK8_THRESHOLD_ID                      = 0x0107U, /*!< Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK9_THRESHOLD_ID                      = 0x0108U, /*!< Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK10_THRESHOLD_ID                     = 0x0109U, /*!< Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK11_THRESHOLD_ID                     = 0x010AU, /*!< Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK12_THRESHOLD_ID                     = 0x010BU, /*!< Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK13_THRESHOLD_ID                     = 0x010CU, /*!< Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK14_THRESHOLD_ID                     = 0x010DU, /*!< Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK15_THRESHOLD_ID                     = 0x010EU, /*!< Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK_THRESHOLD_COUNT_ID                 = 0x010FU, /*!< BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK1_THRESHOLD_ID                = 0x0110U, /*!< Tier1Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK2_THRESHOLD_ID                = 0x0111U, /*!< Tier1Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK3_THRESHOLD_ID                = 0x0112U, /*!< Tier1Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK4_THRESHOLD_ID                = 0x0113U, /*!< Tier1Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK5_THRESHOLD_ID                = 0x0114U, /*!< Tier1Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK6_THRESHOLD_ID                = 0x0115U, /*!< Tier1Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK7_THRESHOLD_ID                = 0x0116U, /*!< Tier1Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK8_THRESHOLD_ID                = 0x0117U, /*!< Tier1Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK9_THRESHOLD_ID                = 0x0118U, /*!< Tier1Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK10_THRESHOLD_ID               = 0x0119U, /*!< Tier1Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK11_THRESHOLD_ID               = 0x011AU, /*!< Tier1Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK12_THRESHOLD_ID               = 0x011BU, /*!< Tier1Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK13_THRESHOLD_ID               = 0x011CU, /*!< Tier1Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK14_THRESHOLD_ID               = 0x011DU, /*!< Tier1Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK15_THRESHOLD_ID               = 0x011EU, /*!< Tier1Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK_THRESHOLD_COUNT_ID           = 0x011FU, /*!< Tier1BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK1_THRESHOLD_ID                = 0x0120U, /*!< Tier2Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK2_THRESHOLD_ID                = 0x0121U, /*!< Tier2Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK3_THRESHOLD_ID                = 0x0122U, /*!< Tier2Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK4_THRESHOLD_ID                = 0x0123U, /*!< Tier2Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK5_THRESHOLD_ID                = 0x0124U, /*!< Tier2Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK6_THRESHOLD_ID                = 0x0125U, /*!< Tier2Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK7_THRESHOLD_ID                = 0x0126U, /*!< Tier2Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK8_THRESHOLD_ID                = 0x0127U, /*!< Tier2Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK9_THRESHOLD_ID                = 0x0128U, /*!< Tier2Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK10_THRESHOLD_ID               = 0x0129U, /*!< Tier2Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK11_THRESHOLD_ID               = 0x012AU, /*!< Tier2Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK12_THRESHOLD_ID               = 0x012BU, /*!< Tier2Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK13_THRESHOLD_ID               = 0x012CU, /*!< Tier2Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK14_THRESHOLD_ID               = 0x012DU, /*!< Tier2Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK15_THRESHOLD_ID               = 0x012EU, /*!< Tier2Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK_THRESHOLD_COUNT_ID           = 0x012FU, /*!< Tier2BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK1_THRESHOLD_ID                = 0x0130U, /*!< Tier3Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK2_THRESHOLD_ID                = 0x0131U, /*!< Tier3Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK3_THRESHOLD_ID                = 0x0132U, /*!< Tier3Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK4_THRESHOLD_ID                = 0x0133U, /*!< Tier3Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK5_THRESHOLD_ID                = 0x0134U, /*!< Tier3Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK6_THRESHOLD_ID                = 0x0135U, /*!< Tier3Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK7_THRESHOLD_ID                = 0x0136U, /*!< Tier3Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK8_THRESHOLD_ID                = 0x0137U, /*!< Tier3Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK9_THRESHOLD_ID                = 0x0138U, /*!< Tier3Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK10_THRESHOLD_ID               = 0x0139U, /*!< Tier3Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK11_THRESHOLD_ID               = 0x013AU, /*!< Tier3Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK12_THRESHOLD_ID               = 0x013BU, /*!< Tier3Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK13_THRESHOLD_ID               = 0x013CU, /*!< Tier3Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK14_THRESHOLD_ID               = 0x013DU, /*!< Tier3Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK15_THRESHOLD_ID               = 0x013EU, /*!< Tier3Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK_THRESHOLD_COUNT_ID           = 0x013FU, /*!< Tier3BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK1_THRESHOLD_ID                = 0x0140U, /*!< Tier4Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK2_THRESHOLD_ID                = 0x0141U, /*!< Tier4Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK3_THRESHOLD_ID                = 0x0142U, /*!< Tier4Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK4_THRESHOLD_ID                = 0x0143U, /*!< Tier4Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK5_THRESHOLD_ID                = 0x0144U, /*!< Tier4Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK6_THRESHOLD_ID                = 0x0145U, /*!< Tier4Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK7_THRESHOLD_ID                = 0x0146U, /*!< Tier4Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK8_THRESHOLD_ID                = 0x0147U, /*!< Tier4Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK9_THRESHOLD_ID                = 0x0148U, /*!< Tier4Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK10_THRESHOLD_ID               = 0x0149U, /*!< Tier4Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK11_THRESHOLD_ID               = 0x014AU, /*!< Tier4Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK12_THRESHOLD_ID               = 0x014BU, /*!< Tier4Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK13_THRESHOLD_ID               = 0x014CU, /*!< Tier4Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK14_THRESHOLD_ID               = 0x014DU, /*!< Tier4Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK15_THRESHOLD_ID               = 0x014EU, /*!< Tier4Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK_THRESHOLD_COUNT_ID           = 0x014FU, /*!< Tier4BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK1_THRESHOLD_ID                = 0x0150U, /*!< Tier5Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK2_THRESHOLD_ID                = 0x0151U, /*!< Tier5Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK3_THRESHOLD_ID                = 0x0152U, /*!< Tier5Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK4_THRESHOLD_ID                = 0x0153U, /*!< Tier5Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK5_THRESHOLD_ID                = 0x0154U, /*!< Tier5Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK6_THRESHOLD_ID                = 0x0155U, /*!< Tier5Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK7_THRESHOLD_ID                = 0x0156U, /*!< Tier5Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK8_THRESHOLD_ID                = 0x0157U, /*!< Tier5Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK9_THRESHOLD_ID                = 0x0158U, /*!< Tier5Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK10_THRESHOLD_ID               = 0x0159U, /*!< Tier5Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK11_THRESHOLD_ID               = 0x015AU, /*!< Tier5Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK12_THRESHOLD_ID               = 0x015BU, /*!< Tier5Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK13_THRESHOLD_ID               = 0x015CU, /*!< Tier5Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK14_THRESHOLD_ID               = 0x015DU, /*!< Tier5Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK15_THRESHOLD_ID               = 0x015EU, /*!< Tier5Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK_THRESHOLD_COUNT_ID           = 0x015FU, /*!< Tier5BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK1_THRESHOLD_ID                = 0x0160U, /*!< Tier6Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK2_THRESHOLD_ID                = 0x0161U, /*!< Tier6Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK3_THRESHOLD_ID                = 0x0162U, /*!< Tier6Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK4_THRESHOLD_ID                = 0x0163U, /*!< Tier6Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK5_THRESHOLD_ID                = 0x0164U, /*!< Tier6Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK6_THRESHOLD_ID                = 0x0165U, /*!< Tier6Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK7_THRESHOLD_ID                = 0x0166U, /*!< Tier6Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK8_THRESHOLD_ID                = 0x0167U, /*!< Tier6Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK9_THRESHOLD_ID                = 0x0168U, /*!< Tier6Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK10_THRESHOLD_ID               = 0x0169U, /*!< Tier6Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK11_THRESHOLD_ID               = 0x016AU, /*!< Tier6Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK12_THRESHOLD_ID               = 0x016BU, /*!< Tier6Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK13_THRESHOLD_ID               = 0x016CU, /*!< Tier6Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK14_THRESHOLD_ID               = 0x016DU, /*!< Tier6Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK15_THRESHOLD_ID               = 0x016EU, /*!< Tier6Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK_THRESHOLD_COUNT_ID           = 0x016FU, /*!< Tier6BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK1_THRESHOLD_ID                = 0x0170U, /*!< Tier7Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK2_THRESHOLD_ID                = 0x0171U, /*!< Tier7Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK3_THRESHOLD_ID                = 0x0172U, /*!< Tier7Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK4_THRESHOLD_ID                = 0x0173U, /*!< Tier7Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK5_THRESHOLD_ID                = 0x0174U, /*!< Tier7Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK6_THRESHOLD_ID                = 0x0175U, /*!< Tier7Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK7_THRESHOLD_ID                = 0x0176U, /*!< Tier7Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK8_THRESHOLD_ID                = 0x0177U, /*!< Tier7Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK9_THRESHOLD_ID                = 0x0178U, /*!< Tier7Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK10_THRESHOLD_ID               = 0x0179U, /*!< Tier7Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK11_THRESHOLD_ID               = 0x017AU, /*!< Tier7Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK12_THRESHOLD_ID               = 0x017BU, /*!< Tier7Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK13_THRESHOLD_ID               = 0x017CU, /*!< Tier7Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK14_THRESHOLD_ID               = 0x017DU, /*!< Tier7Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK15_THRESHOLD_ID               = 0x017EU, /*!< Tier7Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK_THRESHOLD_COUNT_ID           = 0x017FU, /*!< Tier7BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK1_THRESHOLD_ID                = 0x0180U, /*!< Tier8Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK2_THRESHOLD_ID                = 0x0181U, /*!< Tier8Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK3_THRESHOLD_ID                = 0x0182U, /*!< Tier8Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK4_THRESHOLD_ID                = 0x0183U, /*!< Tier8Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK5_THRESHOLD_ID                = 0x0184U, /*!< Tier8Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK6_THRESHOLD_ID                = 0x0185U, /*!< Tier8Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK7_THRESHOLD_ID                = 0x0186U, /*!< Tier8Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK8_THRESHOLD_ID                = 0x0187U, /*!< Tier8Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK9_THRESHOLD_ID                = 0x0188U, /*!< Tier8Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK10_THRESHOLD_ID               = 0x0189U, /*!< Tier8Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK11_THRESHOLD_ID               = 0x018AU, /*!< Tier8Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK12_THRESHOLD_ID               = 0x018BU, /*!< Tier8Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK13_THRESHOLD_ID               = 0x018CU, /*!< Tier8Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK14_THRESHOLD_ID               = 0x018DU, /*!< Tier8Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK15_THRESHOLD_ID               = 0x018EU, /*!< Tier8Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK_THRESHOLD_COUNT_ID           = 0x018FU, /*!< Tier8BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK1_THRESHOLD_ID                = 0x0190U, /*!< Tier9Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK2_THRESHOLD_ID                = 0x0191U, /*!< Tier9Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK3_THRESHOLD_ID                = 0x0192U, /*!< Tier9Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK4_THRESHOLD_ID                = 0x0193U, /*!< Tier9Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK5_THRESHOLD_ID                = 0x0194U, /*!< Tier9Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK6_THRESHOLD_ID                = 0x0195U, /*!< Tier9Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK7_THRESHOLD_ID                = 0x0196U, /*!< Tier9Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK8_THRESHOLD_ID                = 0x0197U, /*!< Tier9Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK9_THRESHOLD_ID                = 0x0198U, /*!< Tier9Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK10_THRESHOLD_ID               = 0x0199U, /*!< Tier9Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK11_THRESHOLD_ID               = 0x019AU, /*!< Tier9Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK12_THRESHOLD_ID               = 0x019BU, /*!< Tier9Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK13_THRESHOLD_ID               = 0x019CU, /*!< Tier9Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK14_THRESHOLD_ID               = 0x019DU, /*!< Tier9Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK15_THRESHOLD_ID               = 0x019EU, /*!< Tier9Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK_THRESHOLD_COUNT_ID           = 0x019FU, /*!< Tier9BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK1_THRESHOLD_ID               = 0x01A0U, /*!< Tier10Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK2_THRESHOLD_ID               = 0x01A1U, /*!< Tier10Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK3_THRESHOLD_ID               = 0x01A2U, /*!< Tier10Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK4_THRESHOLD_ID               = 0x01A3U, /*!< Tier10Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK5_THRESHOLD_ID               = 0x01A4U, /*!< Tier10Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK6_THRESHOLD_ID               = 0x01A5U, /*!< Tier10Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK7_THRESHOLD_ID               = 0x01A6U, /*!< Tier10Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK8_THRESHOLD_ID               = 0x01A7U, /*!< Tier10Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK9_THRESHOLD_ID               = 0x01A8U, /*!< Tier10Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK10_THRESHOLD_ID              = 0x01A9U, /*!< Tier10Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK11_THRESHOLD_ID              = 0x01AAU, /*!< Tier10Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK12_THRESHOLD_ID              = 0x01ABU, /*!< Tier10Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK13_THRESHOLD_ID              = 0x01ACU, /*!< Tier10Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK14_THRESHOLD_ID              = 0x01ADU, /*!< Tier10Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK15_THRESHOLD_ID              = 0x01AEU, /*!< Tier10Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK_THRESHOLD_COUNT_ID          = 0x01AFU, /*!< Tier10BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK1_THRESHOLD_ID               = 0x01B0U, /*!< Tier11Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK2_THRESHOLD_ID               = 0x01B1U, /*!< Tier11Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK3_THRESHOLD_ID               = 0x01B2U, /*!< Tier11Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK4_THRESHOLD_ID               = 0x01B3U, /*!< Tier11Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK5_THRESHOLD_ID               = 0x01B4U, /*!< Tier11Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK6_THRESHOLD_ID               = 0x01B5U, /*!< Tier11Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK7_THRESHOLD_ID               = 0x01B6U, /*!< Tier11Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK8_THRESHOLD_ID               = 0x01B7U, /*!< Tier11Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK9_THRESHOLD_ID               = 0x01B8U, /*!< Tier11Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK10_THRESHOLD_ID              = 0x01B9U, /*!< Tier11Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK11_THRESHOLD_ID              = 0x01BAU, /*!< Tier11Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK12_THRESHOLD_ID              = 0x01BBU, /*!< Tier11Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK13_THRESHOLD_ID              = 0x01BCU, /*!< Tier11Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK14_THRESHOLD_ID              = 0x01BDU, /*!< Tier11Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK15_THRESHOLD_ID              = 0x01BEU, /*!< Tier11Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK_THRESHOLD_COUNT_ID          = 0x01BFU, /*!< Tier11BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK1_THRESHOLD_ID               = 0x01C0U, /*!< Tier12Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK2_THRESHOLD_ID               = 0x01C1U, /*!< Tier12Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK3_THRESHOLD_ID               = 0x01C2U, /*!< Tier12Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK4_THRESHOLD_ID               = 0x01C3U, /*!< Tier12Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK5_THRESHOLD_ID               = 0x01C4U, /*!< Tier12Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK6_THRESHOLD_ID               = 0x01C5U, /*!< Tier12Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK7_THRESHOLD_ID               = 0x01C6U, /*!< Tier12Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK8_THRESHOLD_ID               = 0x01C7U, /*!< Tier12Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK9_THRESHOLD_ID               = 0x01C8U, /*!< Tier12Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK10_THRESHOLD_ID              = 0x01C9U, /*!< Tier12Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK11_THRESHOLD_ID              = 0x01CAU, /*!< Tier12Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK12_THRESHOLD_ID              = 0x01CBU, /*!< Tier12Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK13_THRESHOLD_ID              = 0x01CCU, /*!< Tier12Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK14_THRESHOLD_ID              = 0x01CDU, /*!< Tier12Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK15_THRESHOLD_ID              = 0x01CEU, /*!< Tier12Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK_THRESHOLD_COUNT_ID          = 0x01CFU, /*!< Tier12BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK1_THRESHOLD_ID               = 0x01D0U, /*!< Tier13Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK2_THRESHOLD_ID               = 0x01D1U, /*!< Tier13Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK3_THRESHOLD_ID               = 0x01D2U, /*!< Tier13Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK4_THRESHOLD_ID               = 0x01D3U, /*!< Tier13Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK5_THRESHOLD_ID               = 0x01D4U, /*!< Tier13Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK6_THRESHOLD_ID               = 0x01D5U, /*!< Tier13Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK7_THRESHOLD_ID               = 0x01D6U, /*!< Tier13Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK8_THRESHOLD_ID               = 0x01D7U, /*!< Tier13Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK9_THRESHOLD_ID               = 0x01D8U, /*!< Tier13Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK10_THRESHOLD_ID              = 0x01D9U, /*!< Tier13Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK11_THRESHOLD_ID              = 0x01DAU, /*!< Tier13Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK12_THRESHOLD_ID              = 0x01DBU, /*!< Tier13Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK13_THRESHOLD_ID              = 0x01DCU, /*!< Tier13Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK14_THRESHOLD_ID              = 0x01DDU, /*!< Tier13Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK15_THRESHOLD_ID              = 0x01DEU, /*!< Tier13Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK_THRESHOLD_COUNT_ID          = 0x01DFU, /*!< Tier13BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK1_THRESHOLD_ID               = 0x01E0U, /*!< Tier14Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK2_THRESHOLD_ID               = 0x01E1U, /*!< Tier14Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK3_THRESHOLD_ID               = 0x01E2U, /*!< Tier14Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK4_THRESHOLD_ID               = 0x01E3U, /*!< Tier14Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK5_THRESHOLD_ID               = 0x01E4U, /*!< Tier14Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK6_THRESHOLD_ID               = 0x01E5U, /*!< Tier14Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK7_THRESHOLD_ID               = 0x01E6U, /*!< Tier14Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK8_THRESHOLD_ID               = 0x01E7U, /*!< Tier14Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK9_THRESHOLD_ID               = 0x01E8U, /*!< Tier14Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK10_THRESHOLD_ID              = 0x01E9U, /*!< Tier14Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK11_THRESHOLD_ID              = 0x01EAU, /*!< Tier14Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK12_THRESHOLD_ID              = 0x01EBU, /*!< Tier14Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK13_THRESHOLD_ID              = 0x01ECU, /*!< Tier14Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK14_THRESHOLD_ID              = 0x01EDU, /*!< Tier14Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK15_THRESHOLD_ID              = 0x01EEU, /*!< Tier14Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK_THRESHOLD_COUNT_ID          = 0x01EFU, /*!< Tier14BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK1_THRESHOLD_ID               = 0x01F0U, /*!< Tier15Block1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK2_THRESHOLD_ID               = 0x01F1U, /*!< Tier15Block2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK3_THRESHOLD_ID               = 0x01F2U, /*!< Tier15Block3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK4_THRESHOLD_ID               = 0x01F3U, /*!< Tier15Block4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK5_THRESHOLD_ID               = 0x01F4U, /*!< Tier15Block5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK6_THRESHOLD_ID               = 0x01F5U, /*!< Tier15Block6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK7_THRESHOLD_ID               = 0x01F6U, /*!< Tier15Block7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK8_THRESHOLD_ID               = 0x01F7U, /*!< Tier15Block8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK9_THRESHOLD_ID               = 0x01F8U, /*!< Tier15Block9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK10_THRESHOLD_ID              = 0x01F9U, /*!< Tier15Block10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK11_THRESHOLD_ID              = 0x01FAU, /*!< Tier15Block11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK12_THRESHOLD_ID              = 0x01FBU, /*!< Tier15Block12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK13_THRESHOLD_ID              = 0x01FCU, /*!< Tier15Block13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK14_THRESHOLD_ID              = 0x01FDU, /*!< Tier15Block14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK15_THRESHOLD_ID              = 0x01FEU, /*!< Tier15Block15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK_THRESHOLD_COUNT_ID          = 0x01FFU, /*!< Tier15BlockThresholdCount attribute. */
    EZB_ZCL_ATTR_PRICE_START_OF_BLOCK_PERIOD_ID                 = 0x0200U, /*!< StartOfBlockPeriod attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK_PERIOD_DURATION_ID                 = 0x0201U, /*!< BlockPeriodDuration attribute. */
    EZB_ZCL_ATTR_PRICE_THRESHOLD_MULTIPLIER_ID                  = 0x0202U, /*!< ThresholdMultiplier attribute. */
    EZB_ZCL_ATTR_PRICE_THRESHOLD_DIVISOR_ID                     = 0x0203U, /*!< ThresholdDivisor attribute. */
    EZB_ZCL_ATTR_PRICE_BLOCK_PERIOD_DURATION_TYPE_ID            = 0x0204U, /*!< BlockPeriodDurationType attribute. */
    EZB_ZCL_ATTR_PRICE_COMMODITY_TYPE_ID                        = 0x0300U, /*!< CommodityType attribute. */
    EZB_ZCL_ATTR_PRICE_STANDING_CHARGE_ID                       = 0x0301U, /*!< StandingCharge attribute. */
    EZB_ZCL_ATTR_PRICE_CONVERSION_FACTOR_ID                     = 0x0302U, /*!< ConversionFactor attribute. */
    EZB_ZCL_ATTR_PRICE_CONVERSION_FACTOR_TRAILING_DIGIT_ID      = 0x0303U, /*!< ConversionFactorTrailingDigit attribute. */
    EZB_ZCL_ATTR_PRICE_CALORIFIC_VALUE_ID                       = 0x0304U, /*!< CalorificValue attribute. */
    EZB_ZCL_ATTR_PRICE_CALORIFIC_VALUE_UNIT_ID                  = 0x0305U, /*!< CalorificValueUnit attribute. */
    EZB_ZCL_ATTR_PRICE_CALORIFIC_VALUE_TRAILING_DIGIT_ID        = 0x0306U, /*!< CalorificValueTrailingDigit attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK1_PRICE_ID                  = 0x0400U, /*!< NoTierBlock1Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK2_PRICE_ID                  = 0x0401U, /*!< NoTierBlock2Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK3_PRICE_ID                  = 0x0402U, /*!< NoTierBlock3Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK4_PRICE_ID                  = 0x0403U, /*!< NoTierBlock4Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK5_PRICE_ID                  = 0x0404U, /*!< NoTierBlock5Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK6_PRICE_ID                  = 0x0405U, /*!< NoTierBlock6Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK7_PRICE_ID                  = 0x0406U, /*!< NoTierBlock7Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK8_PRICE_ID                  = 0x0407U, /*!< NoTierBlock8Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK9_PRICE_ID                  = 0x0408U, /*!< NoTierBlock9Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK10_PRICE_ID                 = 0x0409U, /*!< NoTierBlock10Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK11_PRICE_ID                 = 0x040AU, /*!< NoTierBlock11Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK12_PRICE_ID                 = 0x040BU, /*!< NoTierBlock12Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK13_PRICE_ID                 = 0x040CU, /*!< NoTierBlock13Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK14_PRICE_ID                 = 0x040DU, /*!< NoTierBlock14Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK15_PRICE_ID                 = 0x040EU, /*!< NoTierBlock15Price attribute. */
    EZB_ZCL_ATTR_PRICE_NO_TIER_BLOCK16_PRICE_ID                 = 0x040FU, /*!< NoTierBlock16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK1_PRICE_ID                    = 0x0410U, /*!< Tier1Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK2_PRICE_ID                    = 0x0411U, /*!< Tier1Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK3_PRICE_ID                    = 0x0412U, /*!< Tier1Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK4_PRICE_ID                    = 0x0413U, /*!< Tier1Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK5_PRICE_ID                    = 0x0414U, /*!< Tier1Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK6_PRICE_ID                    = 0x0415U, /*!< Tier1Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK7_PRICE_ID                    = 0x0416U, /*!< Tier1Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK8_PRICE_ID                    = 0x0417U, /*!< Tier1Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK9_PRICE_ID                    = 0x0418U, /*!< Tier1Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK10_PRICE_ID                   = 0x0419U, /*!< Tier1Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK11_PRICE_ID                   = 0x041AU, /*!< Tier1Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK12_PRICE_ID                   = 0x041BU, /*!< Tier1Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK13_PRICE_ID                   = 0x041CU, /*!< Tier1Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK14_PRICE_ID                   = 0x041DU, /*!< Tier1Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK15_PRICE_ID                   = 0x041EU, /*!< Tier1Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER1_BLOCK16_PRICE_ID                   = 0x041FU, /*!< Tier1Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK1_PRICE_ID                    = 0x0420U, /*!< Tier2Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK2_PRICE_ID                    = 0x0421U, /*!< Tier2Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK3_PRICE_ID                    = 0x0422U, /*!< Tier2Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK4_PRICE_ID                    = 0x0423U, /*!< Tier2Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK5_PRICE_ID                    = 0x0424U, /*!< Tier2Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK6_PRICE_ID                    = 0x0425U, /*!< Tier2Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK7_PRICE_ID                    = 0x0426U, /*!< Tier2Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK8_PRICE_ID                    = 0x0427U, /*!< Tier2Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK9_PRICE_ID                    = 0x0428U, /*!< Tier2Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK10_PRICE_ID                   = 0x0429U, /*!< Tier2Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK11_PRICE_ID                   = 0x042AU, /*!< Tier2Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK12_PRICE_ID                   = 0x042BU, /*!< Tier2Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK13_PRICE_ID                   = 0x042CU, /*!< Tier2Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK14_PRICE_ID                   = 0x042DU, /*!< Tier2Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK15_PRICE_ID                   = 0x042EU, /*!< Tier2Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER2_BLOCK16_PRICE_ID                   = 0x042FU, /*!< Tier2Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK1_PRICE_ID                    = 0x0430U, /*!< Tier3Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK2_PRICE_ID                    = 0x0431U, /*!< Tier3Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK3_PRICE_ID                    = 0x0432U, /*!< Tier3Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK4_PRICE_ID                    = 0x0433U, /*!< Tier3Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK5_PRICE_ID                    = 0x0434U, /*!< Tier3Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK6_PRICE_ID                    = 0x0435U, /*!< Tier3Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK7_PRICE_ID                    = 0x0436U, /*!< Tier3Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK8_PRICE_ID                    = 0x0437U, /*!< Tier3Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK9_PRICE_ID                    = 0x0438U, /*!< Tier3Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK10_PRICE_ID                   = 0x0439U, /*!< Tier3Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK11_PRICE_ID                   = 0x043AU, /*!< Tier3Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK12_PRICE_ID                   = 0x043BU, /*!< Tier3Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK13_PRICE_ID                   = 0x043CU, /*!< Tier3Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK14_PRICE_ID                   = 0x043DU, /*!< Tier3Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK15_PRICE_ID                   = 0x043EU, /*!< Tier3Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER3_BLOCK16_PRICE_ID                   = 0x043FU, /*!< Tier3Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK1_PRICE_ID                    = 0x0440U, /*!< Tier4Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK2_PRICE_ID                    = 0x0441U, /*!< Tier4Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK3_PRICE_ID                    = 0x0442U, /*!< Tier4Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK4_PRICE_ID                    = 0x0443U, /*!< Tier4Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK5_PRICE_ID                    = 0x0444U, /*!< Tier4Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK6_PRICE_ID                    = 0x0445U, /*!< Tier4Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK7_PRICE_ID                    = 0x0446U, /*!< Tier4Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK8_PRICE_ID                    = 0x0447U, /*!< Tier4Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK9_PRICE_ID                    = 0x0448U, /*!< Tier4Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK10_PRICE_ID                   = 0x0449U, /*!< Tier4Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK11_PRICE_ID                   = 0x044AU, /*!< Tier4Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK12_PRICE_ID                   = 0x044BU, /*!< Tier4Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK13_PRICE_ID                   = 0x044CU, /*!< Tier4Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK14_PRICE_ID                   = 0x044DU, /*!< Tier4Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK15_PRICE_ID                   = 0x044EU, /*!< Tier4Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER4_BLOCK16_PRICE_ID                   = 0x044FU, /*!< Tier4Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK1_PRICE_ID                    = 0x0450U, /*!< Tier5Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK2_PRICE_ID                    = 0x0451U, /*!< Tier5Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK3_PRICE_ID                    = 0x0452U, /*!< Tier5Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK4_PRICE_ID                    = 0x0453U, /*!< Tier5Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK5_PRICE_ID                    = 0x0454U, /*!< Tier5Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK6_PRICE_ID                    = 0x0455U, /*!< Tier5Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK7_PRICE_ID                    = 0x0456U, /*!< Tier5Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK8_PRICE_ID                    = 0x0457U, /*!< Tier5Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK9_PRICE_ID                    = 0x0458U, /*!< Tier5Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK10_PRICE_ID                   = 0x0459U, /*!< Tier5Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK11_PRICE_ID                   = 0x045AU, /*!< Tier5Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK12_PRICE_ID                   = 0x045BU, /*!< Tier5Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK13_PRICE_ID                   = 0x045CU, /*!< Tier5Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK14_PRICE_ID                   = 0x045DU, /*!< Tier5Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK15_PRICE_ID                   = 0x045EU, /*!< Tier5Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER5_BLOCK16_PRICE_ID                   = 0x045FU, /*!< Tier5Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK1_PRICE_ID                    = 0x0460U, /*!< Tier6Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK2_PRICE_ID                    = 0x0461U, /*!< Tier6Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK3_PRICE_ID                    = 0x0462U, /*!< Tier6Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK4_PRICE_ID                    = 0x0463U, /*!< Tier6Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK5_PRICE_ID                    = 0x0464U, /*!< Tier6Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK6_PRICE_ID                    = 0x0465U, /*!< Tier6Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK7_PRICE_ID                    = 0x0466U, /*!< Tier6Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK8_PRICE_ID                    = 0x0467U, /*!< Tier6Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK9_PRICE_ID                    = 0x0468U, /*!< Tier6Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK10_PRICE_ID                   = 0x0469U, /*!< Tier6Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK11_PRICE_ID                   = 0x046AU, /*!< Tier6Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK12_PRICE_ID                   = 0x046BU, /*!< Tier6Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK13_PRICE_ID                   = 0x046CU, /*!< Tier6Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK14_PRICE_ID                   = 0x046DU, /*!< Tier6Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK15_PRICE_ID                   = 0x046EU, /*!< Tier6Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER6_BLOCK16_PRICE_ID                   = 0x046FU, /*!< Tier6Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK1_PRICE_ID                    = 0x0470U, /*!< Tier7Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK2_PRICE_ID                    = 0x0471U, /*!< Tier7Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK3_PRICE_ID                    = 0x0472U, /*!< Tier7Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK4_PRICE_ID                    = 0x0473U, /*!< Tier7Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK5_PRICE_ID                    = 0x0474U, /*!< Tier7Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK6_PRICE_ID                    = 0x0475U, /*!< Tier7Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK7_PRICE_ID                    = 0x0476U, /*!< Tier7Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK8_PRICE_ID                    = 0x0477U, /*!< Tier7Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK9_PRICE_ID                    = 0x0478U, /*!< Tier7Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK10_PRICE_ID                   = 0x0479U, /*!< Tier7Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK11_PRICE_ID                   = 0x047AU, /*!< Tier7Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK12_PRICE_ID                   = 0x047BU, /*!< Tier7Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK13_PRICE_ID                   = 0x047CU, /*!< Tier7Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK14_PRICE_ID                   = 0x047DU, /*!< Tier7Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK15_PRICE_ID                   = 0x047EU, /*!< Tier7Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER7_BLOCK16_PRICE_ID                   = 0x047FU, /*!< Tier7Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK1_PRICE_ID                    = 0x0480U, /*!< Tier8Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK2_PRICE_ID                    = 0x0481U, /*!< Tier8Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK3_PRICE_ID                    = 0x0482U, /*!< Tier8Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK4_PRICE_ID                    = 0x0483U, /*!< Tier8Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK5_PRICE_ID                    = 0x0484U, /*!< Tier8Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK6_PRICE_ID                    = 0x0485U, /*!< Tier8Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK7_PRICE_ID                    = 0x0486U, /*!< Tier8Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK8_PRICE_ID                    = 0x0487U, /*!< Tier8Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK9_PRICE_ID                    = 0x0488U, /*!< Tier8Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK10_PRICE_ID                   = 0x0489U, /*!< Tier8Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK11_PRICE_ID                   = 0x048AU, /*!< Tier8Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK12_PRICE_ID                   = 0x048BU, /*!< Tier8Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK13_PRICE_ID                   = 0x048CU, /*!< Tier8Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK14_PRICE_ID                   = 0x048DU, /*!< Tier8Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK15_PRICE_ID                   = 0x048EU, /*!< Tier8Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER8_BLOCK16_PRICE_ID                   = 0x048FU, /*!< Tier8Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK1_PRICE_ID                    = 0x0490U, /*!< Tier9Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK2_PRICE_ID                    = 0x0491U, /*!< Tier9Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK3_PRICE_ID                    = 0x0492U, /*!< Tier9Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK4_PRICE_ID                    = 0x0493U, /*!< Tier9Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK5_PRICE_ID                    = 0x0494U, /*!< Tier9Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK6_PRICE_ID                    = 0x0495U, /*!< Tier9Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK7_PRICE_ID                    = 0x0496U, /*!< Tier9Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK8_PRICE_ID                    = 0x0497U, /*!< Tier9Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK9_PRICE_ID                    = 0x0498U, /*!< Tier9Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK10_PRICE_ID                   = 0x0499U, /*!< Tier9Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK11_PRICE_ID                   = 0x049AU, /*!< Tier9Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK12_PRICE_ID                   = 0x049BU, /*!< Tier9Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK13_PRICE_ID                   = 0x049CU, /*!< Tier9Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK14_PRICE_ID                   = 0x049DU, /*!< Tier9Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK15_PRICE_ID                   = 0x049EU, /*!< Tier9Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER9_BLOCK16_PRICE_ID                   = 0x049FU, /*!< Tier9Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK1_PRICE_ID                   = 0x04A0U, /*!< Tier10Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK2_PRICE_ID                   = 0x04A1U, /*!< Tier10Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK3_PRICE_ID                   = 0x04A2U, /*!< Tier10Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK4_PRICE_ID                   = 0x04A3U, /*!< Tier10Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK5_PRICE_ID                   = 0x04A4U, /*!< Tier10Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK6_PRICE_ID                   = 0x04A5U, /*!< Tier10Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK7_PRICE_ID                   = 0x04A6U, /*!< Tier10Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK8_PRICE_ID                   = 0x04A7U, /*!< Tier10Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK9_PRICE_ID                   = 0x04A8U, /*!< Tier10Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK10_PRICE_ID                  = 0x04A9U, /*!< Tier10Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK11_PRICE_ID                  = 0x04AAU, /*!< Tier10Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK12_PRICE_ID                  = 0x04ABU, /*!< Tier10Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK13_PRICE_ID                  = 0x04ACU, /*!< Tier10Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK14_PRICE_ID                  = 0x04ADU, /*!< Tier10Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK15_PRICE_ID                  = 0x04AEU, /*!< Tier10Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER10_BLOCK16_PRICE_ID                  = 0x04AFU, /*!< Tier10Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK1_PRICE_ID                   = 0x04B0U, /*!< Tier11Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK2_PRICE_ID                   = 0x04B1U, /*!< Tier11Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK3_PRICE_ID                   = 0x04B2U, /*!< Tier11Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK4_PRICE_ID                   = 0x04B3U, /*!< Tier11Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK5_PRICE_ID                   = 0x04B4U, /*!< Tier11Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK6_PRICE_ID                   = 0x04B5U, /*!< Tier11Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK7_PRICE_ID                   = 0x04B6U, /*!< Tier11Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK8_PRICE_ID                   = 0x04B7U, /*!< Tier11Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK9_PRICE_ID                   = 0x04B8U, /*!< Tier11Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK10_PRICE_ID                  = 0x04B9U, /*!< Tier11Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK11_PRICE_ID                  = 0x04BAU, /*!< Tier11Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK12_PRICE_ID                  = 0x04BBU, /*!< Tier11Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK13_PRICE_ID                  = 0x04BCU, /*!< Tier11Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK14_PRICE_ID                  = 0x04BDU, /*!< Tier11Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK15_PRICE_ID                  = 0x04BEU, /*!< Tier11Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER11_BLOCK16_PRICE_ID                  = 0x04BFU, /*!< Tier11Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK1_PRICE_ID                   = 0x04C0U, /*!< Tier12Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK2_PRICE_ID                   = 0x04C1U, /*!< Tier12Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK3_PRICE_ID                   = 0x04C2U, /*!< Tier12Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK4_PRICE_ID                   = 0x04C3U, /*!< Tier12Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK5_PRICE_ID                   = 0x04C4U, /*!< Tier12Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK6_PRICE_ID                   = 0x04C5U, /*!< Tier12Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK7_PRICE_ID                   = 0x04C6U, /*!< Tier12Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK8_PRICE_ID                   = 0x04C7U, /*!< Tier12Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK9_PRICE_ID                   = 0x04C8U, /*!< Tier12Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK10_PRICE_ID                  = 0x04C9U, /*!< Tier12Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK11_PRICE_ID                  = 0x04CAU, /*!< Tier12Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK12_PRICE_ID                  = 0x04CBU, /*!< Tier12Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK13_PRICE_ID                  = 0x04CCU, /*!< Tier12Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK14_PRICE_ID                  = 0x04CDU, /*!< Tier12Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK15_PRICE_ID                  = 0x04CEU, /*!< Tier12Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER12_BLOCK16_PRICE_ID                  = 0x04CFU, /*!< Tier12Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK1_PRICE_ID                   = 0x04D0U, /*!< Tier13Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK2_PRICE_ID                   = 0x04D1U, /*!< Tier13Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK3_PRICE_ID                   = 0x04D2U, /*!< Tier13Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK4_PRICE_ID                   = 0x04D3U, /*!< Tier13Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK5_PRICE_ID                   = 0x04D4U, /*!< Tier13Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK6_PRICE_ID                   = 0x04D5U, /*!< Tier13Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK7_PRICE_ID                   = 0x04D6U, /*!< Tier13Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK8_PRICE_ID                   = 0x04D7U, /*!< Tier13Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK9_PRICE_ID                   = 0x04D8U, /*!< Tier13Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK10_PRICE_ID                  = 0x04D9U, /*!< Tier13Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK11_PRICE_ID                  = 0x04DAU, /*!< Tier13Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK12_PRICE_ID                  = 0x04DBU, /*!< Tier13Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK13_PRICE_ID                  = 0x04DCU, /*!< Tier13Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK14_PRICE_ID                  = 0x04DDU, /*!< Tier13Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK15_PRICE_ID                  = 0x04DEU, /*!< Tier13Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER13_BLOCK16_PRICE_ID                  = 0x04DFU, /*!< Tier13Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK1_PRICE_ID                   = 0x04E0U, /*!< Tier14Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK2_PRICE_ID                   = 0x04E1U, /*!< Tier14Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK3_PRICE_ID                   = 0x04E2U, /*!< Tier14Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK4_PRICE_ID                   = 0x04E3U, /*!< Tier14Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK5_PRICE_ID                   = 0x04E4U, /*!< Tier14Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK6_PRICE_ID                   = 0x04E5U, /*!< Tier14Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK7_PRICE_ID                   = 0x04E6U, /*!< Tier14Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK8_PRICE_ID                   = 0x04E7U, /*!< Tier14Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK9_PRICE_ID                   = 0x04E8U, /*!< Tier14Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK10_PRICE_ID                  = 0x04E9U, /*!< Tier14Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK11_PRICE_ID                  = 0x04EAU, /*!< Tier14Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK12_PRICE_ID                  = 0x04EBU, /*!< Tier14Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK13_PRICE_ID                  = 0x04ECU, /*!< Tier14Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK14_PRICE_ID                  = 0x04EDU, /*!< Tier14Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK15_PRICE_ID                  = 0x04EEU, /*!< Tier14Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER14_BLOCK16_PRICE_ID                  = 0x04EFU, /*!< Tier14Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK1_PRICE_ID                   = 0x04F0U, /*!< Tier15Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK2_PRICE_ID                   = 0x04F1U, /*!< Tier15Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK3_PRICE_ID                   = 0x04F2U, /*!< Tier15Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK4_PRICE_ID                   = 0x04F3U, /*!< Tier15Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK5_PRICE_ID                   = 0x04F4U, /*!< Tier15Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK6_PRICE_ID                   = 0x04F5U, /*!< Tier15Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK7_PRICE_ID                   = 0x04F6U, /*!< Tier15Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK8_PRICE_ID                   = 0x04F7U, /*!< Tier15Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK9_PRICE_ID                   = 0x04F8U, /*!< Tier15Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK10_PRICE_ID                  = 0x04F9U, /*!< Tier15Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK11_PRICE_ID                  = 0x04FAU, /*!< Tier15Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK12_PRICE_ID                  = 0x04FBU, /*!< Tier15Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK13_PRICE_ID                  = 0x04FCU, /*!< Tier15Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK14_PRICE_ID                  = 0x04FDU, /*!< Tier15Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK15_PRICE_ID                  = 0x04FEU, /*!< Tier15Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_TIER15_BLOCK16_PRICE_ID                  = 0x04FFU, /*!< Tier15Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER16_ID                          = 0x050FU, /*!< PriceTier16 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER17_ID                          = 0x0510U, /*!< PriceTier17 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER18_ID                          = 0x0511U, /*!< PriceTier18 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER19_ID                          = 0x0512U, /*!< PriceTier19 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER20_ID                          = 0x0513U, /*!< PriceTier20 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER21_ID                          = 0x0514U, /*!< PriceTier21 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER22_ID                          = 0x0515U, /*!< PriceTier22 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER23_ID                          = 0x0516U, /*!< PriceTier23 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER24_ID                          = 0x0517U, /*!< PriceTier24 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER25_ID                          = 0x0518U, /*!< PriceTier25 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER26_ID                          = 0x0519U, /*!< PriceTier26 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER27_ID                          = 0x051AU, /*!< PriceTier27 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER28_ID                          = 0x051BU, /*!< PriceTier28 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER29_ID                          = 0x051CU, /*!< PriceTier29 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER30_ID                          = 0x051DU, /*!< PriceTier30 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER31_ID                          = 0x051EU, /*!< PriceTier31 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER32_ID                          = 0x051FU, /*!< PriceTier32 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER33_ID                          = 0x0520U, /*!< PriceTier33 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER34_ID                          = 0x0521U, /*!< PriceTier34 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER35_ID                          = 0x0522U, /*!< PriceTier35 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER36_ID                          = 0x0523U, /*!< PriceTier36 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER37_ID                          = 0x0524U, /*!< PriceTier37 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER38_ID                          = 0x0525U, /*!< PriceTier38 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER39_ID                          = 0x0526U, /*!< PriceTier39 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER40_ID                          = 0x0527U, /*!< PriceTier40 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER41_ID                          = 0x0528U, /*!< PriceTier41 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER42_ID                          = 0x0529U, /*!< PriceTier42 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER43_ID                          = 0x052AU, /*!< PriceTier43 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER44_ID                          = 0x052BU, /*!< PriceTier44 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER45_ID                          = 0x052CU, /*!< PriceTier45 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER46_ID                          = 0x052DU, /*!< PriceTier46 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER47_ID                          = 0x052EU, /*!< PriceTier47 attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TIER48_ID                          = 0x052FU, /*!< PriceTier48 attribute. */
    EZB_ZCL_ATTR_PRICE_CPP1_PRICE_ID                            = 0x05FEU, /*!< CPP1Price attribute. */
    EZB_ZCL_ATTR_PRICE_CPP2_PRICE_ID                            = 0x05FFU, /*!< CPP2Price attribute. */
    EZB_ZCL_ATTR_PRICE_TARIFF_LABEL_ID                          = 0x0610U, /*!< TariffLabel attribute. */
    EZB_ZCL_ATTR_PRICE_NUMBER_OF_PRICE_TIERS_IN_USE_ID          = 0x0611U, /*!< NumberOfPriceTiersInUse attribute. */
    EZB_ZCL_ATTR_PRICE_NUMBER_OF_BLOCK_THRESHOLDS_IN_USE_ID     = 0x0612U, /*!< NumberOfBlockThresholdsInUse attribute. */
    EZB_ZCL_ATTR_PRICE_TIER_BLOCK_MODE_ID                       = 0x0613U, /*!< TierBlockMode attribute. */
    EZB_ZCL_ATTR_PRICE_UNIT_OF_MEASURE_ID                       = 0x0615U, /*!< UnitOfMeasure attribute. */
    EZB_ZCL_ATTR_PRICE_CURRENCY_ID                              = 0x0616U, /*!< Currency attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_TRAILING_DIGIT_ID                  = 0x0617U, /*!< PriceTrailingDigit attribute. */
    EZB_ZCL_ATTR_PRICE_TARIFF_RESOLUTION_PERIOD_ID              = 0x0619U, /*!< TariffResolutionPeriod attribute. */
    EZB_ZCL_ATTR_PRICE_CO2_ID                                   = 0x0620U, /*!< Co2 attribute. */
    EZB_ZCL_ATTR_PRICE_CO2_UNIT_ID                              = 0x0621U, /*!< CO2Unit attribute. */
    EZB_ZCL_ATTR_PRICE_CO2_TRAILING_DIGIT_ID                    = 0x0622U, /*!< CO2TrailingDigit attribute. */
    EZB_ZCL_ATTR_PRICE_CURRENT_BILLING_PERIOD_START_ID          = 0x0700U, /*!< CurrentBillingPeriodStart attribute. */
    EZB_ZCL_ATTR_PRICE_LAST_BILLING_PERIOD_CONSOLIDATED_BILL_ID = 0x0704U, /*!< LastBillingPeriodConsolidatedBill attribute. */
    EZB_ZCL_ATTR_PRICE_CURRENT_BILLING_PERIOD_DURATION_ID       = 0x0701U, /*!< CurrentBillingPeriodDuration attribute. */
    EZB_ZCL_ATTR_PRICE_LAST_BILLING_PERIOD_START_ID             = 0x0702U, /*!< LastBillingPeriodStart attribute. */
    EZB_ZCL_ATTR_PRICE_LAST_BILLING_PERIOD_DURATION_ID          = 0x0703U, /*!< LastBillingPeriodDuration attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_DUE_DATE_ID               = 0x0800U, /*!< CreditPaymentDueDate attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_STATUS_ID                 = 0x0801U, /*!< CreditPaymentStatus attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_OVER_DUE_AMOUNT_ID        = 0x0802U, /*!< CreditPaymentOverDueAmount attribute. */
    EZB_ZCL_ATTR_PRICE_PAYMENT_DISCOUNT_ID                      = 0x080AU, /*!< PaymentDiscount attribute. */
    EZB_ZCL_ATTR_PRICE_PAYMENT_DISCOUNT_PERIOD_ID               = 0x080BU, /*!< PaymentDiscountPeriod attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT1_ID                       = 0x0810U, /*!< CreditPayment1 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_DATE1_ID                  = 0x0811U, /*!< CreditPaymentDate1 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_REF1_ID                   = 0x0812U, /*!< CreditPaymentRef1 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT2_ID                       = 0x0820U, /*!< CreditPayment2 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_DATE2_ID                  = 0x0821U, /*!< CreditPaymentDate2 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_REF2_ID                   = 0x0822U, /*!< CreditPaymentRef2 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT3_ID                       = 0x0830U, /*!< CreditPayment3 attribute. */
    EZB_ZCL_ATTR_PRICE_LAST_BILLI_CREDIT_PAYMENT_DATE3_ID       = 0x0831U, /*!< LastBilliCreditPaymentDate3 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_REF3_ID                   = 0x0832U, /*!< CreditPaymentRef3 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT4_ID                       = 0x0840U, /*!< CreditPayment4 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_DATE4_ID                  = 0x0841U, /*!< CreditPaymentDate4 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_REF4_ID                   = 0x0842U, /*!< CreditPaymentRef4 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT5_ID                       = 0x0850U, /*!< CreditPayment5 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_DATE5_ID                  = 0x0851U, /*!< CreditPaymentDate5 attribute. */
    EZB_ZCL_ATTR_PRICE_CREDIT_PAYMENT_REF5_ID                   = 0x0852U, /*!< CreditPaymentRef5 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER1_PRICE_LABEL_ID            = 0x8000U, /*!< ReceivedTier1PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER2_PRICE_LABEL_ID            = 0x8001U, /*!< ReceivedTier2PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER3_PRICE_LABEL_ID            = 0x8002U, /*!< ReceivedTier3PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER4_PRICE_LABEL_ID            = 0x8003U, /*!< ReceivedTier4PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER5_PRICE_LABEL_ID            = 0x8004U, /*!< ReceivedTier5PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER6_PRICE_LABEL_ID            = 0x8005U, /*!< ReceivedTier6PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER7_PRICE_LABEL_ID            = 0x8006U, /*!< ReceivedTier7PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER8_PRICE_LABEL_ID            = 0x8007U, /*!< ReceivedTier8PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER9_PRICE_LABEL_ID            = 0x8008U, /*!< ReceivedTier9PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER10_PRICE_LABEL_ID           = 0x8009U, /*!< ReceivedTier10PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER11_PRICE_LABEL_ID           = 0x800AU, /*!< ReceivedTier11PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER12_PRICE_LABEL_ID           = 0x800BU, /*!< ReceivedTier12PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER13_PRICE_LABEL_ID           = 0x800CU, /*!< ReceivedTier13PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER14_PRICE_LABEL_ID           = 0x800DU, /*!< ReceivedTier14PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER15_PRICE_LABEL_ID           = 0x800EU, /*!< ReceivedTier15PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER16_PRICE_LABEL_ID           = 0x800FU, /*!< ReceivedTier16PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER17_PRICE_LABEL_ID           = 0x8010U, /*!< ReceivedTier17PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER18_PRICE_LABEL_ID           = 0x8011U, /*!< ReceivedTier18PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER19_PRICE_LABEL_ID           = 0x8012U, /*!< ReceivedTier19PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER20_PRICE_LABEL_ID           = 0x8013U, /*!< ReceivedTier20PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER21_PRICE_LABEL_ID           = 0x8014U, /*!< ReceivedTier21PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER22_PRICE_LABEL_ID           = 0x8015U, /*!< ReceivedTier22PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER23_PRICE_LABEL_ID           = 0x8016U, /*!< ReceivedTier23PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER24_PRICE_LABEL_ID           = 0x8017U, /*!< ReceivedTier24PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER25_PRICE_LABEL_ID           = 0x8018U, /*!< ReceivedTier25PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER26_PRICE_LABEL_ID           = 0x8019U, /*!< ReceivedTier26PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER27_PRICE_LABEL_ID           = 0x801AU, /*!< ReceivedTier27PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER28_PRICE_LABEL_ID           = 0x801BU, /*!< ReceivedTier28PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER29_PRICE_LABEL_ID           = 0x801CU, /*!< ReceivedTier29PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER30_PRICE_LABEL_ID           = 0x801DU, /*!< ReceivedTier30PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER31_PRICE_LABEL_ID           = 0x801EU, /*!< ReceivedTier31PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER32_PRICE_LABEL_ID           = 0x801FU, /*!< ReceivedTier32PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER33_PRICE_LABEL_ID           = 0x8020U, /*!< ReceivedTier33PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER34_PRICE_LABEL_ID           = 0x8021U, /*!< ReceivedTier34PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER35_PRICE_LABEL_ID           = 0x8022U, /*!< ReceivedTier35PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER36_PRICE_LABEL_ID           = 0x8023U, /*!< ReceivedTier36PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER37_PRICE_LABEL_ID           = 0x8024U, /*!< ReceivedTier37PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER38_PRICE_LABEL_ID           = 0x8025U, /*!< ReceivedTier38PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER39_PRICE_LABEL_ID           = 0x8026U, /*!< ReceivedTier39PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER40_PRICE_LABEL_ID           = 0x8027U, /*!< ReceivedTier40PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER41_PRICE_LABEL_ID           = 0x8028U, /*!< ReceivedTier41PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER42_PRICE_LABEL_ID           = 0x8029U, /*!< ReceivedTier42PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER43_PRICE_LABEL_ID           = 0x802AU, /*!< ReceivedTier43PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER44_PRICE_LABEL_ID           = 0x802BU, /*!< ReceivedTier44PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER45_PRICE_LABEL_ID           = 0x802CU, /*!< ReceivedTier45PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER46_PRICE_LABEL_ID           = 0x802DU, /*!< ReceivedTier46PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER47_PRICE_LABEL_ID           = 0x802EU, /*!< ReceivedTier47PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER48_PRICE_LABEL_ID           = 0x802FU, /*!< ReceivedTier48PriceLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK1_THRESHOLD_ID             = 0x8100U, /*!< ReceivedBlock1Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK2_THRESHOLD_ID             = 0x8101U, /*!< ReceivedBlock2Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK3_THRESHOLD_ID             = 0x8102U, /*!< ReceivedBlock3Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK4_THRESHOLD_ID             = 0x8103U, /*!< ReceivedBlock4Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK5_THRESHOLD_ID             = 0x8104U, /*!< ReceivedBlock5Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK6_THRESHOLD_ID             = 0x8105U, /*!< ReceivedBlock6Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK7_THRESHOLD_ID             = 0x8106U, /*!< ReceivedBlock7Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK8_THRESHOLD_ID             = 0x8107U, /*!< ReceivedBlock8Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK9_THRESHOLD_ID             = 0x8108U, /*!< ReceivedBlock9Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK10_THRESHOLD_ID            = 0x8109U, /*!< ReceivedBlock10Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK11_THRESHOLD_ID            = 0x810AU, /*!< ReceivedBlock11Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK12_THRESHOLD_ID            = 0x810BU, /*!< ReceivedBlock12Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK13_THRESHOLD_ID            = 0x810CU, /*!< ReceivedBlock13Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK14_THRESHOLD_ID            = 0x810DU, /*!< ReceivedBlock14Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK15_THRESHOLD_ID            = 0x810EU, /*!< ReceivedBlock15Threshold attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_START_OF_BLOCK_PERIOD_ID        = 0x8200U, /*!< ReceivedStartOfBlockPeriod attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_BLOCK_PERIOD_DURATION_ID        = 0x8201U, /*!< ReceivedBlockPeriodDuration attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_THRESHOLD_MULTIPLIER_ID         = 0x8202U, /*!< ReceivedThresholdMultiplier attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_THRESHOLD_DIVISOR_ID            = 0x8203U, /*!< ReceivedThresholdDivisor attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK1_PRICE_ID               = 0x8400U, /*!< RxNoTierBlock1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK2_PRICE_ID               = 0x8401U, /*!< RxNoTierBlock2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK3_PRICE_ID               = 0x8402U, /*!< RxNoTierBlock3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK4_PRICE_ID               = 0x8403U, /*!< RxNoTierBlock4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK5_PRICE_ID               = 0x8404U, /*!< RxNoTierBlock5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK6_PRICE_ID               = 0x8405U, /*!< RxNoTierBlock6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK7_PRICE_ID               = 0x8406U, /*!< RxNoTierBlock7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK8_PRICE_ID               = 0x8407U, /*!< RxNoTierBlock8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK9_PRICE_ID               = 0x8408U, /*!< RxNoTierBlock9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK10_PRICE_ID              = 0x8409U, /*!< RxNoTierBlock10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK11_PRICE_ID              = 0x840AU, /*!< RxNoTierBlock11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK12_PRICE_ID              = 0x840BU, /*!< RxNoTierBlock12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK13_PRICE_ID              = 0x840CU, /*!< RxNoTierBlock13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK14_PRICE_ID              = 0x840DU, /*!< RxNoTierBlock14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK15_PRICE_ID              = 0x840EU, /*!< RxNoTierBlock15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_NO_TIER_BLOCK16_PRICE_ID              = 0x840FU, /*!< RxNoTierBlock16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK1_PRICE_ID                 = 0x8410U, /*!< RxTier1Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK2_PRICE_ID                 = 0x8411U, /*!< RxTier1Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK3_PRICE_ID                 = 0x8412U, /*!< RxTier1Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK4_PRICE_ID                 = 0x8413U, /*!< RxTier1Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK5_PRICE_ID                 = 0x8414U, /*!< RxTier1Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK6_PRICE_ID                 = 0x8415U, /*!< RxTier1Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK7_PRICE_ID                 = 0x8416U, /*!< RxTier1Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK8_PRICE_ID                 = 0x8417U, /*!< RxTier1Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK9_PRICE_ID                 = 0x8418U, /*!< RxTier1Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK10_PRICE_ID                = 0x8419U, /*!< RxTier1Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK11_PRICE_ID                = 0x841AU, /*!< RxTier1Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK12_PRICE_ID                = 0x841BU, /*!< RxTier1Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK13_PRICE_ID                = 0x841CU, /*!< RxTier1Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK14_PRICE_ID                = 0x841DU, /*!< RxTier1Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK15_PRICE_ID                = 0x841EU, /*!< RxTier1Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER1_BLOCK16_PRICE_ID                = 0x841FU, /*!< RxTier1Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK1_PRICE_ID                 = 0x8420U, /*!< RxTier2Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK2_PRICE_ID                 = 0x8421U, /*!< RxTier2Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK3_PRICE_ID                 = 0x8422U, /*!< RxTier2Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK4_PRICE_ID                 = 0x8423U, /*!< RxTier2Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK5_PRICE_ID                 = 0x8424U, /*!< RxTier2Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK6_PRICE_ID                 = 0x8425U, /*!< RxTier2Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK7_PRICE_ID                 = 0x8426U, /*!< RxTier2Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK8_PRICE_ID                 = 0x8427U, /*!< RxTier2Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK9_PRICE_ID                 = 0x8428U, /*!< RxTier2Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK10_PRICE_ID                = 0x8429U, /*!< RxTier2Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK11_PRICE_ID                = 0x842AU, /*!< RxTier2Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK12_PRICE_ID                = 0x842BU, /*!< RxTier2Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK13_PRICE_ID                = 0x842CU, /*!< RxTier2Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK14_PRICE_ID                = 0x842DU, /*!< RxTier2Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK15_PRICE_ID                = 0x842EU, /*!< RxTier2Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER2_BLOCK16_PRICE_ID                = 0x842FU, /*!< RxTier2Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK1_PRICE_ID                 = 0x8430U, /*!< RxTier3Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK2_PRICE_ID                 = 0x8431U, /*!< RxTier3Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK3_PRICE_ID                 = 0x8432U, /*!< RxTier3Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK4_PRICE_ID                 = 0x8433U, /*!< RxTier3Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK5_PRICE_ID                 = 0x8434U, /*!< RxTier3Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK6_PRICE_ID                 = 0x8435U, /*!< RxTier3Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK7_PRICE_ID                 = 0x8436U, /*!< RxTier3Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK8_PRICE_ID                 = 0x8437U, /*!< RxTier3Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK9_PRICE_ID                 = 0x8438U, /*!< RxTier3Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK10_PRICE_ID                = 0x8439U, /*!< RxTier3Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK11_PRICE_ID                = 0x843AU, /*!< RxTier3Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK12_PRICE_ID                = 0x843BU, /*!< RxTier3Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK13_PRICE_ID                = 0x843CU, /*!< RxTier3Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK14_PRICE_ID                = 0x843DU, /*!< RxTier3Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK15_PRICE_ID                = 0x843EU, /*!< RxTier3Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER3_BLOCK16_PRICE_ID                = 0x843FU, /*!< RxTier3Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK1_PRICE_ID                 = 0x8440U, /*!< RxTier4Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK2_PRICE_ID                 = 0x8441U, /*!< RxTier4Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK3_PRICE_ID                 = 0x8442U, /*!< RxTier4Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK4_PRICE_ID                 = 0x8443U, /*!< RxTier4Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK5_PRICE_ID                 = 0x8444U, /*!< RxTier4Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK6_PRICE_ID                 = 0x8445U, /*!< RxTier4Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK7_PRICE_ID                 = 0x8446U, /*!< RxTier4Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK8_PRICE_ID                 = 0x8447U, /*!< RxTier4Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK9_PRICE_ID                 = 0x8448U, /*!< RxTier4Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK10_PRICE_ID                = 0x8449U, /*!< RxTier4Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK11_PRICE_ID                = 0x844AU, /*!< RxTier4Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK12_PRICE_ID                = 0x844BU, /*!< RxTier4Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK13_PRICE_ID                = 0x844CU, /*!< RxTier4Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK14_PRICE_ID                = 0x844DU, /*!< RxTier4Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK15_PRICE_ID                = 0x844EU, /*!< RxTier4Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER4_BLOCK16_PRICE_ID                = 0x844FU, /*!< RxTier4Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK1_PRICE_ID                 = 0x8450U, /*!< RxTier5Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK2_PRICE_ID                 = 0x8451U, /*!< RxTier5Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK3_PRICE_ID                 = 0x8452U, /*!< RxTier5Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK4_PRICE_ID                 = 0x8453U, /*!< RxTier5Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK5_PRICE_ID                 = 0x8454U, /*!< RxTier5Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK6_PRICE_ID                 = 0x8455U, /*!< RxTier5Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK7_PRICE_ID                 = 0x8456U, /*!< RxTier5Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK8_PRICE_ID                 = 0x8457U, /*!< RxTier5Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK9_PRICE_ID                 = 0x8458U, /*!< RxTier5Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK10_PRICE_ID                = 0x8459U, /*!< RxTier5Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK11_PRICE_ID                = 0x845AU, /*!< RxTier5Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK12_PRICE_ID                = 0x845BU, /*!< RxTier5Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK13_PRICE_ID                = 0x845CU, /*!< RxTier5Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK14_PRICE_ID                = 0x845DU, /*!< RxTier5Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK15_PRICE_ID                = 0x845EU, /*!< RxTier5Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER5_BLOCK16_PRICE_ID                = 0x845FU, /*!< RxTier5Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK1_PRICE_ID                 = 0x8460U, /*!< RxTier6Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK2_PRICE_ID                 = 0x8461U, /*!< RxTier6Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK3_PRICE_ID                 = 0x8462U, /*!< RxTier6Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK4_PRICE_ID                 = 0x8463U, /*!< RxTier6Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK5_PRICE_ID                 = 0x8464U, /*!< RxTier6Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK6_PRICE_ID                 = 0x8465U, /*!< RxTier6Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK7_PRICE_ID                 = 0x8466U, /*!< RxTier6Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK8_PRICE_ID                 = 0x8467U, /*!< RxTier6Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK9_PRICE_ID                 = 0x8468U, /*!< RxTier6Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK10_PRICE_ID                = 0x8469U, /*!< RxTier6Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK11_PRICE_ID                = 0x846AU, /*!< RxTier6Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK12_PRICE_ID                = 0x846BU, /*!< RxTier6Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK13_PRICE_ID                = 0x846CU, /*!< RxTier6Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK14_PRICE_ID                = 0x846DU, /*!< RxTier6Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK15_PRICE_ID                = 0x846EU, /*!< RxTier6Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER6_BLOCK16_PRICE_ID                = 0x846FU, /*!< RxTier6Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK1_PRICE_ID                 = 0x8470U, /*!< RxTier7Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK2_PRICE_ID                 = 0x8471U, /*!< RxTier7Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK3_PRICE_ID                 = 0x8472U, /*!< RxTier7Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK4_PRICE_ID                 = 0x8473U, /*!< RxTier7Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK5_PRICE_ID                 = 0x8474U, /*!< RxTier7Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK6_PRICE_ID                 = 0x8475U, /*!< RxTier7Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK7_PRICE_ID                 = 0x8476U, /*!< RxTier7Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK8_PRICE_ID                 = 0x8477U, /*!< RxTier7Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK9_PRICE_ID                 = 0x8478U, /*!< RxTier7Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK10_PRICE_ID                = 0x8479U, /*!< RxTier7Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK11_PRICE_ID                = 0x847AU, /*!< RxTier7Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK12_PRICE_ID                = 0x847BU, /*!< RxTier7Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK13_PRICE_ID                = 0x847CU, /*!< RxTier7Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK14_PRICE_ID                = 0x847DU, /*!< RxTier7Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK15_PRICE_ID                = 0x847EU, /*!< RxTier7Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER7_BLOCK16_PRICE_ID                = 0x847FU, /*!< RxTier7Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK1_PRICE_ID                 = 0x8480U, /*!< RxTier8Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK2_PRICE_ID                 = 0x8481U, /*!< RxTier8Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK3_PRICE_ID                 = 0x8482U, /*!< RxTier8Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK4_PRICE_ID                 = 0x8483U, /*!< RxTier8Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK5_PRICE_ID                 = 0x8484U, /*!< RxTier8Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK6_PRICE_ID                 = 0x8485U, /*!< RxTier8Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK7_PRICE_ID                 = 0x8486U, /*!< RxTier8Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK8_PRICE_ID                 = 0x8487U, /*!< RxTier8Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK9_PRICE_ID                 = 0x8488U, /*!< RxTier8Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK10_PRICE_ID                = 0x8489U, /*!< RxTier8Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK11_PRICE_ID                = 0x848AU, /*!< RxTier8Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK12_PRICE_ID                = 0x848BU, /*!< RxTier8Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK13_PRICE_ID                = 0x848CU, /*!< RxTier8Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK14_PRICE_ID                = 0x848DU, /*!< RxTier8Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK15_PRICE_ID                = 0x848EU, /*!< RxTier8Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER8_BLOCK16_PRICE_ID                = 0x848FU, /*!< RxTier8Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK1_PRICE_ID                 = 0x8490U, /*!< RxTier9Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK2_PRICE_ID                 = 0x8491U, /*!< RxTier9Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK3_PRICE_ID                 = 0x8492U, /*!< RxTier9Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK4_PRICE_ID                 = 0x8493U, /*!< RxTier9Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK5_PRICE_ID                 = 0x8494U, /*!< RxTier9Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK6_PRICE_ID                 = 0x8495U, /*!< RxTier9Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK7_PRICE_ID                 = 0x8496U, /*!< RxTier9Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK8_PRICE_ID                 = 0x8497U, /*!< RxTier9Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK9_PRICE_ID                 = 0x8498U, /*!< RxTier9Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK10_PRICE_ID                = 0x8499U, /*!< RxTier9Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK11_PRICE_ID                = 0x849AU, /*!< RxTier9Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK12_PRICE_ID                = 0x849BU, /*!< RxTier9Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK13_PRICE_ID                = 0x849CU, /*!< RxTier9Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK14_PRICE_ID                = 0x849DU, /*!< RxTier9Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK15_PRICE_ID                = 0x849EU, /*!< RxTier9Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER9_BLOCK16_PRICE_ID                = 0x849FU, /*!< RxTier9Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK1_PRICE_ID                = 0x84A0U, /*!< RxTier10Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK2_PRICE_ID                = 0x84A1U, /*!< RxTier10Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK3_PRICE_ID                = 0x84A2U, /*!< RxTier10Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK4_PRICE_ID                = 0x84A3U, /*!< RxTier10Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK5_PRICE_ID                = 0x84A4U, /*!< RxTier10Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK6_PRICE_ID                = 0x84A5U, /*!< RxTier10Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK7_PRICE_ID                = 0x84A6U, /*!< RxTier10Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK8_PRICE_ID                = 0x84A7U, /*!< RxTier10Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK9_PRICE_ID                = 0x84A8U, /*!< RxTier10Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK10_PRICE_ID               = 0x84A9U, /*!< RxTier10Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK11_PRICE_ID               = 0x84AAU, /*!< RxTier10Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK12_PRICE_ID               = 0x84ABU, /*!< RxTier10Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK13_PRICE_ID               = 0x84ACU, /*!< RxTier10Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK14_PRICE_ID               = 0x84ADU, /*!< RxTier10Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK15_PRICE_ID               = 0x84AEU, /*!< RxTier10Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER10_BLOCK16_PRICE_ID               = 0x84AFU, /*!< RxTier10Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK1_PRICE_ID                = 0x84B0U, /*!< RxTier11Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK2_PRICE_ID                = 0x84B1U, /*!< RxTier11Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK3_PRICE_ID                = 0x84B2U, /*!< RxTier11Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK4_PRICE_ID                = 0x84B3U, /*!< RxTier11Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK5_PRICE_ID                = 0x84B4U, /*!< RxTier11Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK6_PRICE_ID                = 0x84B5U, /*!< RxTier11Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK7_PRICE_ID                = 0x84B6U, /*!< RxTier11Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK8_PRICE_ID                = 0x84B7U, /*!< RxTier11Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK9_PRICE_ID                = 0x84B8U, /*!< RxTier11Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK10_PRICE_ID               = 0x84B9U, /*!< RxTier11Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK11_PRICE_ID               = 0x84BAU, /*!< RxTier11Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK12_PRICE_ID               = 0x84BBU, /*!< RxTier11Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK13_PRICE_ID               = 0x84BCU, /*!< RxTier11Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK14_PRICE_ID               = 0x84BDU, /*!< RxTier11Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK15_PRICE_ID               = 0x84BEU, /*!< RxTier11Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER11_BLOCK16_PRICE_ID               = 0x84BFU, /*!< RxTier11Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK1_PRICE_ID                = 0x84C0U, /*!< RxTier12Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK2_PRICE_ID                = 0x84C1U, /*!< RxTier12Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK3_PRICE_ID                = 0x84C2U, /*!< RxTier12Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK4_PRICE_ID                = 0x84C3U, /*!< RxTier12Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK5_PRICE_ID                = 0x84C4U, /*!< RxTier12Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK6_PRICE_ID                = 0x84C5U, /*!< RxTier12Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK7_PRICE_ID                = 0x84C6U, /*!< RxTier12Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK8_PRICE_ID                = 0x84C7U, /*!< RxTier12Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK9_PRICE_ID                = 0x84C8U, /*!< RxTier12Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK10_PRICE_ID               = 0x84C9U, /*!< RxTier12Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK11_PRICE_ID               = 0x84CAU, /*!< RxTier12Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK12_PRICE_ID               = 0x84CBU, /*!< RxTier12Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK13_PRICE_ID               = 0x84CCU, /*!< RxTier12Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK14_PRICE_ID               = 0x84CDU, /*!< RxTier12Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK15_PRICE_ID               = 0x84CEU, /*!< RxTier12Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER12_BLOCK16_PRICE_ID               = 0x84CFU, /*!< RxTier12Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK1_PRICE_ID                = 0x84D0U, /*!< RxTier13Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK2_PRICE_ID                = 0x84D1U, /*!< RxTier13Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK3_PRICE_ID                = 0x84D2U, /*!< RxTier13Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK4_PRICE_ID                = 0x84D3U, /*!< RxTier13Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK5_PRICE_ID                = 0x84D4U, /*!< RxTier13Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK6_PRICE_ID                = 0x84D5U, /*!< RxTier13Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK7_PRICE_ID                = 0x84D6U, /*!< RxTier13Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK8_PRICE_ID                = 0x84D7U, /*!< RxTier13Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK9_PRICE_ID                = 0x84D8U, /*!< RxTier13Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK10_PRICE_ID               = 0x84D9U, /*!< RxTier13Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK11_PRICE_ID               = 0x84DAU, /*!< RxTier13Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK12_PRICE_ID               = 0x84DBU, /*!< RxTier13Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK13_PRICE_ID               = 0x84DCU, /*!< RxTier13Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK14_PRICE_ID               = 0x84DDU, /*!< RxTier13Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK15_PRICE_ID               = 0x84DEU, /*!< RxTier13Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER13_BLOCK16_PRICE_ID               = 0x84DFU, /*!< RxTier13Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK1_PRICE_ID                = 0x84E0U, /*!< RxTier14Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK2_PRICE_ID                = 0x84E1U, /*!< RxTier14Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK3_PRICE_ID                = 0x84E2U, /*!< RxTier14Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK4_PRICE_ID                = 0x84E3U, /*!< RxTier14Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK5_PRICE_ID                = 0x84E4U, /*!< RxTier14Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK6_PRICE_ID                = 0x84E5U, /*!< RxTier14Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK7_PRICE_ID                = 0x84E6U, /*!< RxTier14Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK8_PRICE_ID                = 0x84E7U, /*!< RxTier14Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK9_PRICE_ID                = 0x84E8U, /*!< RxTier14Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK10_PRICE_ID               = 0x84E9U, /*!< RxTier14Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK11_PRICE_ID               = 0x84EAU, /*!< RxTier14Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK12_PRICE_ID               = 0x84EBU, /*!< RxTier14Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK13_PRICE_ID               = 0x84ECU, /*!< RxTier14Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK14_PRICE_ID               = 0x84EDU, /*!< RxTier14Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK15_PRICE_ID               = 0x84EEU, /*!< RxTier14Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER14_BLOCK16_PRICE_ID               = 0x84EFU, /*!< RxTier14Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK1_PRICE_ID                = 0x84F0U, /*!< RxTier15Block1Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK2_PRICE_ID                = 0x84F1U, /*!< RxTier15Block2Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK3_PRICE_ID                = 0x84F2U, /*!< RxTier15Block3Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK4_PRICE_ID                = 0x84F3U, /*!< RxTier15Block4Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK5_PRICE_ID                = 0x84F4U, /*!< RxTier15Block5Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK6_PRICE_ID                = 0x84F5U, /*!< RxTier15Block6Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK7_PRICE_ID                = 0x84F6U, /*!< RxTier15Block7Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK8_PRICE_ID                = 0x84F7U, /*!< RxTier15Block8Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK9_PRICE_ID                = 0x84F8U, /*!< RxTier15Block9Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK10_PRICE_ID               = 0x84F9U, /*!< RxTier15Block10Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK11_PRICE_ID               = 0x84FAU, /*!< RxTier15Block11Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK12_PRICE_ID               = 0x84FBU, /*!< RxTier15Block12Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK13_PRICE_ID               = 0x84FCU, /*!< RxTier15Block13Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK14_PRICE_ID               = 0x84FDU, /*!< RxTier15Block14Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK15_PRICE_ID               = 0x84FEU, /*!< RxTier15Block15Price attribute. */
    EZB_ZCL_ATTR_PRICE_RX_TIER15_BLOCK16_PRICE_ID               = 0x84FFU, /*!< RxTier15Block16Price attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER16_ID                 = 0x850FU, /*!< ReceivedPriceTier16 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER17_ID                 = 0x8510U, /*!< ReceivedPriceTier17 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER18_ID                 = 0x8511U, /*!< ReceivedPriceTier18 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER19_ID                 = 0x8512U, /*!< ReceivedPriceTier19 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER20_ID                 = 0x8513U, /*!< ReceivedPriceTier20 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER21_ID                 = 0x8514U, /*!< ReceivedPriceTier21 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER22_ID                 = 0x8515U, /*!< ReceivedPriceTier22 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER23_ID                 = 0x8516U, /*!< ReceivedPriceTier23 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER24_ID                 = 0x8517U, /*!< ReceivedPriceTier24 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER25_ID                 = 0x8518U, /*!< ReceivedPriceTier25 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER26_ID                 = 0x8519U, /*!< ReceivedPriceTier26 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER27_ID                 = 0x851AU, /*!< ReceivedPriceTier27 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER28_ID                 = 0x851BU, /*!< ReceivedPriceTier28 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER29_ID                 = 0x851CU, /*!< ReceivedPriceTier29 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER30_ID                 = 0x851DU, /*!< ReceivedPriceTier30 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER31_ID                 = 0x851EU, /*!< ReceivedPriceTier31 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER32_ID                 = 0x851FU, /*!< ReceivedPriceTier32 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER33_ID                 = 0x8520U, /*!< ReceivedPriceTier33 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER34_ID                 = 0x8521U, /*!< ReceivedPriceTier34 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER35_ID                 = 0x8522U, /*!< ReceivedPriceTier35 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER36_ID                 = 0x8523U, /*!< ReceivedPriceTier36 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER37_ID                 = 0x8524U, /*!< ReceivedPriceTier37 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER38_ID                 = 0x8525U, /*!< ReceivedPriceTier38 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER39_ID                 = 0x8526U, /*!< ReceivedPriceTier39 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER40_ID                 = 0x8527U, /*!< ReceivedPriceTier40 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER41_ID                 = 0x8528U, /*!< ReceivedPriceTier41 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER42_ID                 = 0x8529U, /*!< ReceivedPriceTier42 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER43_ID                 = 0x852AU, /*!< ReceivedPriceTier43 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER44_ID                 = 0x852BU, /*!< ReceivedPriceTier44 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER45_ID                 = 0x852CU, /*!< ReceivedPriceTier45 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER46_ID                 = 0x852DU, /*!< ReceivedPriceTier46 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER47_ID                 = 0x852EU, /*!< ReceivedPriceTier47 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_PRICE_TIER48_ID                 = 0x852FU, /*!< ReceivedPriceTier48 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TARIFF_LABEL_ID                 = 0x8610U, /*!< ReceivedTariffLabel attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_NUMBER_OF_PRICE_TIERS_IN_USE_ID = 0x8611U, /*!< ReceivedNumberOfPriceTiersInUse attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_NUMBER_OF_BLOCK_THRESHOLDS_IN_USE_ID =
        0x8612U, /*!< ReceivedNumberOfBlockThresholdsInUse attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TIER_BLOCK_MODE_ID              = 0x8613U, /*!< ReceivedTierBlockMode attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_TARIFF_RESOLUTION_PERIOD_ID     = 0x8615U, /*!< ReceivedTariffResolutionPeriod attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_CO2_ID                          = 0x8625U, /*!< ReceivedCO2 attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_CO2_UNIT_ID                     = 0x8626U, /*!< ReceivedCO2Unit attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_CO2_TRAILING_DIGIT_ID           = 0x8627U, /*!< ReceivedCO2TrailingDigit attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_CURRENT_BILLING_PERIOD_START_ID = 0x8700U, /*!< ReceivedCurrentBillingPeriodStart attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_CURRENT_BILLING_PERIOD_DURATION_ID =
        0x8701U, /*!< ReceivedCurrentBillingPeriodDuration attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_LAST_BILLING_PERIOD_START_ID    = 0x8702U, /*!< ReceivedLastBillingPeriodStart attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_LAST_BILLING_PERIOD_DURATION_ID = 0x8703U, /*!< ReceivedLastBillingPeriodDuration attribute. */
    EZB_ZCL_ATTR_PRICE_RECEIVED_LAST_BILLING_PERIOD_CONSOLIDATED_BILL_ID =
        0x8704U, /*!< ReceivedLastBillingPeriodConsolidatedBill attribute. */
} ezb_zcl_price_server_attr_t;

/**
 * @brief Enumeration for ZCL BlockPeriodDurationType attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_BLOCK_PERIOD_DURATION_TYPE_MINUTES = 0x00U, /*!< Minutes */
    EZB_ZCL_PRICE_BLOCK_PERIOD_DURATION_TYPE_DAYS    = 0x01U, /*!< Days */
    EZB_ZCL_PRICE_BLOCK_PERIOD_DURATION_TYPE_WEEKS   = 0x02U, /*!< Weeks */
    EZB_ZCL_PRICE_BLOCK_PERIOD_DURATION_TYPE_MONTHS  = 0x03U, /*!< Months */
} ezb_zcl_price_server_block_period_duration_type_t;

/**
 * @brief Enumeration for ZCL CalorificValueUnit attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_CALORIFIC_VALUE_UNIT_MJ_M3 = 0x00U, /*!< MjM3 */
    EZB_ZCL_PRICE_CALORIFIC_VALUE_UNIT_MJ_KG = 0x01U, /*!< MjKg */
} ezb_zcl_price_server_calorific_value_unit_t;

/**
 * @brief Enumeration for ZCL TierBlockMode attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_TIER_BLOCK_MODE_SINGLE_SET_THRESHOLDS         = 0x00U, /*!< SingleSetThresholds */
    EZB_ZCL_PRICE_TIER_BLOCK_MODE_COMMON_THRESHOLDS_ACROSS_TOU  = 0x01U, /*!< CommonThresholdsAcrossTOU */
    EZB_ZCL_PRICE_TIER_BLOCK_MODE_INDIVIDUAL_THRESHOLDS_PER_TOU = 0x02U, /*!< IndividualThresholdsPerTOU */
    EZB_ZCL_PRICE_TIER_BLOCK_MODE_NOT_USED                      = 0xffU, /*!< NotUsed */
} ezb_zcl_price_server_tier_block_mode_t;

/**
 * @brief Enumeration for ZCL TariffResolutionPeriod attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_TARIFF_RESOLUTION_PERIOD_NOT_DEFINED  = 0x00U, /*!< NotDefined */
    EZB_ZCL_PRICE_TARIFF_RESOLUTION_PERIOD_BLOCK_PERIOD = 0x01U, /*!< BlockPeriod */
    EZB_ZCL_PRICE_TARIFF_RESOLUTION_PERIOD_ONE_DAY      = 0x02U, /*!< OneDay */
} ezb_zcl_price_server_tariff_resolution_period_t;

/**
 * @brief Enumeration for ZCL CO2Unit attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_CO2_UNIT_RESERVED_FOR_FUTURE_USE     = 0x00U, /*!< ReservedForFutureUse */
    EZB_ZCL_PRICE_CO2_UNIT_KG_PERK_WH                  = 0x01U, /*!< kgPerkWh */
    EZB_ZCL_PRICE_CO2_UNIT_KG_PER_GALLON_OF_GASOLINE   = 0x02U, /*!< kgPerGallonOfGasoline */
    EZB_ZCL_PRICE_CO2_UNIT_KG_PER_THERM_OF_NATURAL_GAS = 0x03U, /*!< kgPerThermOfNaturalGas */
} ezb_zcl_price_server_co2_unit_t;

/**
 * @brief Enumeration for ZCL CreditPaymentStatus attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_CREDIT_PAYMENT_STATUS_PENDING            = 0x00U, /*!< Pending */
    EZB_ZCL_PRICE_CREDIT_PAYMENT_STATUS_RECEIVED           = 0x01U, /*!< Received */
    EZB_ZCL_PRICE_CREDIT_PAYMENT_STATUS_OVERDUE            = 0x02U, /*!< Overdue */
    EZB_ZCL_PRICE_CREDIT_PAYMENT_STATUS_2_PAYMENTS_OVERDUE = 0x03U, /*!< 2PaymentsOverdue */
    EZB_ZCL_PRICE_CREDIT_PAYMENT_STATUS_3_PAYMENTS_OVERDUE = 0x04U, /*!< 3PaymentsOverdue */
} ezb_zcl_price_server_credit_payment_status_t;

/**
 * @brief Enumeration for ZCL PaymentDiscountPeriod attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_PAYMENT_DISCOUNT_PERIOD_CURRENT_BILLING_PERIOD    = 0x00U, /*!< CurrentBillingPeriod */
    EZB_ZCL_PRICE_PAYMENT_DISCOUNT_PERIOD_CURRENT_CONSOLIDATED_BILL = 0x01U, /*!< CurrentConsolidatedBill */
    EZB_ZCL_PRICE_PAYMENT_DISCOUNT_PERIOD_ONE_MONTH                 = 0x02U, /*!< OneMonth */
    EZB_ZCL_PRICE_PAYMENT_DISCOUNT_PERIOD_ONE_QUARTER               = 0x03U, /*!< OneQuarter */
    EZB_ZCL_PRICE_PAYMENT_DISCOUNT_PERIOD_ONE_YEAR                  = 0x04U, /*!< OneYear */
} ezb_zcl_price_server_payment_discount_period_t;

/**
 * @brief Enumeration for ZCL ReceivedTariffResolutionPeriod attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_RECEIVED_TARIFF_RESOLUTION_PERIOD_NOT_DEFINED  = 0x00U, /*!< NotDefined */
    EZB_ZCL_PRICE_RECEIVED_TARIFF_RESOLUTION_PERIOD_BLOCK_PERIOD = 0x01U, /*!< BlockPeriod */
    EZB_ZCL_PRICE_RECEIVED_TARIFF_RESOLUTION_PERIOD_ONE_DAY      = 0x02U, /*!< OneDay */
} ezb_zcl_price_server_received_tariff_resolution_period_t;

/**
 * @brief Enumeration for ZCL ReceivedCO2Unit attribute of Price.
 */
typedef enum {
    EZB_ZCL_PRICE_RECEIVED_CO2_UNIT_RESERVED_FOR_FUTURE_USE     = 0x00U, /*!< ReservedForFutureUse */
    EZB_ZCL_PRICE_RECEIVED_CO2_UNIT_KG_PERK_WH                  = 0x01U, /*!< kgPerkWh */
    EZB_ZCL_PRICE_RECEIVED_CO2_UNIT_KG_PER_GALLON_OF_GASOLINE   = 0x02U, /*!< kgPerGallonOfGasoline */
    EZB_ZCL_PRICE_RECEIVED_CO2_UNIT_KG_PER_THERM_OF_NATURAL_GAS = 0x03U, /*!< kgPerThermOfNaturalGas */
} ezb_zcl_price_server_received_co2_unit_t;

/** @brief Default value of Tier1PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER1_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 1")

/** @brief Default value of Tier2PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER2_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 2")

/** @brief Default value of Tier3PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER3_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 3")

/** @brief Default value of Tier4PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER4_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 4")

/** @brief Default value of Tier5PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER5_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 5")

/** @brief Default value of Tier6PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER6_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 6")

/** @brief Default value of Tier7PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER7_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 7")

/** @brief Default value of Tier8PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER8_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 8")

/** @brief Default value of Tier9PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER9_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                           \
     "Tier 9")

/** @brief Default value of Tier10PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER10_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 10")

/** @brief Default value of Tier11PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER11_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 11")

/** @brief Default value of Tier12PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER12_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 12")

/** @brief Default value of Tier13PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER13_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 13")

/** @brief Default value of Tier14PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER14_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 14")

/** @brief Default value of Tier15PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER15_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 15")

/** @brief Default value of Tier16PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER16_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 16")

/** @brief Default value of Tier17PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER17_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 17")

/** @brief Default value of Tier18PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER18_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 18")

/** @brief Default value of Tier19PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER19_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 19")

/** @brief Default value of Tier20PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER20_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 20")

/** @brief Default value of Tier21PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER21_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 21")

/** @brief Default value of Tier22PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER22_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 22")

/** @brief Default value of Tier23PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER23_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 23")

/** @brief Default value of Tier24PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER24_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 24")

/** @brief Default value of Tier25PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER25_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 25")

/** @brief Default value of Tier26PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER26_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 26")

/** @brief Default value of Tier27PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER27_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 27")

/** @brief Default value of Tier28PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER28_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 28")

/** @brief Default value of Tier29PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER29_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 29")

/** @brief Default value of Tier30PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER30_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 30")

/** @brief Default value of Tier31PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER31_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 31")

/** @brief Default value of Tier32PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER32_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 32")

/** @brief Default value of Tier33PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER33_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 33")

/** @brief Default value of Tier34PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER34_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 34")

/** @brief Default value of Tier35PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER35_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 35")

/** @brief Default value of Tier36PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER36_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 36")

/** @brief Default value of Tier37PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER37_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 37")

/** @brief Default value of Tier38PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER38_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 38")

/** @brief Default value of Tier39PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER39_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 39")

/** @brief Default value of Tier40PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER40_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 40")

/** @brief Default value of Tier41PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER41_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 41")

/** @brief Default value of Tier42PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER42_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 42")

/** @brief Default value of Tier43PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER43_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 43")

/** @brief Default value of Tier44PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER44_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 44")

/** @brief Default value of Tier45PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER45_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 45")

/** @brief Default value of Tier46PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER46_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 46")

/** @brief Default value of Tier47PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER47_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 47")

/** @brief Default value of Tier48PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_TIER48_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                            \
     "Tier 48")

/** @brief Default value of BlockPeriodDurationType in Price cluster */
#define EZB_ZCL_PRICE_BLOCK_PERIOD_DURATION_TYPE_DEFAULT_VALUE (0x00)

/** @brief Default value of ConversionFactor in Price cluster */
#define EZB_ZCL_PRICE_CONVERSION_FACTOR_DEFAULT_VALUE (0x10000000)

/** @brief Default value of ConversionFactorTrailingDigit in Price cluster */
#define EZB_ZCL_PRICE_CONVERSION_FACTOR_TRAILING_DIGIT_DEFAULT_VALUE (0x70)

/** @brief Default value of CalorificValue in Price cluster */
#define EZB_ZCL_PRICE_CALORIFIC_VALUE_DEFAULT_VALUE (0x2625A00)

/** @brief Default value of CalorificValueUnit in Price cluster */
#define EZB_ZCL_PRICE_CALORIFIC_VALUE_UNIT_DEFAULT_VALUE (0x01)

/** @brief Default value of CalorificValueTrailingDigit in Price cluster */
#define EZB_ZCL_PRICE_CALORIFIC_VALUE_TRAILING_DIGIT_DEFAULT_VALUE (0x60)

/** @brief Default value of TariffLabel in Price cluster */
#define EZB_ZCL_PRICE_TARIFF_LABEL_DEFAULT_VALUE \
    ("\x04"                                      \
     "0x00")

/** @brief Default value of NumberOfPriceTiersInUse in Price cluster */
#define EZB_ZCL_PRICE_NUMBER_OF_PRICE_TIERS_IN_USE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of NumberOfPriceTiersInUse in Price cluster */
#define EZB_ZCL_PRICE_NUMBER_OF_PRICE_TIERS_IN_USE_MIN_VALUE (0x00)

/** @brief Maximum value of NumberOfPriceTiersInUse in Price cluster */
#define EZB_ZCL_PRICE_NUMBER_OF_PRICE_TIERS_IN_USE_MAX_VALUE (0x0f)
/** @brief Default value of NumberOfBlockThresholdsInUse in Price cluster */
#define EZB_ZCL_PRICE_NUMBER_OF_BLOCK_THRESHOLDS_IN_USE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of NumberOfBlockThresholdsInUse in Price cluster */
#define EZB_ZCL_PRICE_NUMBER_OF_BLOCK_THRESHOLDS_IN_USE_MIN_VALUE (0x00)

/** @brief Maximum value of NumberOfBlockThresholdsInUse in Price cluster */
#define EZB_ZCL_PRICE_NUMBER_OF_BLOCK_THRESHOLDS_IN_USE_MAX_VALUE (0x0f)
/** @brief Default value of TierBlockMode in Price cluster */
#define EZB_ZCL_PRICE_TIER_BLOCK_MODE_DEFAULT_VALUE (0xff)

/** @brief Default value of UnitOfMeasure in Price cluster */
#define EZB_ZCL_PRICE_UNIT_OF_MEASURE_DEFAULT_VALUE (0x00)

/** @brief Default value of PriceTrailingDigit in Price cluster */
#define EZB_ZCL_PRICE_PRICE_TRAILING_DIGIT_DEFAULT_VALUE (0x00)

/** @brief Default value of TariffResolutionPeriod in Price cluster */
#define EZB_ZCL_PRICE_TARIFF_RESOLUTION_PERIOD_DEFAULT_VALUE (0x00)

/** @brief Default value of Co2 in Price cluster */
#define EZB_ZCL_PRICE_CO2_DEFAULT_VALUE (0x000000B9)

/** @brief Default value of CO2Unit in Price cluster */
#define EZB_ZCL_PRICE_CO2_UNIT_DEFAULT_VALUE (0x01)

/** @brief Default value of CO2TrailingDigit in Price cluster */
#define EZB_ZCL_PRICE_CO2_TRAILING_DIGIT_DEFAULT_VALUE (0x00)

/** @brief Default value of CreditPaymentOverDueAmount in Price cluster */
#define EZB_ZCL_PRICE_CREDIT_PAYMENT_OVER_DUE_AMOUNT_DEFAULT_VALUE (0x00)

/** @brief Default value of ReceivedTier1PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER1_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 1")

/** @brief Default value of ReceivedTier2PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER2_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 2")

/** @brief Default value of ReceivedTier3PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER3_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 3")

/** @brief Default value of ReceivedTier4PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER4_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 4")

/** @brief Default value of ReceivedTier5PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER5_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 5")

/** @brief Default value of ReceivedTier6PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER6_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 6")

/** @brief Default value of ReceivedTier7PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER7_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 7")

/** @brief Default value of ReceivedTier8PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER8_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 8")

/** @brief Default value of ReceivedTier9PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER9_PRICE_LABEL_DEFAULT_VALUE \
    ("\x06"                                                    \
     "Tier 9")

/** @brief Default value of ReceivedTier10PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER10_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 10")

/** @brief Default value of ReceivedTier11PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER11_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 11")

/** @brief Default value of ReceivedTier12PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER12_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 12")

/** @brief Default value of ReceivedTier13PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER13_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 13")

/** @brief Default value of ReceivedTier14PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER14_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 14")

/** @brief Default value of ReceivedTier15PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER15_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 15")

/** @brief Default value of ReceivedTier16PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER16_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 16")

/** @brief Default value of ReceivedTier17PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER17_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 17")

/** @brief Default value of ReceivedTier18PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER18_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 18")

/** @brief Default value of ReceivedTier19PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER19_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 19")

/** @brief Default value of ReceivedTier20PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER20_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 20")

/** @brief Default value of ReceivedTier21PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER21_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 21")

/** @brief Default value of ReceivedTier22PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER22_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 22")

/** @brief Default value of ReceivedTier23PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER23_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 23")

/** @brief Default value of ReceivedTier24PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER24_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 24")

/** @brief Default value of ReceivedTier25PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER25_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 25")

/** @brief Default value of ReceivedTier26PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER26_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 26")

/** @brief Default value of ReceivedTier27PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER27_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 27")

/** @brief Default value of ReceivedTier28PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER28_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 28")

/** @brief Default value of ReceivedTier29PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER29_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 29")

/** @brief Default value of ReceivedTier30PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER30_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 30")

/** @brief Default value of ReceivedTier31PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER31_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 31")

/** @brief Default value of ReceivedTier32PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER32_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 32")

/** @brief Default value of ReceivedTier33PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER33_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 33")

/** @brief Default value of ReceivedTier34PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER34_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 34")

/** @brief Default value of ReceivedTier35PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER35_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 35")

/** @brief Default value of ReceivedTier36PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER36_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 36")

/** @brief Default value of ReceivedTier37PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER37_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 37")

/** @brief Default value of ReceivedTier38PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER38_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 38")

/** @brief Default value of ReceivedTier39PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER39_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 39")

/** @brief Default value of ReceivedTier40PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER40_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 40")

/** @brief Default value of ReceivedTier41PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER41_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 41")

/** @brief Default value of ReceivedTier42PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER42_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 42")

/** @brief Default value of ReceivedTier43PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER43_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 43")

/** @brief Default value of ReceivedTier44PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER44_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 44")

/** @brief Default value of ReceivedTier45PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER45_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 45")

/** @brief Default value of ReceivedTier46PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER46_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 46")

/** @brief Default value of ReceivedTier47PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER47_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 47")

/** @brief Default value of ReceivedTier48PriceLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER48_PRICE_LABEL_DEFAULT_VALUE \
    ("\x07"                                                     \
     "Tier 48")

/** @brief Default value of ReceivedTariffLabel in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TARIFF_LABEL_DEFAULT_VALUE \
    ("\x04"                                               \
     "0x00")

/** @brief Default value of ReceivedNumberOfPriceTiersInUse in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_NUMBER_OF_PRICE_TIERS_IN_USE_DEFAULT_VALUE (0x00)

/** @brief Default value of ReceivedNumberOfBlockThresholdsInUse in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_NUMBER_OF_BLOCK_THRESHOLDS_IN_USE_DEFAULT_VALUE (0x00)

/** @brief Default value of ReceivedTierBlockMode in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TIER_BLOCK_MODE_DEFAULT_VALUE (0xff)

/** @brief Default value of ReceivedTariffResolutionPeriod in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_TARIFF_RESOLUTION_PERIOD_DEFAULT_VALUE (0x00)

/** @brief Default value of ReceivedCO2 in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_CO2_DEFAULT_VALUE (0x000000B9)

/** @brief Default value of ReceivedCO2Unit in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_CO2_UNIT_DEFAULT_VALUE (0x01)

/** @brief Default value of ReceivedCO2TrailingDigit in Price cluster */
#define EZB_ZCL_PRICE_RECEIVED_CO2_TRAILING_DIGIT_DEFAULT_VALUE (0x00)

/**
 * @brief Received Command identifiers for the Price cluster.
 */
typedef enum {
    EZB_ZCL_CMD_PRICE_GET_CURRENT_PRICE_ID       = 0x00U, /*!< GetCurrentPrice command. */
    EZB_ZCL_CMD_PRICE_GET_SCHEDULED_PRICES_ID    = 0x01U, /*!< GetScheduledPrices command. */
    EZB_ZCL_CMD_PRICE_PRICE_ACKNOWLEDGEMENT_ID   = 0x02U, /*!< PriceAcknowledgement command. */
    EZB_ZCL_CMD_PRICE_GET_BLOCK_PERIOD_ID        = 0x03U, /*!< GetBlockPeriod command. */
    EZB_ZCL_CMD_PRICE_GET_CONVERSION_FACTOR_ID   = 0x04U, /*!< GetConversionFactor command. */
    EZB_ZCL_CMD_PRICE_GET_CALORIFIC_VALUE_ID     = 0x05U, /*!< GetCalorificValue command. */
    EZB_ZCL_CMD_PRICE_GET_TARIFF_INFORMATION_ID  = 0x06U, /*!< GetTariffInformation command. */
    EZB_ZCL_CMD_PRICE_GET_PRICE_MATRIX_ID        = 0x07U, /*!< GetPriceMatrix command. */
    EZB_ZCL_CMD_PRICE_GET_BLOCK_THRESHOLDS_ID    = 0x08U, /*!< GetBlockThresholds command. */
    EZB_ZCL_CMD_PRICE_GET_CO2_VALUE_ID           = 0x09U, /*!< GetCO2Value command. */
    EZB_ZCL_CMD_PRICE_GET_TIER_LABELS_ID         = 0x0AU, /*!< GetTierLabels command. */
    EZB_ZCL_CMD_PRICE_GET_BILLING_PERIOD_ID      = 0x0BU, /*!< GetBillingPeriod command. */
    EZB_ZCL_CMD_PRICE_GET_CONSOLIDATED_BILL_ID   = 0x0CU, /*!< GetConsolidatedBill command. */
    EZB_ZCL_CMD_PRICE_CPP_EVENT_RESPONSE_ID      = 0x0DU, /*!< CPPEventResponse command. */
    EZB_ZCL_CMD_PRICE_GET_CREDIT_PAYMENT_ID      = 0x0EU, /*!< GetCreditPayment command. */
    EZB_ZCL_CMD_PRICE_GET_CURRENCY_CONVERSION_ID = 0x0FU, /*!< GetCurrencyConversion command. */
    EZB_ZCL_CMD_PRICE_GET_TARIFF_CANCELLATION_ID = 0x10U, /*!< GetTariffCancellation command. */
} ezb_zcl_price_server_cmd_id_t;

/**
 * @brief Attribute identifiers for the price client cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_PRICE_PRICE_INCREASE_RANDOMIZE_MINUTES_ID = 0x0000U, /*!< PriceIncreaseRandomizeMinutes attribute. */
    EZB_ZCL_ATTR_PRICE_PRICE_DECREASE_RANDOMIZE_MINUTES_ID = 0x0001U, /*!< PriceDecreaseRandomizeMinutes attribute. */
    EZB_ZCL_ATTR_PRICE_CLIENT_COMMODITY_TYPE_ID            = 0x0002U, /*!< ClientCommodityType attribute. */
} ezb_zcl_price_client_attr_t;

/** @brief Default value of PriceIncreaseRandomizeMinutes in Price cluster */
#define EZB_ZCL_PRICE_PRICE_INCREASE_RANDOMIZE_MINUTES_DEFAULT_VALUE (0x05)

/** @brief Default value of PriceDecreaseRandomizeMinutes in Price cluster */
#define EZB_ZCL_PRICE_PRICE_DECREASE_RANDOMIZE_MINUTES_DEFAULT_VALUE (0x0F)

/**
 * @brief Received Command identifiers for the Price cluster.
 */
typedef enum {
    EZB_ZCL_CMD_PRICE_PUBLISH_PRICE_ID               = 0x00U, /*!< PublishPrice command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_BLOCK_PERIOD_ID        = 0x01U, /*!< PublishBlockPeriod command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_CONVERSION_FACTOR_ID   = 0x02U, /*!< PublishConversionFactor command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_CALORIFIC_VALUE_ID     = 0x03U, /*!< PublishCalorificValue command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_TARIFF_INFORMATION_ID  = 0x04U, /*!< PublishTariffInformation command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_PRICE_MATRIX_ID        = 0x05U, /*!< PublishPriceMatrix command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_BLOCK_THRESHOLDS_ID    = 0x06U, /*!< PublishBlockThresholds command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_CO2_VALUE_ID           = 0x07U, /*!< PublishCO2Value command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_TIER_LABELS_ID         = 0x08U, /*!< PublishTierLabels command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_BILLING_PERIOD_ID      = 0x09U, /*!< PublishBillingPeriod command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_CONSOLIDATED_BILL_ID   = 0x0AU, /*!< PublishConsolidatedBill command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_CPP_EVENT_ID           = 0x0BU, /*!< PublishCPPEvent command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_CREDIT_PAYMENT_ID      = 0x0CU, /*!< PublishCreditPayment command. */
    EZB_ZCL_CMD_PRICE_PUBLISH_CURRENCY_CONVERSION_ID = 0x0DU, /*!< PublishCurrencyConversion command. */
    EZB_ZCL_CMD_PRICE_CANCEL_TARIFF_ID               = 0x0EU, /*!< CancelTariff command. */
} ezb_zcl_price_client_cmd_id_t;

/**
 * @brief Cluster configuration for the Price cluster.
 */
typedef struct ezb_zcl_price_cluster_config_s {
    int _unused; /*!< Unused. */
} ezb_zcl_price_cluster_config_t;

/**
 * @brief Add an attribute to an price cluster descriptor.
 *
 * @param cluster_desc Pointer to the price cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_price_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an price cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the price cluster configuration structure, refer to ezb_zcl_price_cluster_server_config_t or
 * ezb_zcl_price_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_price_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Price cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_price_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Price cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_price_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_PRICE_CLIENT_ROLE_INIT ezb_zcl_price_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_PRICE_SERVER_ROLE_INIT ezb_zcl_price_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
