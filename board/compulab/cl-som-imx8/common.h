#ifndef __CL_SOM_IMX8_COMMON_H__
#define __CL_SOM_IMX8_COMMON_H__

#include <asm/imx-common/iomux-v3.h>

int board_early_init_f(void);

#ifdef CONFIG_MXC_SPI
int board_ecspi_init(void);
int board_spi_cs_gpio(unsigned bus, unsigned cs);
#else
static inline int board_ecspi_init(void) { return 0; }
#endif

#define I2C_PAD_CTRL	(PAD_CTL_DSE6 | PAD_CTL_HYS | PAD_CTL_PUE)
#define PC MUX_PAD_CTRL(I2C_PAD_CTRL)

#endif /* __CL_SOM_IMX8_COMMON_H__ */
