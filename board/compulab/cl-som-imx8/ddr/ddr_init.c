/*
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <asm/arch/ddr_memory_map.h>
#include <asm/arch/clock.h>
#include "ddr.h"

#ifdef CONFIG_ENABLE_DDR_TRAINING_DEBUG
#define ddr_printf(args...) printf(args)
#else
#define ddr_printf(args...)
#endif

#include "wait_ddrphy_training_complete.c"
#ifndef SRC_DDRC_RCR_ADDR
#define SRC_DDRC_RCR_ADDR SRC_IPS_BASE_ADDR +0x1000
#endif
#ifndef DDR_CSD1_BASE_ADDR
#define DDR_CSD1_BASE_ADDR 0x40000000
#endif
#define SILICON_TRAIN

void ddr_init(void)
{
	volatile unsigned int tmp, tmp_t;
	/** Initialize DDR clock and DDRC registers **/
	reg32_write(0x3038a088,0x7070000);
	reg32_write(0x3038a084,0x4030000);
	reg32_write(0x303a00ec,0xffff);
	tmp=reg32_read(0x303a00f8);
	tmp |= 0x20;
	reg32_write(0x303a00f8,tmp);
	reg32_write(0x30391000,0x8f000000);
	reg32_write(0x30391004,0x8f000000);
	reg32_write(0x30360068,0xbbe580);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x80;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp |= 0x200;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x20;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x10;
	reg32_write(0x30360060,tmp);
	do{
		tmp=reg32_read(0x30360060);
		if(tmp&0x80000000) break;
	}while(1);
	reg32_write(0x30391000,0x8f000006);
	reg32_write(0x3d400304,0x1);
	reg32_write(0x3d400030,0x1);
	reg32_write(0x3d400000,0x83080020);
	reg32_write(0x3d400064,0x6100e0);
	reg32_write(0x3d4000d0,0xc003061b);
	reg32_write(0x3d4000d4,0x9d0000);
	reg32_write(0x3d4000dc,0xd4002d);
	reg32_write(0x3d4000e0,0x310008);
	reg32_write(0x3d4000e8,0x46004d);
	reg32_write(0x3d4000ec,0x15004d);
	reg32_write(0x3d4000f4,0x639);
	reg32_write(0x3d400100,0x1a201b22);
	reg32_write(0x3d400104,0x60633);
	reg32_write(0x3d400108,0x70e1114);
	reg32_write(0x3d40010c,0xc0c000);
	reg32_write(0x3d400110,0xf04080f);
	reg32_write(0x3d400114,0x2040c0c);
	reg32_write(0x3d400118,0x1010007);
	reg32_write(0x3d40011c,0x401);
	reg32_write(0x3d400130,0x20600);
	reg32_write(0x3d400134,0xc100002);
	reg32_write(0x3d400138,0xe6);
	reg32_write(0x3d400144,0xa00050);
	reg32_write(0x3d400180,0x3200018);
	reg32_write(0x3d400184,0x28061a8);
	reg32_write(0x3d400190,0x497820a);
	reg32_write(0x3d400194,0x80303);
	reg32_write(0x3d4001b4,0x170a);
	reg32_write(0x3d4001b0,0x11);
	reg32_write(0x3d4001a0,0xe0400018);
	reg32_write(0x3d4001a4,0xdf00e4);
	reg32_write(0x3d4001a8,0x0);
	reg32_write(0x3d4001c0,0x1);
	reg32_write(0x3d4001c4,0x1);
	reg32_write(0x3d400200,0x16);
	reg32_write(0x3d40020c,0x0);
	reg32_write(0x3d400210,0x1f1f);
	reg32_write(0x3d400204,0x80808);
	reg32_write(0x3d400214,0x7070707);
	reg32_write(0x3d400218,0xf070707);
	reg32_write(0x3d400244,0x0);
	reg32_write(0x3d400490,0x1);
	reg32_write(0x30391000,0x8f000004);
	reg32_write(0x30391000,0x8f000000);
	reg32_write(0x3d400304,0x0);
	reg32_write(0x3d400030,0xa8);
	reg32_write(0x3d400320,0x0);
	reg32_write(0x3d000000,0x1);
	reg32_write(0x3d4001b0,0x10);

	/* die # 0 map 0-7 */
	reg32_write(0x3c040280,0x0);
	reg32_write(0x3c040284,0x1);
	reg32_write(0x3c040288,0x2);
	reg32_write(0x3c04028c,0x3);
	reg32_write(0x3c040290,0x4);
	reg32_write(0x3c040294,0x5);
	reg32_write(0x3c040298,0x6);
	reg32_write(0x3c04029c,0x7);

	/* die # 0 map 8-15 */
	reg32_write(0x3c044280,0x2);
	reg32_write(0x3c044284,0x6);
	reg32_write(0x3c044288,0x4);
	reg32_write(0x3c04428c,0x7);
	reg32_write(0x3c044290,0x5);
	reg32_write(0x3c044294,0x3);
	reg32_write(0x3c044298,0x0);
	reg32_write(0x3c04429c,0x1);

	/* die # 1 map 0-7 */
	reg32_write(0x3c048280,0x0);
	reg32_write(0x3c048284,0x1);
	reg32_write(0x3c048288,0x2);
	reg32_write(0x3c04828c,0x3);
	reg32_write(0x3c048290,0x4);
	reg32_write(0x3c048294,0x5);
	reg32_write(0x3c048298,0x6);
	reg32_write(0x3c04829c,0x7);

	/* die # 1 map 8-15 */
	reg32_write(0x3c04c280,0x1);
	reg32_write(0x3c04c284,0x3);
	reg32_write(0x3c04c288,0x4);
	reg32_write(0x3c04c28c,0x7);
	reg32_write(0x3c04c290,0x6);
	reg32_write(0x3c04c294,0x5);
	reg32_write(0x3c04c298,0x0);
	reg32_write(0x3c04c29c,0x2);

	/* Configure LPDDR4 PHY's registers */
	lpddr4_cfg_phy();

	reg32_write(DDRC_RFSHCTL3(0), 0x00000000);
	reg32_write(DDRC_SWCTL(0), 0x0000);
	/*
	 * ------------------- 9 -------------------
	 * Set DFIMISC.dfi_init_start to 1 
	 *  -----------------------------------------
	 */
	reg32_write(DDRC_DFIMISC(0), 0x00000030);
	reg32_write(DDRC_SWCTL(0), 0x0001);

	/* wait DFISTAT.dfi_init_complete to 1 */
	tmp_t = 0;
	while(tmp_t==0){
		tmp  = reg32_read(DDRC_DFISTAT(0));
		tmp_t = tmp & 0x01;
		tmp  = reg32_read(DDRC_MRSTAT(0));
	}

	reg32_write(DDRC_SWCTL(0), 0x0000);

	/* clear DFIMISC.dfi_init_complete_en */
	reg32_write(DDRC_DFIMISC(0), 0x00000010);
	reg32_write(DDRC_DFIMISC(0), 0x00000011);
	reg32_write(DDRC_PWRCTL(0), 0x00000088);

	tmp = reg32_read(DDRC_CRCPARSTAT(0));
	/*
	 * set SWCTL.sw_done to enable quasi-dynamic register
	 * programming outside reset.
	 */
	reg32_write(DDRC_SWCTL(0), 0x00000001);

	/* wait SWSTAT.sw_done_ack to 1 */
	while((reg32_read(DDRC_SWSTAT(0)) & 0x1) == 0)
		;

	/* wait STAT.operating_mode([1:0] for ddr3) to normal state */
	while ((reg32_read(DDRC_STAT(0)) & 0x3) != 0x1)
		;

	reg32_write(DDRC_PWRCTL(0), 0x00000088);
	/* reg32_write(DDRC_PWRCTL(0), 0x018a); */
	tmp = reg32_read(DDRC_CRCPARSTAT(0));

	/* enable port 0 */
	reg32_write(DDRC_PCTRL_0(0), 0x00000001);
	tmp = reg32_read(DDRC_CRCPARSTAT(0));
	reg32_write(DDRC_RFSHCTL3(0), 0x00000000);
}
