/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Runtime camera configuration for the unified Exynos 990 kernel.
 *
 * The vendor configuration headers describe one product each. A kernel that
 * supports several products cannot include all of them at the same time, so
 * the values that really differ between products live in this structure and
 * are selected once from the root device tree model.
 */

#ifndef IS_VENDOR_CONFIG_RUNTIME_H
#define IS_VENDOR_CONFIG_RUNTIME_H

#include <linux/types.h>

struct is_vendor_config {
	const char *name;

	/* Behavior flags that differ between products */
	bool shift_crop;
	bool slow_motion_pdaf_off;
	bool tele_vflip;
	u32 fixed_crop_shift_num;

	bool rear_tof;
	bool rear_tof_cal;
	bool rear4_tof_moduleid;
	bool rear_tof_tilt;
	bool rear2_tof_tilt;
	bool tof_af;
	u16 tof_module_check_id;
	bool tof_io_denoise;
	bool tof_tx_freq_variation;
	bool tof_tx_freq_variation_sysfs;
	u8 tof_check_map_version;
	u8 tof_check_sensor_id;
	u16 tof_default_uid;
	u16 tof_crc_addr1_map001;
	u16 tof_crc_addr1_map002;

	bool ex_mode_option;
	bool ois_hall_vdis;
	bool tele_ois_af_common;
	bool high_res_flash_before_stream;
	bool shared_reg_mcu_peri;
	bool mcu_spi_pud;
	bool rear2_ois_from_eeprom;

	bool use_buck2;
	bool camfw_policy_ed38;
	bool wide_mipi_strength_490mv;
	bool use_common_vddio;
	bool front_fixed_focus;
	bool rear3_moduleid;

	/* Module calibration versions */
	bool hm1_cal_check;
	u8 hm1_cal_version;
	u8 gw2_pdxtc_version;		/* 0: no version check */

	/* OIS calibration */
	int tele_ois_tilt_rom_id;	/* -1: not used */
	int ois_default_tele;		/* -1: not used */
	int ois_eeprom_default_tele;	/* -1: not used */

	/* Flash */
	bool leds_s2mpb02;
	u32 leds_s2mpb02_movie_current;

	/* EEPROM map */
	u32 max_cal_size;
	u32 paf_cal_start;
	u32 rear3_paf_cal_start;
	u32 front_paf_cal_start;
	u32 paf_cal_err_check_offset;
};

const struct is_vendor_config *is_vendor_cfg(void);
void is_vendor_config_init(void);

#endif /* IS_VENDOR_CONFIG_RUNTIME_H */
