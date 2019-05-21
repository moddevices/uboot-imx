/*
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CL_SOM_IMX8_H
#define __CL_SOM_IMX8_H

#include <linux/sizes.h>
#include <asm/arch/imx-regs.h>
#include "imx_env.h"

#ifdef CONFIG_SECURE_BOOT
#define CONFIG_CSF_SIZE			0x2000 /* 8K region */
#endif

#define CONFIG_SPL_TEXT_BASE		0x7E1000
#define CONFIG_SPL_MAX_SIZE		(148 * 1024)
#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_USE_SECTOR
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION	1

#ifdef CONFIG_SPL_BUILD
/*#define CONFIG_ENABLE_DDR_TRAINING_DEBUG*/
#define CONFIG_SPL_WATCHDOG_SUPPORT
#define CONFIG_SPL_DRIVERS_MISC_SUPPORT
#define CONFIG_SPL_POWER_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT
#define CONFIG_SPL_LDSCRIPT		"arch/arm/cpu/armv8/u-boot-spl.lds"
#define CONFIG_SPL_STACK		0x187FF0
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_GPIO_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SPL_BSS_START_ADDR      0x00180000
#define CONFIG_SPL_BSS_MAX_SIZE        0x2000	/* 8 KB */
#define CONFIG_SYS_SPL_MALLOC_START    0x42200000
#define CONFIG_SYS_SPL_MALLOC_SIZE    0x80000	/* 512 KB */
#define CONFIG_SYS_SPL_PTE_RAM_BASE    0x41580000
#define CONFIG_SYS_ICACHE_OFF
#define CONFIG_SYS_DCACHE_OFF

#define CONFIG_MALLOC_F_ADDR		0x182000 /* malloc f used before GD_FLG_FULL_MALLOC_INIT set */

#define CONFIG_SPL_ABORT_ON_RAW_IMAGE /* For RAW image gives a error info not panic */

#undef CONFIG_DM_MMC
#undef CONFIG_DM_PMIC
#undef CONFIG_DM_PMIC_PFUZE100

#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR 0x08
#endif

#define CONFIG_REMAKE_ELF

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_POSTCLK_INIT
#define CONFIG_BOARD_LATE_INIT

/* Flat Device Tree Definitions */
#define CONFIG_OF_BOARD_SETUP

#undef CONFIG_CMD_IMLS

#undef CONFIG_CMD_CRC32
#undef CONFIG_BOOTM_NETBSD

/* ENET Config */
/* ENET1 */
#if defined(CONFIG_CMD_NET)
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_MII
#define CONFIG_ETHPRIME                 "FEC"

#define CONFIG_FEC_MXC
#define CONFIG_FEC_XCV_TYPE             RGMII
#define CONFIG_FEC_MXC_PHYADDR          0
#define FEC_QUIRK_ENET_MAC

#define CONFIG_PHY_GIGE
#define IMX_FEC_BASE			0x30BE0000

#define CONFIG_PHYLIB
#define CONFIG_PHY_ATHEROS
#endif

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS  \
	"bootdelay=1\0"                                           \
	"bootcmd=run boot_main; run boot_restore; run boot_usb\0" \
	"console=ttymxc2,115200\0"                                \
	"fdt_addr=0x43000000\0"                                   \
	"fdt_high=0xffffffffffffffff\0"                           \
	"fdt_file=/modduox-cl-imx8mq.dtb\0"                       \
	"initrd_addr=0x43800000\0"                                \
	"initrd_high=0xffffffffffffffff\0"                        \
	"bootenv_file=/uEnv.txt\0"                                \
	"kernel=/Image-cl-imx8mq\0"                               \
	"autoload=off\0"                                          \
	"mmcautodetect=yes\0"                                     \
	"root=/dev/mmcblk0p2\0"                                   \
	"boot_image=booti ${loadaddr} - ${fdt_addr}\0"            \
	"main_bootargs=setenv bootargs console=${console} root=${root} loglevel=${loglevel} ${extraargs}\0"                  \
	"main_loadbootenv=ext4load mmc 0:2 ${loadaddr} /boot${bootenv_file} && env import ${loadaddr} ${filesize}\0"         \
	"main_fdt=ext4load mmc 0:2 ${fdt_addr} /boot${fdt_file}\0"                                                           \
	"main_kernel=ext4load mmc 0:2 ${loadaddr} /boot${kernel}\0"                                                          \
	"boot_main=run main_loadbootenv main_bootargs main_fdt main_kernel boot_image\0"                                     \
	"restore_bootargs=setenv bootargs console=${console} loglevel=${loglevel} ${extraargs}\0"                            \
	"restore_loadbootenv=fatload mmc 0:1 ${loadaddr} ${bootenv_file} && env import ${loadaddr} ${filesize}\0"            \
	"restore_fdt=fatload mmc 0:1 ${fdt_addr} ${fdt_file}\0"                                                              \
	"restore_kernel=fatload mmc 0:1 ${loadaddr} ${kernel}\0"                                                             \
	"boot_restore=run restore_loadbootenv restore_bootargs restore_fdt restore_kernel boot_image\0"                      \
	"usb_bootargs=setenv bootargs console=${console} loglevel=${loglevel} ${extraargs}\0"                                \
	"usb_loadbootenv=load usb 0 ${loadaddr} ${bootenv_file} && env import ${loadaddr} ${filesize}\0"                     \
	"usb_fdt=load usb 0 ${fdt_addr} ${fdt_file}\0"                                                                       \
	"usb_kernel=load usb 0 ${loadaddr} ${kernel}\0"                                                                      \
	"boot_usb=usb start; run usb_loadbootenv usb_bootargs usb_bootargs usb_fdt usb_kernel boot_image\0"                  \
	"boot_fastboot=fastboot\0"                                                                                           \
	"loadbootenv=echo\0"

#define CONFIG_BOOTCOMMAND \
	   "mmc dev ${mmcdev}; if mmc rescan; then " \
		   "if run loadbootscript; then " \
			   "run bootscript; " \
		   "else " \
			   "if run loadimage; then " \
				   "run mmcboot; " \
			   "else booti ${loadaddr} - ${fdt_addr}; " \
			   "fi; " \
		   "fi; " \
	   "else booti ${loadaddr} - ${fdt_addr}; fi"

/* Link Definitions */
#define CONFIG_LOADADDR			0x40480000

#define CONFIG_SYS_LOAD_ADDR           CONFIG_LOADADDR

#define CONFIG_SYS_INIT_RAM_ADDR        0x40000000
#define CONFIG_SYS_INIT_RAM_SIZE        0x80000
#define CONFIG_SYS_INIT_SP_OFFSET \
        (CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
        (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

#define CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_OFFSET               (64 * SZ_64K)
#define CONFIG_ENV_SIZE			0x1000
#define CONFIG_SYS_MMC_ENV_DEV		0   /* USDHC1/eMMC */
#define CONFIG_MMCROOT			"/dev/mmcblk0p2"  /* USDHC1 */

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		((CONFIG_ENV_SIZE + (2*1024) + (16*1024)) * 1024)

#define CONFIG_SYS_SDRAM_BASE           0x40000000
#define PHYS_SDRAM                      0x40000000
#define PHYS_SDRAM_SIZE			0x80000000 /* 2GB DDR */
#define CONFIG_NR_DRAM_BANKS		1

#define CONFIG_SYS_MEMTEST_START    PHYS_SDRAM
#define CONFIG_SYS_MEMTEST_END      (CONFIG_SYS_MEMTEST_START + (PHYS_SDRAM_SIZE >> 1))

#define CONFIG_BAUDRATE			115200

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART3_BASE_ADDR

/* Monitor Command Prompt */
#undef CONFIG_SYS_PROMPT
#define CONFIG_SYS_PROMPT		"u-boot=> "
#define CONFIG_SYS_PROMPT_HUSH_PS2     "> "
#define CONFIG_SYS_CBSIZE              2048
#define CONFIG_SYS_MAXARGS             64
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

#define CONFIG_IMX_BOOTAUX

#define CONFIG_CMD_MMC
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC

#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_SYS_FSL_ESDHC_ADDR       0

#define CONFIG_SUPPORT_EMMC_BOOT	/* eMMC specific */
#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_MXC_GPIO

#define CONFIG_MXC_OCOTP
#define CONFIG_CMD_FUSE

/* I2C Configs */
#define CONFIG_SYS_I2C_SPEED		  100000

/* USB configs */
#ifndef CONFIG_SPL_BUILD

#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE

#define CONFIG_CMD_USB_MASS_STORAGE
#define CONFIG_USB_GADGET_MASS_STORAGE
#define CONFIG_USB_FUNCTION_MASS_STORAGE

#define CONFIG_CMD_READ

#endif

#define CONFIG_OF_SYSTEM_SETUP

/* Framebuffer */
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_IMXDCSS
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_IMX_VIDEO_SKIP
#endif

#if defined(CONFIG_ANDROID_SUPPORT)
#include "cl-som-imx8_android.h"
#endif

#endif
