/*
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * Generated code from MX8M_DDR_tool
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

struct regv {
	unsigned long reg;
	unsigned long value;
};

static struct regv aregv1[] = {
    {0x3d400000,0xa1080020},
    {0x3d400064,0x610090},
    {0x3d400138,0x96},
    {0x3d400200,0x1f},
    {0x3d400218,0xf070707},
    {0x3d402064,0x14001f},
    {0x3d402138,0x20},
    {0x54012,0x110},
    {0x5402c,0x1},
};

static struct regv aregv2[] = {
    {0x3d400000,0xa3080020},
    {0x3d400064,0x6100e0},
    {0x3d400138,0xe6},
    {0x3d400200,0x16},
    {0x3d400218,0xf070707},
    {0x3d402064,0x14002f},
    {0x3d402138,0x31},
    {0x54012,0x310},
    {0x5402c,0x3},
};

static struct regv aregv4[] = {
    {0x3d400000,0xa3080020},
    {0x3d400064,0x6100e0},
    {0x3d400138,0xe6},
    {0x3d400200,0x17},
    {0x3d400218,0x7070707},
    {0x3d402064,0x14002f},
    {0x3d402138,0x31},
    {0x54012,0x310},
    {0x5402c,0x3},
};

enum regs {
    REG0000 = 0x0,
    REG0064 = 0x1,
    REG0138 = 0x2,
    REG0200 = 0x3,
    REG0218 = 0x4,
    REG2064 = 0x5,
    REG2138 = 0x6,
    REG54012 = 0x7,
    REG5402C = 0x8,
};

static unsigned long sdram_size[] = {0, 0x100000000, 0x80000000, 0x40000000};
static struct regv* pregv[] = {NULL, aregv4, aregv2, aregv1};

#define REG0000_VALUE pregv[0][REG0000].value
#define REG0064_VALUE pregv[0][REG0064].value
#define REG0138_VALUE pregv[0][REG0138].value
#define REG0200_VALUE pregv[0][REG0200].value
#define REG0218_VALUE pregv[0][REG0218].value
#define REG2064_VALUE pregv[0][REG2064].value
#define REG2138_VALUE pregv[0][REG2138].value
#define REG54012_VALUE pregv[0][REG54012].value
#define REG5402C_VALUE pregv[0][REG5402C].value

#include "ddrphy_train.c"

void ddr_cfg_phy(void);
static void _ddr_init(void)
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
	reg32_write(0x30360068,0xece580);
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
	reg32_write(0x3d400000,REG0000_VALUE);
	reg32_write(0x3d400028,0x0);
	reg32_write(0x3d400020,0x203);
	reg32_write(0x3d400024,0x186a000);
	reg32_write(0x3d400064,REG0064_VALUE);
	reg32_write(0x3d4000d0,0xc003061c);
	reg32_write(0x3d4000d4,0x9e0000);
	reg32_write(0x3d4000dc,0xd4002d);
	reg32_write(0x3d4000e0,0x310008);
	reg32_write(0x3d4000e8,0x66004a);
	reg32_write(0x3d4000ec,0x16004a);
	reg32_write(0x3d400100,0x1a201b22);
	reg32_write(0x3d400104,0x60633);
	reg32_write(0x3d40010c,0xc0c000);
	reg32_write(0x3d400110,0xf04080f);
	reg32_write(0x3d400114,0x2040c0c);
	reg32_write(0x3d400118,0x1010007);
	reg32_write(0x3d40011c,0x401);
	reg32_write(0x3d400130,0x20600);
	reg32_write(0x3d400134,0xc100002);
	reg32_write(0x3d400138,REG0138_VALUE);
	reg32_write(0x3d400144,0xa00050);
	reg32_write(0x3d400180,0x3200018);
	reg32_write(0x3d400184,0x28061a8);
	reg32_write(0x3d400188,0x0);
	reg32_write(0x3d400190,0x497820a);
	reg32_write(0x3d400194,0x80303);
	reg32_write(0x3d4001a0,0xe0400018);
	reg32_write(0x3d4001a4,0xdf00e4);
	reg32_write(0x3d4001a8,0x80000000);
	reg32_write(0x3d4001b0,0x11);
	reg32_write(0x3d4001b4,0x170a);
	reg32_write(0x3d4001c0,0x1);
	reg32_write(0x3d4001c4,0x1);
	reg32_write(0x3d4000f4,0x639);
	reg32_write(0x3d400108,0x70e1214);
	reg32_write(0x3d400200,REG0200_VALUE);
	reg32_write(0x3d40020c,0x0);
	reg32_write(0x3d400210,0x1f1f);
	reg32_write(0x3d400204,0x80808);
	reg32_write(0x3d400214,0x7070707);
	reg32_write(0x3d400218,REG0218_VALUE);
	reg32_write(0x3d402020,0x1);
	reg32_write(0x3d402024,0x518b00);
	reg32_write(0x3d402050,0x20d040);
	reg32_write(0x3d402064,REG2064_VALUE);
	reg32_write(0x3d4020dc,0x940009);
	reg32_write(0x3d4020e0,0x310000);
	reg32_write(0x3d4020e8,0x66004a);
	reg32_write(0x3d4020ec,0x16004a);
	reg32_write(0x3d402100,0xb070508);
	reg32_write(0x3d402104,0x3040b);
	reg32_write(0x3d402108,0x305090c);
	reg32_write(0x3d40210c,0x505000);
	reg32_write(0x3d402110,0x4040204);
	reg32_write(0x3d402114,0x2030303);
	reg32_write(0x3d402118,0x1010004);
	reg32_write(0x3d40211c,0x301);
	reg32_write(0x3d402130,0x20300);
	reg32_write(0x3d402134,0xa100002);
	reg32_write(0x3d402138,REG2138_VALUE);
	reg32_write(0x3d402144,0x220011);
	reg32_write(0x3d402180,0xa70006);
	reg32_write(0x3d402190,0x3858202);
	reg32_write(0x3d402194,0x80303);
	reg32_write(0x3d4021b4,0x502);
	reg32_write(0x3d400244,0x0);
	reg32_write(0x3d400250,0x29001505);
	reg32_write(0x3d400254,0x2c);
	reg32_write(0x3d40025c,0x5900575b);
	reg32_write(0x3d400264,0x9);
	reg32_write(0x3d40026c,0x2005574);
	reg32_write(0x3d400300,0x16);
	reg32_write(0x3d400304,0x0);
	reg32_write(0x3d40030c,0x0);
	reg32_write(0x3d400320,0x1);
	reg32_write(0x3d40036c,0x11);
	reg32_write(0x3d400400,0x111);
	reg32_write(0x3d400404,0x10f3);
	reg32_write(0x3d400408,0x72ff);
	reg32_write(0x3d400490,0x1);
	reg32_write(0x3d400494,0x1110d00);
	reg32_write(0x3d400498,0x620790);
	reg32_write(0x3d40049c,0x100001);
	reg32_write(0x3d4004a0,0x41f);
	reg32_write(0x30391000,0x8f000004);
	reg32_write(0x30391000,0x8f000000);
	reg32_write(0x3d400030,0xa8);
	do{
		tmp=reg32_read(0x3d400004);
		if(tmp&0x223) break;
	}while(1);
	reg32_write(0x3d400320,0x0);
	reg32_write(0x3d000000,0x1);
	reg32_write(0x3d4001b0,0x10);
	reg32_write(0x3c040280,0x0);
	reg32_write(0x3c040284,0x1);
	reg32_write(0x3c040288,0x2);
	reg32_write(0x3c04028c,0x3);
	reg32_write(0x3c040290,0x4);
	reg32_write(0x3c040294,0x5);
	reg32_write(0x3c040298,0x6);
	reg32_write(0x3c04029c,0x7);
	reg32_write(0x3c044280,0x2);
	reg32_write(0x3c044284,0x6);
	reg32_write(0x3c044288,0x4);
	reg32_write(0x3c04428c,0x7);
	reg32_write(0x3c044290,0x5);
	reg32_write(0x3c044294,0x3);
	reg32_write(0x3c044298,0x0);
	reg32_write(0x3c04429c,0x1);
	reg32_write(0x3c048280,0x0);
	reg32_write(0x3c048284,0x1);
	reg32_write(0x3c048288,0x2);
	reg32_write(0x3c04828c,0x3);
	reg32_write(0x3c048290,0x4);
	reg32_write(0x3c048294,0x5);
	reg32_write(0x3c048298,0x6);
	reg32_write(0x3c04829c,0x7);
	reg32_write(0x3c04c280,0x1);
	reg32_write(0x3c04c284,0x3);
	reg32_write(0x3c04c288,0x4);
	reg32_write(0x3c04c28c,0x7);
	reg32_write(0x3c04c290,0x6);
	reg32_write(0x3c04c294,0x5);
	reg32_write(0x3c04c298,0x0);
	reg32_write(0x3c04c29c,0x2);

	/* Configure DDR PHY's registers */
	ddr_cfg_phy();

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
	/* enable DDR auto-refresh mode */
	tmp = reg32_read(DDRC_RFSHCTL3(0)) & ~0x1;
	reg32_write(DDRC_RFSHCTL3(0), tmp);
}

static void ddr_phy_reset(void) 
{
    volatile unsigned int reg_value;
    printf("DDR Phy reset\n");
    /* Assert */
    reg_value = reg32_read(0x30391000) | 0xF;
    reg32_write(0x30391000, reg_value);
    reg_value = reg32_read(0x30391004) | 0xF;
    reg32_write(0x30391004, reg_value);
    mdelay(100);
    /* De-Assert */
    reg_value = reg32_read(0x30391000) & ~0xF;
    reg32_write(0x30391000, reg_value);
    reg_value = reg32_read(0x30391004) & ~0xF;
    reg32_write(0x30391004, reg_value);
    mdelay(100);
}

void ddr_init()
{
    size_t i, n = sizeof(pregv) / sizeof(pregv[0]);
    unsigned int result;
    phys_size_t _sdram_size;
    /* Start from #1; #0 is for defaults */
    for (i=1 ; i < n ; i++) {
        pregv[0] = pregv[i];
        _ddr_init();
        result = get_ddrphy_training_result();
        if (result) {
            printf("Warning [%zu/%zu] : ddr init failed\n", i , n-1);
        } else {
            printf("Success [%zu/%zu] : ddr init passed\n", i , n-1);
            _sdram_size = get_ram_size((long int *)PHYS_SDRAM, sdram_size[i]);
            printf("Mem discovery %zx / %zx \n",_sdram_size, sdram_size[i]);
            if (_sdram_size == sdram_size[i]) {
                return;
            }
        }
        ddr_phy_reset();
    }
    return;
}
