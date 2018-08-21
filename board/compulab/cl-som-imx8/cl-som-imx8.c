/*
 * Copyright 2016 Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <malloc.h>
#include <errno.h>
#include <asm/io.h>
#include <miiphy.h>
#include <netdev.h>
#include <asm/imx-common/iomux-v3.h>
#include <asm-generic/gpio.h>
#include <fsl_esdhc.h>
#include <mmc.h>
#include <asm/arch/imx8mq_pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/imx-common/gpio.h>
#include <asm/imx-common/mxc_i2c.h>
#include <asm/arch/clock.h>
#include <spl.h>
#include <power/pmic.h>
#include <power/pfuze100_pmic.h>
#include "common.h"
#include "eeprom.h"

#include "../common/pfuze.h"

#include <usb.h>
#include <dwc3-uboot.h>

DECLARE_GLOBAL_DATA_PTR;

#define WDOG_PAD_CTRL	(PAD_CTL_DSE6 | PAD_CTL_HYS | PAD_CTL_PUE)

static iomux_v3_cfg_t const wdog_pads[] = {
	IMX8MQ_PAD_GPIO1_IO02__WDOG1_WDOG_B | MUX_PAD_CTRL(WDOG_PAD_CTRL),
};

struct i2c_pads_info i2c_pad_info0 = {
	.scl = {
		.i2c_mode = IMX8MQ_PAD_I2C1_SCL__I2C1_SCL | PC,
		.gpio_mode = IMX8MQ_PAD_I2C1_SCL__GPIO5_IO14 | PC,
		.gp = IMX_GPIO_NR(5, 14),
	},
	.sda = {
		.i2c_mode = IMX8MQ_PAD_I2C1_SDA__I2C1_SDA | PC,
		.gpio_mode = IMX8MQ_PAD_I2C1_SDA__GPIO5_IO15 | PC,
		.gp = IMX_GPIO_NR(5, 15),
	},
};

#ifdef CONFIG_BOARD_POSTCLK_INIT
int board_postclk_init(void)
{
	/* TODO */
	return 0;
}
#endif

static phys_size_t imx8_ddr_size(void)
{
    unsigned long mem = 0x3d400000;
	unsigned long value = readl(mem+0x200);
	phys_size_t dram_size;

    switch (value) {
    case 0x1f:
        dram_size = 0x40000000;
        break;
    case 0x16:
        dram_size = 0x80000000;
        break;
    case 0x17:
        /* dram_size = 0x100000000;*/
        /* reports 3G only, if reports above then gets crashed */
        dram_size = 0xc0000000;
        break;
    default:
        break;
    };
    return dram_size;
}

int dram_init(void)
{
    gd->ram_size = imx8_ddr_size();
    return 0;
}

void dram_init_banksize(void)
{
    gd->bd->bi_dram[0].start = PHYS_SDRAM;
    gd->bd->bi_dram[0].size = imx8_ddr_size();
}

phys_size_t get_effective_memsize(void)
{
    phys_size_t dram_size = imx8_ddr_size();
    if (dram_size > 0xc0000000)
        return 0xc0000000;

    return dram_size;
}

#ifdef CONFIG_OF_BOARD_SETUP
int ft_board_setup(void *blob, bd_t *bd)
{
	return 0;
}
#endif

#ifdef CONFIG_FEC_MXC
#define FEC_RST_PAD IMX_GPIO_NR(1, 9)
static iomux_v3_cfg_t const fec1_rst_pads[] = {
	IMX8MQ_PAD_GPIO1_IO09__GPIO1_IO9 | MUX_PAD_CTRL(NO_PAD_CTRL),
};

static void setup_iomux_fec(void)
{
	imx_iomux_v3_setup_multiple_pads(fec1_rst_pads, ARRAY_SIZE(fec1_rst_pads));

	gpio_request(IMX_GPIO_NR(1, 9), "fec1_rst");
	gpio_direction_output(IMX_GPIO_NR(1, 9), 0);
	udelay(500);
	gpio_direction_output(IMX_GPIO_NR(1, 9), 1);
}

#define NO_MAC_ADDR	"No MAC address found for %s\n"
static int handle_mac_address(char *env_var, uint eeprom_bus)
{
	unsigned char enetaddr[6];
	int rc;

	rc = eth_getenv_enetaddr(env_var, enetaddr);
	if (rc)
		return 0;

	rc = cpl_eeprom_read_mac_addr(enetaddr, eeprom_bus);
	if (rc)
		return rc;

	if (!is_valid_ethaddr(enetaddr))
		return -1;

	return eth_setenv_enetaddr(env_var, enetaddr);
}

static inline void setup_mac_address()
{
	if (handle_mac_address("ethaddr", 0))
		printf(NO_MAC_ADDR, "primary NIC");
}

static int setup_fec(void)
{
	setup_iomux_fec();

	/* Use 125M anatop REF_CLK1 for ENET1, not from external */
	clrsetbits_le32(IOMUXC_GPR1,
			BIT(13) | BIT(17), 0);
	return set_clk_enet(ENET_125MHz);
}

static void setup_fec_mac() {
	if (handle_mac_address("ethaddr", /*CONFIG_SYS_I2C_EEPROM_BUS*/0))
		printf(NO_MAC_ADDR, "primary NIC");
}

int board_phy_config(struct phy_device *phydev)
{
	/* enable rgmii rxc skew and phy mode select to RGMII copper */
	phy_write(phydev, MDIO_DEVAD_NONE, 0x1d, 0x1f);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x1e, 0x8);

	phy_write(phydev, MDIO_DEVAD_NONE, 0x1d, 0x05);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x1e, 0x100);

	if (phydev->drv->config)
		phydev->drv->config(phydev);

	setup_mac_address();

	return 0;
}
#endif

#ifdef CONFIG_USB_DWC3

#define USB_PHY_CTRL0			0xF0040
#define USB_PHY_CTRL0_REF_SSP_EN	BIT(2)

#define USB_PHY_CTRL1			0xF0044
#define USB_PHY_CTRL1_RESET		BIT(0)
#define USB_PHY_CTRL1_COMMONONN		BIT(1)
#define USB_PHY_CTRL1_ATERESET		BIT(3)
#define USB_PHY_CTRL1_VDATSRCENB0	BIT(19)
#define USB_PHY_CTRL1_VDATDETENB0	BIT(20)

#define USB_PHY_CTRL2			0xF0048
#define USB_PHY_CTRL2_TXENABLEN0	BIT(8)

static struct dwc3_device dwc3_device_data = {
	.maximum_speed = USB_SPEED_SUPER,
	.base = USB1_BASE_ADDR,
	.dr_mode = USB_DR_MODE_HOST,
	.index = 0,
	.power_down_scale = 2,
};

int usb_gadget_handle_interrupts(void)
{
	dwc3_uboot_handle_interrupt(0);
	return 0;
}

static void dwc3_nxp_usb_phy_init(struct dwc3_device *dwc3)
{
	u32 RegData;

	RegData = readl(dwc3->base + USB_PHY_CTRL1);
	RegData &= ~(USB_PHY_CTRL1_VDATSRCENB0 | USB_PHY_CTRL1_VDATDETENB0 |
			USB_PHY_CTRL1_COMMONONN);
	RegData |= USB_PHY_CTRL1_RESET | USB_PHY_CTRL1_ATERESET;
	writel(RegData, dwc3->base + USB_PHY_CTRL1);

	RegData = readl(dwc3->base + USB_PHY_CTRL0);
	RegData |= USB_PHY_CTRL0_REF_SSP_EN;
	writel(RegData, dwc3->base + USB_PHY_CTRL0);

	RegData = readl(dwc3->base + USB_PHY_CTRL2);
	RegData |= USB_PHY_CTRL2_TXENABLEN0;
	writel(RegData, dwc3->base + USB_PHY_CTRL2);

	RegData = readl(dwc3->base + USB_PHY_CTRL1);
	RegData &= ~(USB_PHY_CTRL1_RESET | USB_PHY_CTRL1_ATERESET);
	writel(RegData, dwc3->base + USB_PHY_CTRL1);
}

int board_usb_init(int index, enum usb_init_type init)
{
	dwc3_nxp_usb_phy_init(&dwc3_device_data);
	return dwc3_uboot_init(&dwc3_device_data);
}

int board_usb_cleanup(int index, enum usb_init_type init)
{
	dwc3_uboot_exit(index);
	return 0;
}
#endif

int board_init(void)
{

#ifdef CONFIG_MXC_SPI
	board_ecspi_init();
#endif

#ifdef CONFIG_FEC_MXC
	setup_fec();
#endif
	/* Configure #0 bus in order to read an #0x54 eeprom */
	setup_i2c(0, CONFIG_SYS_I2C_SPEED, 0x7f, &i2c_pad_info0);

	return 0;
}

int board_mmc_get_env_dev(int devno)
{
	const char *s = getenv("atp");
	if (s != NULL) {
		printf("ATP Mode: Save environmet on eMMC\n");
		return CONFIG_SYS_MMC_ENV_DEV;
	}
	return devno;
}

int board_late_init(void)
{

#ifdef CONFIG_ENV_IS_IN_MMC
	board_late_mmc_env_init();
#endif

	return 0;
}

static iomux_v3_cfg_t const board_rst_pads[] = {
	IMX8MQ_PAD_NAND_RE_B__GPIO3_IO15 | MUX_PAD_CTRL(NO_PAD_CTRL),
};

static void board_reset(void)
{
	imx_iomux_v3_setup_multiple_pads(board_rst_pads, ARRAY_SIZE(board_rst_pads));
	gpio_request(IMX_GPIO_NR(3, 15), "board_reset");
	gpio_direction_output(IMX_GPIO_NR(3, 15), 0);

	while (1)
		;
}

void reset_misc() { board_reset(); }

#ifdef CONFIG_FSL_FASTBOOT
#ifdef CONFIG_ANDROID_RECOVERY
int is_recovery_key_pressing(void)
{
	return 0; /*TODO*/
}
#endif /*CONFIG_ANDROID_RECOVERY*/
#endif /*CONFIG_FSL_FASTBOOT*/
