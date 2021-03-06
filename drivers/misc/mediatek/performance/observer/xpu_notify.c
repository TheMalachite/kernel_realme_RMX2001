/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
#define pr_fmt(fmt) "pob_xpu: " fmt
#include <linux/notifier.h>
#include <mt-plat/mtk_perfobserver.h>

static BLOCKING_NOTIFIER_HEAD(pob_xpufreq_notifier_list);

int pob_xpufreq_register_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&pob_xpufreq_notifier_list, nb);
}
EXPORT_SYMBOL(pob_xpufreq_register_client);

int pob_xpufreq_unregister_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&pob_xpufreq_notifier_list,
							nb);
}
EXPORT_SYMBOL(pob_xpufreq_unregister_client);

int pob_xpufreq_notifier_call_chain(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(&pob_xpufreq_notifier_list, val, v);
}

int pob_xpufreq_update(enum pob_xpufreq_info_num info_num,
			struct pob_xpufreq_info *v)
{
	pob_xpufreq_notifier_call_chain(info_num, v);

	return 0;
}
EXPORT_SYMBOL(pob_xpufreq_update);
