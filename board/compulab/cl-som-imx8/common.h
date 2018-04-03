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

#endif /* __CL_SOM_IMX8_COMMON_H__ */
