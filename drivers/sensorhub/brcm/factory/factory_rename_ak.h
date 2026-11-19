/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Symbol remapping for the unified sensor factory dispatch.
 * Only active when both factory implementations are built in.
 */
#ifndef __FACTORY_RENAME_AK_H
#define __FACTORY_RENAME_AK_H

#ifdef CONFIG_SENSORS_FACTORY_UNIFIED

#define get_fuserom_data ak09918c_get_fuserom_data

#endif

#endif
