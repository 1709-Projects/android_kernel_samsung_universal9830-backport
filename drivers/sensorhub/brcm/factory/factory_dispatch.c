// SPDX-License-Identifier: GPL-2.0
/*
 * Runtime sensor factory dispatch for the unified Exynos 990 kernel.
 *
 * The S20 family uses the SSP chip factory implementations (LSM6DSO and the
 * common magnetic code), while the Note20 family and the S20 FE use the
 * dynamic sensor factory plus the direct AK09918C driver.  Both sets are
 * built into the unified image; the renamed implementations below are picked
 * from the device tree model at runtime.
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/exynos9830-unified.h>

#include "../ssp.h"

#ifdef CONFIG_SENSORS_FACTORY_UNIFIED

/* Generic dynamic-list implementations */
extern int gen_accel_open_calibration(struct ssp_data *data);
extern void gen_initialize_accel_factorytest(struct ssp_data *data);
extern void gen_remove_accel_factorytest(struct ssp_data *data);
extern void gen_set_AccelCalibrationInfoData(char *pchRcvDataFrame, int *iDataIdx);
extern int gen_set_accel_cal(struct ssp_data *data);

extern int gen_gyro_open_calibration(struct ssp_data *data);
extern void gen_initialize_gyro_factorytest(struct ssp_data *data);
extern void gen_remove_gyro_factorytest(struct ssp_data *data);
extern int gen_save_gyro_caldata(struct ssp_data *data, s32 *iCalData);
extern int gen_send_vdis_flag(struct ssp_data *data, bool bFlag);
extern void gen_set_GyroCalibrationInfoData(char *pchRcvDataFrame, int *iDataIdx);
extern int gen_set_gyro_cal(struct ssp_data *data);

extern int gen_get_hw_offset(struct ssp_data *data);
extern void gen_initialize_magnetic_factorytest(struct ssp_data *data);
extern int gen_initialize_magnetic_sensor(struct ssp_data *data);
extern int gen_load_magnetic_cal_param_from_nvm(u8 *data, u8 length);
extern int gen_mag_open_hwoffset(struct ssp_data *data);
extern int gen_mag_store_hwoffset(struct ssp_data *data);
extern void gen_remove_magnetic_factorytest(struct ssp_data *data);
extern int gen_save_magnetic_cal_param_to_nvm(struct ssp_data *data,
		char *pchRcvDataFrame, int *iDataIdx);
extern int gen_set_hw_offset(struct ssp_data *data);
extern int gen_set_magnetic_cal_param_to_ssp(struct ssp_data *data);

/* SSP chip implementations */
extern int hst_accel_open_calibration(struct ssp_data *data);
extern void hst_initialize_accel_factorytest(struct ssp_data *data);
extern void hst_remove_accel_factorytest(struct ssp_data *data);
extern void hst_set_AccelCalibrationInfoData(char *pchRcvDataFrame, int *iDataIdx);
extern int hst_set_accel_cal(struct ssp_data *data);

extern int hst_gyro_open_calibration(struct ssp_data *data);
extern void hst_initialize_gyro_factorytest(struct ssp_data *data);
extern void hst_remove_gyro_factorytest(struct ssp_data *data);
extern int hst_save_gyro_caldata(struct ssp_data *data, s32 *iCalData);
extern int hst_send_vdis_flag(struct ssp_data *data, bool bFlag);
extern void hst_set_GyroCalibrationInfoData(char *pchRcvDataFrame, int *iDataIdx);
extern int hst_set_gyro_cal(struct ssp_data *data);

extern int hst_get_hw_offset(struct ssp_data *data);
extern void hst_initialize_magnetic_factorytest(struct ssp_data *data);
extern int hst_initialize_magnetic_sensor(struct ssp_data *data);
extern int hst_load_magnetic_cal_param_from_nvm(u8 *data, u8 length);
extern int hst_mag_open_hwoffset(struct ssp_data *data);
extern int hst_mag_store_hwoffset(struct ssp_data *data);
extern void hst_remove_magnetic_factorytest(struct ssp_data *data);
extern int hst_save_magnetic_cal_param_to_nvm(struct ssp_data *data,
		char *pchRcvDataFrame, int *iDataIdx);
extern int hst_set_hw_offset(struct ssp_data *data);
extern int hst_set_magnetic_cal_param_to_ssp(struct ssp_data *data);
extern int hst_get_fuserom_data(struct ssp_data *data);

extern int ak09918c_get_fuserom_data(struct ssp_data *data);

static bool use_hst_factory(void)
{
	return exynos9830_is_hst();
}

int accel_open_calibration(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_accel_open_calibration(data);
	return gen_accel_open_calibration(data);
}

void initialize_accel_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_initialize_accel_factorytest(data);
	else
		gen_initialize_accel_factorytest(data);
}

void remove_accel_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_remove_accel_factorytest(data);
	else
		gen_remove_accel_factorytest(data);
}

void set_AccelCalibrationInfoData(char *pchRcvDataFrame, int *iDataIdx)
{
	if (use_hst_factory())
		hst_set_AccelCalibrationInfoData(pchRcvDataFrame, iDataIdx);
	else
		gen_set_AccelCalibrationInfoData(pchRcvDataFrame, iDataIdx);
}

int set_accel_cal(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_set_accel_cal(data);
	return gen_set_accel_cal(data);
}

int gyro_open_calibration(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_gyro_open_calibration(data);
	return gen_gyro_open_calibration(data);
}

void initialize_gyro_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_initialize_gyro_factorytest(data);
	else
		gen_initialize_gyro_factorytest(data);
}

void remove_gyro_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_remove_gyro_factorytest(data);
	else
		gen_remove_gyro_factorytest(data);
}

int save_gyro_caldata(struct ssp_data *data, s32 *iCalData)
{
	if (use_hst_factory())
		return hst_save_gyro_caldata(data, iCalData);
	return gen_save_gyro_caldata(data, iCalData);
}

int send_vdis_flag(struct ssp_data *data, bool bFlag)
{
	if (use_hst_factory())
		return hst_send_vdis_flag(data, bFlag);
	return gen_send_vdis_flag(data, bFlag);
}

void set_GyroCalibrationInfoData(char *pchRcvDataFrame, int *iDataIdx)
{
	if (use_hst_factory())
		hst_set_GyroCalibrationInfoData(pchRcvDataFrame, iDataIdx);
	else
		gen_set_GyroCalibrationInfoData(pchRcvDataFrame, iDataIdx);
}

int set_gyro_cal(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_set_gyro_cal(data);
	return gen_set_gyro_cal(data);
}

int get_hw_offset(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_get_hw_offset(data);
	return gen_get_hw_offset(data);
}

void initialize_magnetic_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_initialize_magnetic_factorytest(data);
	else
		gen_initialize_magnetic_factorytest(data);
}

int initialize_magnetic_sensor(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_initialize_magnetic_sensor(data);
	return gen_initialize_magnetic_sensor(data);
}

int load_magnetic_cal_param_from_nvm(u8 *data, u8 length)
{
	if (use_hst_factory())
		return hst_load_magnetic_cal_param_from_nvm(data, length);
	return gen_load_magnetic_cal_param_from_nvm(data, length);
}

int mag_open_hwoffset(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_mag_open_hwoffset(data);
	return gen_mag_open_hwoffset(data);
}

int mag_store_hwoffset(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_mag_store_hwoffset(data);
	return gen_mag_store_hwoffset(data);
}

void remove_magnetic_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_remove_magnetic_factorytest(data);
	else
		gen_remove_magnetic_factorytest(data);
}

int save_magnetic_cal_param_to_nvm(struct ssp_data *data,
		char *pchRcvDataFrame, int *iDataIdx)
{
	if (use_hst_factory())
		return hst_save_magnetic_cal_param_to_nvm(data, pchRcvDataFrame,
				iDataIdx);
	return gen_save_magnetic_cal_param_to_nvm(data, pchRcvDataFrame, iDataIdx);
}

int set_hw_offset(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_set_hw_offset(data);
	return gen_set_hw_offset(data);
}

int set_magnetic_cal_param_to_ssp(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_set_magnetic_cal_param_to_ssp(data);
	return gen_set_magnetic_cal_param_to_ssp(data);
}

int get_fuserom_data(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_get_fuserom_data(data);
	return ak09918c_get_fuserom_data(data);
}

extern void gen_initialize_light_factorytest(struct ssp_data *data);
extern int gen_initialize_light_sensor(struct ssp_data *data);
extern void gen_remove_light_factorytest(struct ssp_data *data);
extern int gen_set_lcd_panel_type_to_ssp(struct ssp_data *data);
extern int gen_set_light_cal_param_to_ssp(struct ssp_data *data);
extern void hst_initialize_light_factorytest(struct ssp_data *data);
extern int hst_initialize_light_sensor(struct ssp_data *data);
extern void hst_remove_light_factorytest(struct ssp_data *data);
extern int hst_set_lcd_panel_type_to_ssp(struct ssp_data *data);
extern int hst_set_light_cal_param_to_ssp(struct ssp_data *data);

extern void gen_initialize_prox_factorytest(struct ssp_data *data);
extern int gen_load_prox_cal_from_nvm(int *cal_data, int size);
extern int gen_proximity_save_calibration(int *cal_data, int size);
extern void gen_remove_prox_factorytest(struct ssp_data *data);
extern int gen_set_prox_cal_to_ssp(struct ssp_data *data);
extern void hst_initialize_prox_factorytest(struct ssp_data *data);
extern int hst_load_prox_cal_from_nvm(int *cal_data, int size);
extern int hst_proximity_save_calibration(int *cal_data, int size);
extern void hst_remove_prox_factorytest(struct ssp_data *data);
extern int hst_set_prox_cal_to_ssp(struct ssp_data *data);

extern void gen_initialize_pressure_factorytest(struct ssp_data *data);
extern int gen_pressure_open_calibration(struct ssp_data *data);
extern void gen_remove_pressure_factorytest(struct ssp_data *data);
extern void hst_initialize_pressure_factorytest(struct ssp_data *data);
extern int hst_pressure_open_calibration(struct ssp_data *data);
extern void hst_remove_pressure_factorytest(struct ssp_data *data);

void initialize_light_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_initialize_light_factorytest(data);
	else
		gen_initialize_light_factorytest(data);
}

int initialize_light_sensor(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_initialize_light_sensor(data);
	return gen_initialize_light_sensor(data);
}

void remove_light_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_remove_light_factorytest(data);
	else
		gen_remove_light_factorytest(data);
}

int set_lcd_panel_type_to_ssp(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_set_lcd_panel_type_to_ssp(data);
	return gen_set_lcd_panel_type_to_ssp(data);
}

int set_light_cal_param_to_ssp(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_set_light_cal_param_to_ssp(data);
	return gen_set_light_cal_param_to_ssp(data);
}

void initialize_prox_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_initialize_prox_factorytest(data);
	else
		gen_initialize_prox_factorytest(data);
}

int load_prox_cal_from_nvm(int *cal_data, int size)
{
	if (use_hst_factory())
		return hst_load_prox_cal_from_nvm(cal_data, size);
	return gen_load_prox_cal_from_nvm(cal_data, size);
}

int proximity_save_calibration(int *cal_data, int size)
{
	if (use_hst_factory())
		return hst_proximity_save_calibration(cal_data, size);
	return gen_proximity_save_calibration(cal_data, size);
}

void remove_prox_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_remove_prox_factorytest(data);
	else
		gen_remove_prox_factorytest(data);
}

int set_prox_cal_to_ssp(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_set_prox_cal_to_ssp(data);
	return gen_set_prox_cal_to_ssp(data);
}

void initialize_pressure_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_initialize_pressure_factorytest(data);
	else
		gen_initialize_pressure_factorytest(data);
}

int pressure_open_calibration(struct ssp_data *data)
{
	if (use_hst_factory())
		return hst_pressure_open_calibration(data);
	return gen_pressure_open_calibration(data);
}

void remove_pressure_factorytest(struct ssp_data *data)
{
	if (use_hst_factory())
		hst_remove_pressure_factorytest(data);
	else
		gen_remove_pressure_factorytest(data);
}

#endif /* CONFIG_SENSORS_FACTORY_UNIFIED */
