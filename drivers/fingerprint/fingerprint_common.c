// SPDX-License-Identifier: GPL-2.0
/*
 * Shared state between the fingerprint drivers. The pinctrl driver calls
 * fps_resume_set() on resume, so the symbol must exist exactly once even
 * when several fingerprint drivers are built into the same kernel image.
 */

#include "fingerprint.h"

#if defined(ENABLE_SENSORS_FPRINT_SECURE)
int fpsensor_goto_suspend = 0;

int fps_resume_set(void) {
	int rc = 0;

	if (fpsensor_goto_suspend)
		fpsensor_goto_suspend = 0;
	return rc;
}
#endif
