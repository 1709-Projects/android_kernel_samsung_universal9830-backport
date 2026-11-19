// SPDX-License-Identifier: GPL-2.0
/*
 * Runtime camera configuration for the unified Exynos 990 kernel.
 *
 * One kernel image carries the drivers of every supported product, so the
 * per-product vendor configuration has to be chosen at runtime. The root
 * device tree model is the authoritative source; the Android boot parameter
 * is only used as a fallback.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/string.h>

#include "is-vendor-config-runtime.h"

static const struct is_vendor_config hst_v01_cfg = {
	.name = "hst_v01",
	.shift_crop = true,
	.slow_motion_pdaf_off = true,
	.gw2_pdxtc_version = 'B',
	.tele_ois_tilt_rom_id = -1,
	.ois_default_tele = 0,
	.ois_eeprom_default_tele = -1,
	.use_buck2 = true,
	.leds_s2mpb02 = true,
	.leds_s2mpb02_movie_current = 120,
	.max_cal_size = 64 * 1024,
	.paf_cal_start = 0x1C00,
	.rear3_paf_cal_start = 0x5A00,
	.front_paf_cal_start = 0x200,
	.paf_cal_err_check_offset = 0x14,
};

static const struct is_vendor_config hst_v02_cfg = {
	.name = "hst_v02",
	.shift_crop = true,
	.slow_motion_pdaf_off = true,
	.rear_tof = true,
	.rear_tof_cal = true,
	.rear4_tof_moduleid = true,
	.rear_tof_tilt = true,
	.rear2_tof_tilt = true,
	.tof_io_denoise = true,
	.tof_tx_freq_variation = true,
	.tof_check_map_version = '1',
	.tof_check_sensor_id = '3',
	.tof_default_uid = 0xCD35,
	.tof_crc_addr1_map001 = 0x11E1,
	.tof_crc_addr1_map002 = 0x11E3,
	.tele_ois_tilt_rom_id = -1,
	.ois_default_tele = 0,
	.ois_eeprom_default_tele = -1,
	.use_buck2 = true,
	.leds_s2mpb02 = true,
	.leds_s2mpb02_movie_current = 120,
	.max_cal_size = 64 * 1024,
	.paf_cal_start = 0x1C00,
	.rear3_paf_cal_start = 0x5A00,
	.front_paf_cal_start = 0x200,
	.paf_cal_err_check_offset = 0x14,
};

static const struct is_vendor_config hst_v03_cfg = {
	.name = "hst_v03",
	.rear_tof = true,
	.rear_tof_cal = true,
	.rear4_tof_moduleid = true,
	.rear_tof_tilt = true,
	.rear2_tof_tilt = true,
	.tof_af = true,
	.tof_module_check_id = 0xB903,
	.tof_io_denoise = true,
	.tof_tx_freq_variation = true,
	.tof_check_map_version = '1',
	.tof_check_sensor_id = '3',
	.tof_default_uid = 0xCD35,
	.tof_crc_addr1_map001 = 0x11E1,
	.tof_crc_addr1_map002 = 0x11E3,
	.ex_mode_option = true,
	.tele_ois_af_common = true,
	.high_res_flash_before_stream = true,
	.shared_reg_mcu_peri = true,
	.rear2_ois_from_eeprom = true,
	.rear3_moduleid = true,
	.hm1_cal_check = true,
	.hm1_cal_version = 'M',
	.tele_ois_tilt_rom_id = 6,
	.ois_default_tele = 0,
	.ois_eeprom_default_tele = -1,
	.use_buck2 = true,
	.leds_s2mpb02 = true,
	.leds_s2mpb02_movie_current = 120,
	.max_cal_size = 64 * 1024,
	.paf_cal_start = 0x2300,
	.rear3_paf_cal_start = 0x2300,
	.front_paf_cal_start = 0x2300,
	.paf_cal_err_check_offset = 0x14,
};

static const struct is_vendor_config cnt_v01_cfg = {
	.name = "cnt_v01",
	.shift_crop = true,
	.slow_motion_pdaf_off = true,
	.ois_hall_vdis = true,
	.camfw_policy_ed38 = true,
	.gw2_pdxtc_version = 'B',
	.tele_ois_tilt_rom_id = -1,
	.ois_default_tele = 0,
	.ois_eeprom_default_tele = -1,
	.use_buck2 = true,
	.leds_s2mpb02 = true,
	.leds_s2mpb02_movie_current = 120,
	.max_cal_size = 64 * 1024,
	.paf_cal_start = 0x1C00,
	.rear3_paf_cal_start = 0x5A00,
	.front_paf_cal_start = 0x200,
	.paf_cal_err_check_offset = 0x14,
};

static const struct is_vendor_config cnt_v02_cfg = {
	.name = "cnt_v02",
	.shift_crop = true,
	.tele_vflip = true,
	.fixed_crop_shift_num = 5,
	.tof_tx_freq_variation = true,
	.ex_mode_option = true,
	.ois_hall_vdis = true,
	.tele_ois_af_common = true,
	.high_res_flash_before_stream = true,
	.shared_reg_mcu_peri = true,
	.rear2_ois_from_eeprom = true,
	.use_buck2 = true,
	.camfw_policy_ed38 = true,
	.wide_mipi_strength_490mv = true,
	.rear3_moduleid = true,
	.tele_ois_tilt_rom_id = 4,
	.ois_default_tele = -1,
	.ois_eeprom_default_tele = 0,
	.leds_s2mpb02 = true,
	.leds_s2mpb02_movie_current = 120,
	.max_cal_size = 64 * 1024,
	.paf_cal_start = 0x2300,
	.rear3_paf_cal_start = 0x2300,
	.front_paf_cal_start = 0x200,
	.paf_cal_err_check_offset = 0x14,
};

static const struct is_vendor_config rst_v08_cfg = {
	.name = "rst_v08",
	.shift_crop = true,
	.mcu_spi_pud = true,
	.camfw_policy_ed38 = true,
	.use_common_vddio = true,
	.front_fixed_focus = true,
	.rear3_moduleid = true,
	.tele_ois_tilt_rom_id = 4,
	.ois_default_tele = 0,
	.ois_eeprom_default_tele = -1,
	.max_cal_size = 16 * 1024,
	.paf_cal_start = 0x1C00,
	.rear3_paf_cal_start = 0x1C00,
	.front_paf_cal_start = 0,
	.paf_cal_err_check_offset = 0x14,
};

static const struct is_vendor_config *is_vendor_cfg_selected;

static const struct is_vendor_config *is_vendor_cfg_from_model(const char *model)
{
	if (!model)
		return NULL;

	if (!strncmp(model, "Samsung X1S", 11))
		return &hst_v01_cfg;
	if (!strncmp(model, "Samsung Y2S", 11))
		return &hst_v02_cfg;
	if (!strncmp(model, "Samsung Z3S", 11))
		return &hst_v03_cfg;
	if (!strncmp(model, "Samsung C1S", 11))
		return &cnt_v01_cfg;
	if (!strncmp(model, "Samsung C2S", 11))
		return &cnt_v02_cfg;
	if (!strncmp(model, "Samsung R8S", 11))
		return &rst_v08_cfg;

	return NULL;
}

static const struct is_vendor_config *is_vendor_cfg_from_cmdline(void)
{
	if (!saved_command_line)
		return NULL;

	if (strstr(saved_command_line, "androidboot.device=x1s"))
		return &hst_v01_cfg;
	if (strstr(saved_command_line, "androidboot.device=y2s"))
		return &hst_v02_cfg;
	if (strstr(saved_command_line, "androidboot.device=z3s"))
		return &hst_v03_cfg;
	if (strstr(saved_command_line, "androidboot.device=c1s"))
		return &cnt_v01_cfg;
	if (strstr(saved_command_line, "androidboot.device=c2s"))
		return &cnt_v02_cfg;
	if (strstr(saved_command_line, "androidboot.device=r8s"))
		return &rst_v08_cfg;

	return NULL;
}

void is_vendor_config_init(void)
{
	const struct is_vendor_config *cfg;
	const char *model = NULL;

	if (READ_ONCE(is_vendor_cfg_selected))
		return;

#ifdef CONFIG_OF
	if (of_root && of_property_read_string(of_root, "model", &model))
		model = NULL;
#endif

	cfg = is_vendor_cfg_from_model(model);
	if (!cfg)
		cfg = is_vendor_cfg_from_cmdline();
	if (!cfg)
		cfg = &hst_v02_cfg;

	WRITE_ONCE(is_vendor_cfg_selected, cfg);

	pr_info("is-vendor: using %s camera configuration%s%s\n",
		cfg->name, model ? " for " : "", model ? model : "");
}

const struct is_vendor_config *is_vendor_cfg(void)
{
	const struct is_vendor_config *cfg = READ_ONCE(is_vendor_cfg_selected);

	if (unlikely(!cfg)) {
		is_vendor_config_init();
		cfg = READ_ONCE(is_vendor_cfg_selected);
	}

	return cfg;
}
