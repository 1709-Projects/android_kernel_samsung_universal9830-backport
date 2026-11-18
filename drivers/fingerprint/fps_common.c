// SPDX-License-Identifier: GPL-2.0
/*
 * Shared fingerprint suspend state.
 *
 * The pinctrl driver calls fps_resume_set() when it restores pin state.
 * A unified kernel builds more than one fingerprint driver, so the flag
 * and the helper live here instead of in every driver.
 */

#if defined(ENABLE_SENSORS_FPRINT_SECURE)
int fpsensor_goto_suspend;

int fps_resume_set(void)
{
	if (fpsensor_goto_suspend)
		fpsensor_goto_suspend = 0;

	return 0;
}
#endif
