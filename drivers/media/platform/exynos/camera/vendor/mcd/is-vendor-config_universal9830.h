/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Universal Exynos 990 (universal9830) camera build configuration.
 *
 * This is the neutral base for the single unified Image. It is not derived
 * from any one product: it enables the union of the code paths that the
 * supported products require, while the values that really differ between
 * products are selected at runtime by is_vendor_cfg().
 *
 * Sources of the per-product values:
 *   x1s/x1slte  -> hst_v01
 *   y2s/y2slte  -> hst_v02
 *   z3s         -> hst_v03
 *   c1s/c1slte  -> cnt_v01
 *   c2s/c2slte  -> cnt_v02
 *   r8s         -> rst_v08
 */

#ifndef IS_VENDOR_CONFIG_UNIVERSAL9830_H
#define IS_VENDOR_CONFIG_UNIVERSAL9830_H

#include "is-vendor-config-runtime.h"

#define VENDER_PATH

/*
 * Every product configuration disables the camera dynamic-memory
 * allocator. Keep the unified build identical; the per-product headers
 * all contain this undef and the resource manager behaves differently
 * when it is left enabled.
 */
#undef ENABLE_DYNAMIC_MEM

/* ------------------------------------------------------------------------- */
/* Hardware topology shared by every supported product                       */
/* ------------------------------------------------------------------------- */

#define CAMERA_REAR_DUAL_CAL
#define CAMERA_REAR2
#define CAMERA_REAR2_AF			/* related to OIS */
#define CAMERA_REAR2_TILT
#define CAMERA_REAR2_MODULEID
#define CAMERA_REAR3
#define CAMERA_REAR3_AFCAL
#define CAMERA_REAR3_TILT
#define CAMERA_2ND_OIS
#define CAMERA_USE_OIS_VDD_1_8V

/* Firmware and calibration policies shared by all products */
#define CAMERA_OIS_DOM_UPDATE_VERSION		'O'
#define CAMERA_OIS_SEC_UPDATE_VERSION		'P'
#define CAMERA_MODULE_DUAL_CAL_AVAILABLE_VERSION	'A'
#define CAMERA_OIS_GYRO_OFFSET_SPEC		10000
#define IS_MAX_FW_BUFFER_SIZE			(4100 * 1024)

/* ISP chain / framework options shared by all products */
#define RTA_CODE_AREA_SIZE			(0x00180000)
#define USE_CAMERA_EMBEDDED_HEADER
#define USE_CAMERA_MIPI_CLOCK_VARIATION
#define USE_CAMERA_HW_BIG_DATA
#define USE_AF_SLEEP_MODE
#define USE_NEW_PER_FRAME_CONTROL
#if defined(CONFIG_USE_CAMERA_LDU) || defined(CONFIG_SEC_FACTORY)
#define USE_OIS_SHIFT_FOR_APERTURE
#if defined(CONFIG_SEC_FACTORY)
#define OIS_SHIFT_OFFSET_VALUE_NORMAL		0
#else
#define OIS_SHIFT_OFFSET_VALUE_NORMAL		1000
#endif
#endif
#define USE_SENSOR_LONG_EXPOSURE_SHOT
#define OIS_DUAL_CAL_DEFAULT_VALUE_WIDE		0

#define CSI_SCENARIO_SEN_FRONT			(1)
#define CSI_SCENARIO_TELE			(2)
#define CSI_SCENARIO_SECURE			(3)
#define CSI_SCENARIO_SEN_REAR			(0)

/* ------------------------------------------------------------------------- */
/* Union of the per-product features                                         */
/* Each feature is gated at runtime where it changes behavior.               */
/* ------------------------------------------------------------------------- */

/* Shift crop: x1s/y2s/c1s/c2s/r8s; gated at runtime for the sensor mode. */
#define CAMERA_REAR2_SENSOR_SHIFT_CROP
#define CAMERA_2LD_SLOW_MOTION_PDAF_OFF
#define CAMERA_USE_TELE_VFLIP
#define FIXED_SENSOR_CROP_SHIFT_NUM		5

/* GW2 PDXTC calibration version: same 'B' on every product that uses GW2. */
#define CAMERA_GW2_PDXTC_MODULE_VERSION		'B'

/* z3s sensors: IMX586/GH1 are not present on the other products. */
#define CAMERA_IMX586_CAL_MODULE_VERSION	'B'
#define CAMERA_GH1_CAL_MODULE_VERSION		'B'
#define CAMERA_GH1_CAL_MODULE_VERSION_FOR_Z3

/*
 * The HM1 calibration layout is shared by z3s and c2s, but only z3s checks
 * the module version. The driver tests is_vendor_cfg()->hm1_cal_check.
 */
#define CAMERA_HM1_CAL_MODULE_VERSION		'M'

/* TOF: present on y2s and z3s; c2s keeps the AF control but no sensor. */
#define CAMERA_REAR_TOF
#define CAMERA_REAR_TOF_CAL
#define CAMERA_REAR4_TOF_MODULEID		/* rear tof moduleid */
#define CAMERA_REAR_TOF_TILT			/* wide - tof */
#define CAMERA_REAR2_TOF_TILT			/* ultrawide - tof tilt */
#define USE_TOF_AF
#define TOF_MODULE_CHECK_ID			0xB903
#define USE_CAMERA_REAR_TOF_TX_FREQ_VARIATION
#define REAR_TOF_ROM_ID				ROM_ID_REAR3
#define REAR_TOF_CHECK_MAP_VERSION		'1'
#define REAR_TOF_DEFAULT_UID			0xCD35
#define REAR_TOF_CHECK_SENSOR_ID		'3' /* '3' => imx516 */
#define REAR_TOF_IMX316_CRC_ADDR1_MAP001	0x11E1 /* map ver01 */
#define REAR_TOF_IMX316_CRC_ADDR1_MAP002	0x11E3 /* map ver02 */

/* EX mode option: z3s/c2s use it; harmless when ex_mode_option is zero. */
#define USE_EX_MODE_OPTION

/* MCU/OIS features: z3s/c2s use them, the other products use the fallback. */
#define USE_TELE_OIS_AF_COMMON_INTERFACE
#define USE_SHARED_REG_MCU_PERI_CON
#define USE_REAR2_OIS_DATA_FROM_EEPROM
#define USE_HIGH_RES_FLASH_FIRE_BEFORE_STREAM_ON

/* c1s/c2s hall data, r8s SPI pad setting and common VDDIO. */
#define USE_OIS_HALL_DATA_FOR_VDIS
#define USE_MCU_SPI_PUD_SETTING
#define CAMERA_USE_COMMON_VDDIO
#define USE_CAMFW_POLICY_ED38

/* c2s HM1 MIPI strength, x1s/y2s/c1s/c2s buck2 regulator. */
#define USE_WIDE_MIPI_STRENGTH_490MV
#define USE_BUCK2_REGULATOR_CONTROL

/* Debug/calibration attributes: a superset is harmless on the other units. */
#define CAMERA_REAR3_MODULEID
#define LEDS_S2MPB02_ADAPTIVE_MOVIE_CURRENT	120

/*
 * Neutral EEPROM layout. The real size and PAF offsets are taken from
 * is_vendor_cfg() at runtime; these values only keep the compile-time code
 * paths present and give a safe upper bound for the calibration buffer.
 */
#define IS_MAX_CAL_SIZE				(64 * 1024)
#define ROM_PAF_CAL_DATA_START_ADDR		0
#define ROM_REAR3_PAF_CAL_DATA_START_ADDR	0
#define ROM_PAF_CAL_DATA_START_ADDR_FRONT	0
#define ROM_PAF_CAL_ERR_CHECK_OFFSET		0x14

#endif /* IS_VENDOR_CONFIG_UNIVERSAL9830_H */
