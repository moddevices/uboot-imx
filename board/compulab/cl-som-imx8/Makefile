#
# Copyright 2017 CompuLab LTD.
#
# SPDX-License-Identifier:      GPL-2.0+
#
obj-y += common.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o ddr/ddr_init.o ddr/helper.o
else
obj-y += cl-som-imx8.o eeprom.o
endif
