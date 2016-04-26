/*
 * Copyright 2011 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 *
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <linux/init.h>
#include <linux/smp.h>
#include <asm/cacheflush.h>
#include <asm/page.h>
#include <asm/smp_scu.h>
#include <asm/mach/map.h>
#include <asm/cputype.h>

#include "common.h"
#include "hardware.h"

u32 g_diag_reg;
static void __iomem *scu_base;

static unsigned long cpu_part_number;

static struct map_desc scu_io_desc __initdata = {
	/* .virtual and .pfn are run-time assigned */
	.length		= SZ_4K,
	.type		= MT_DEVICE,
};

void __init imx_scu_map_io(void)
{
	unsigned long base;

	/* Get SCU base */
	asm("mrc p15, 4, %0, c15, c0, 0" : "=r" (base));

	scu_io_desc.virtual = IMX_IO_P2V(base);
	scu_io_desc.pfn = __phys_to_pfn(base);
	iotable_init(&scu_io_desc, 1);

	scu_base = IMX_IO_ADDRESS(base);
}

static int imx_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	imx_set_cpu_jump(cpu, v7_secondary_startup);
	imx_enable_cpu(cpu, true);

	return 0;
}

static int __cpuinit sac58r_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	imx_set_cpu_jump(cpu, sac58r_secondary_startup);
	imx_enable_cpu(cpu, true);

	return 0;
}
/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the system.
 */
static void __init imx_smp_init_cpus(void)
{
	int i, ncores;

	cpu_part_number = read_cpuid_part();

	switch (cpu_part_number)
	{
		case ARM_CPU_PART_CORTEX_A7:
			/* sac58R and other A7 based SoC */
			/* get number of cores from CP15 L2 controller register(L2CTLR)*/
			asm volatile ("mrc p15, 1, %0, c9, c0, 2" : "=r" (ncores));
			ncores = ((ncores >> 24) & 0x3) + 1;
			break;

		case ARM_CPU_PART_CORTEX_A9:
		default:
			/* i.MX6 and other A9 based SoC */
			ncores = scu_get_core_count(scu_base);
			break;
	}

	for (i = ncores; i < NR_CPUS; i++)
		set_cpu_possible(i, false);
}

void imx_smp_prepare(void)
{
	scu_enable(scu_base);
}

static void __init imx_smp_prepare_cpus(unsigned int max_cpus)
{
	if (ARM_CPU_PART_CORTEX_A9 == cpu_part_number)
	{
		imx_smp_prepare();

		/*
		 * The diagnostic register holds the errata bits.  Mostly bootloader
		 * does not bring up secondary cores, so that when errata bits are set
		 * in bootloader, they are set only for boot cpu.  But on a SMP
		 * configuration, it should be equally done on every single core.
		 * Read the register from boot cpu here, and will replicate it into
		 * secondary cores when booting them.
		 */
		asm("mrc p15, 0, %0, c15, c0, 1" : "=r" (g_diag_reg) : : "cc");
		__cpuc_flush_dcache_area(&g_diag_reg, sizeof(g_diag_reg));
		outer_clean_range(__pa(&g_diag_reg), __pa(&g_diag_reg + 1));
	}
}

struct smp_operations  imx_smp_ops __initdata = {
	.smp_init_cpus		= imx_smp_init_cpus,
	.smp_prepare_cpus	= imx_smp_prepare_cpus,
	.smp_boot_secondary	= imx_boot_secondary,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_die		= imx_cpu_die,
	.cpu_kill		= imx_cpu_kill,
#endif
};

struct smp_operations  sac58r_smp_ops __initdata = {
	.smp_init_cpus		= imx_smp_init_cpus,
	.smp_prepare_cpus	= imx_smp_prepare_cpus,
	.smp_boot_secondary	= sac58r_boot_secondary,
};
