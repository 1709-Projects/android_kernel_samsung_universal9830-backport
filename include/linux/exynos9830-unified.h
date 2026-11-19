/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Device family helpers for the unified Exynos 990 kernel.
 *
 * The unified image runs on several products that share the SoC but use
 * different touch controllers and board options.  The root device tree model
 * is the same identifier the camera runtime configuration uses, with the
 * Android boot parameter as a fallback.
 */
#ifndef _LINUX_EXYNOS9830_UNIFIED_H
#define _LINUX_EXYNOS9830_UNIFIED_H

#include <linux/init.h>
#include <linux/of.h>
#include <linux/string.h>
#include <linux/types.h>

static inline const char *exynos9830_model(void)
{
	const char *model = NULL;

#ifdef CONFIG_OF
	if (of_root)
		of_property_read_string(of_root, "model", &model);
#endif
	return model;
}

static inline bool exynos9830_model_has_prefix(const char *prefix)
{
	const char *model = exynos9830_model();

	return model && !strncmp(model, prefix, strlen(prefix));
}

static inline bool exynos9830_cmdline_has(const char *param)
{
	return saved_command_line && strstr(saved_command_line, param);
}

/*
 * Galaxy Note20 family (c1s/c2s and their LTE variants) uses the Y79A_C
 * touch controller.  The S20 family uses Y79A and the S20 FE uses Zinitix.
 */
static inline bool exynos9830_is_cnt_touch(void)
{
	if (exynos9830_model_has_prefix("Samsung C1S") ||
	    exynos9830_model_has_prefix("Samsung C2S"))
		return true;

	return exynos9830_cmdline_has("androidboot.device=c1s") ||
	       exynos9830_cmdline_has("androidboot.device=c2s");
}

/*
 * Sensor hub factory layout.  The S20 family uses the SSP chip specific
 * factory implementations, while the Note20 family and the S20 FE use the
 * dynamic sensor list and direct sensor drivers.
 */
static inline bool exynos9830_is_hst(void)
{
	if (exynos9830_model_has_prefix("Samsung X1S") ||
	    exynos9830_model_has_prefix("Samsung Y2S") ||
	    exynos9830_model_has_prefix("Samsung Z3S"))
		return true;

	if (exynos9830_model_has_prefix("Samsung C1S") ||
	    exynos9830_model_has_prefix("Samsung C2S") ||
	    exynos9830_model_has_prefix("Samsung R8S"))
		return false;

	if (exynos9830_cmdline_has("androidboot.device=c1s") ||
	    exynos9830_cmdline_has("androidboot.device=c2s") ||
	    exynos9830_cmdline_has("androidboot.device=r8s") ||
	    exynos9830_cmdline_has("androidboot.device=c1slte") ||
	    exynos9830_cmdline_has("androidboot.device=c2slte"))
		return false;

	/* The base defconfig targets the S20 family; keep that as default. */
	return true;
}


/*
 * Display/panel family.  The unified image contains every panel driver, but
 * only the drivers that belong to the running product may register their
 * panel descriptions.  Selecting the family here keeps the boot-time panel
 * list identical to a per-device build.
 */
enum exynos9830_display_family_id {
	EXYNOS9830_DISPLAY_S20,
	EXYNOS9830_DISPLAY_C1,
	EXYNOS9830_DISPLAY_C2,
	EXYNOS9830_DISPLAY_R8,
};

static inline int exynos9830_display_family(void)
{
	if (exynos9830_model_has_prefix("Samsung C1S") ||
	    exynos9830_cmdline_has("androidboot.device=c1s"))
		return EXYNOS9830_DISPLAY_C1;

	if (exynos9830_model_has_prefix("Samsung C2S") ||
	    exynos9830_cmdline_has("androidboot.device=c2s"))
		return EXYNOS9830_DISPLAY_C2;

	if (exynos9830_model_has_prefix("Samsung R8S") ||
	    exynos9830_cmdline_has("androidboot.device=r8s"))
		return EXYNOS9830_DISPLAY_R8;

	return EXYNOS9830_DISPLAY_S20;
}

static inline bool exynos9830_panel_is_s20(void)
{
	return exynos9830_display_family() == EXYNOS9830_DISPLAY_S20;
}

static inline bool exynos9830_panel_is_c1(void)
{
	return exynos9830_display_family() == EXYNOS9830_DISPLAY_C1;
}

static inline bool exynos9830_panel_is_c2(void)
{
	return exynos9830_display_family() == EXYNOS9830_DISPLAY_C2;
}

static inline bool exynos9830_panel_is_r8(void)
{
	return exynos9830_display_family() == EXYNOS9830_DISPLAY_R8;
}


static inline bool exynos9830_display_use_decon_board(void)
{
	return IS_ENABLED(CONFIG_PANEL_DECON_BOARD) &&
	       exynos9830_panel_is_r8();
}

static inline bool exynos9830_display_use_vrr_mod(void)
{
	return IS_ENABLED(CONFIG_DECON_VRR_MODULATION) &&
	       exynos9830_panel_is_c2();
}


static inline bool exynos9830_display_use_doze_first_frame_black(void)
{
	return IS_ENABLED(CONFIG_EXYNOS_DOZE_FIRST_FRAME_BLACK) &&
	       exynos9830_panel_is_r8();
}

static inline bool exynos9830_display_use_mask_layer(void)
{
	return IS_ENABLED(CONFIG_SUPPORT_MASK_LAYER) &&
	       exynos9830_panel_is_r8();
}

static inline bool exynos9830_display_use_bts_vrr_async(void)
{
	return IS_ENABLED(CONFIG_DECON_BTS_VRR_ASYNC) &&
	       (exynos9830_panel_is_s20() || exynos9830_panel_is_r8());
}

static inline bool exynos9830_display_use_vrr_bridge(void)
{
	return IS_ENABLED(CONFIG_PANEL_VRR_BRIDGE) &&
	       exynos9830_panel_is_s20();
}

static inline bool exynos9830_display_use_dim_flash(void)
{
	return IS_ENABLED(CONFIG_SUPPORT_DIM_FLASH) &&
	       exynos9830_panel_is_s20();
}

#endif /* _LINUX_EXYNOS9830_UNIFIED_H */
