/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef __DTS_S32V234_PINFUNC_H
#define __DTS_S32V234_PINFUNC_H

/*
 * The pin function ID for S32V234 is a tuple of:
 * <mux_reg input_reg mux_mode input_val>
 * mux_reg - MSCRn offset
 * input_reg - IMCR or GPDO offset
 * mux_mode - MUX_MODE value from MSCR register
 * input_val - specifies the direction of the PIN
 */

#define ALT0	0x0
#define ALT1	0x1
#define ALT2	0x2
#define ALT3	0x3
#define ALT4	0x4
#define ALT5	0x5
#define ALT6	0x6
#define ALT7	0x7


#define S32V234_PAD_PA0__GPIO_0				0x000 0x000 ALT0 0x0
#define S32V234_PAD_PA0__EIRQ_0				0x24E 0x04E ALT2 0x0

#define S32V234_PAD_PA1__GPIO_1				0x001 0x001 ALT0 0x0
#define S32V234_PAD_PA1__EIRQ_1				0x24F 0x04F ALT2 0x0

#define S32V234_PAD_PA2__GPIO_2				0x002 0x002 ALT0 0x0
#define S32V234_PAD_PA2__CAN_FD0_TXD		0x002 0x002 ALT1 0x1
#define S32V234_PAD_PA2__EIRQ_2				0x250 0x050 ALT2 0x0

#define S32V234_PAD_PA3__GPIO_3				0x000 0x003 ALT0 0x0
#define S32V234_PAD_PA3__EIRQ_3				0x251 0x051 ALT2 0x0
#define S32V234_PAD_PA3__CAN_FD0_RXD		0x2BC 0x0BC ALT2 0x0
#define S32V234_PAD_PA3__CAN_FD1_RXD		0x2BD 0x0BD ALT2 0x0

#define S32V234_PAD_PA4__GPIO_4				0x004 0x004 ALT0 0x0
#define S32V234_PAD_PA4__CAN_FD1_TXD		0x004 0x004 ALT1 0x1
#define S32V234_PAD_PA4__FLEXRAY_TXD_B		0x004 0x004 ALT2 0x1
#define S32V234_PAD_PA4__EIRQ_4				0x252 0x052 ALT2 0x0

#define S32V234_PAD_PA5__GPIO_5				0x005 0x005 ALT0 0x0
#define S32V234_PAD_PA5__EIRQ_5				0x253 0x053 ALT2 0x0
#define S32V234_PAD_PA5__CAN_FD0_RXD		0x2BC 0x0BC ALT3 0x0
#define S32V234_PAD_PA5__CAN_FD1_RXD		0x2BD 0x0BD ALT3 0x0

#define S32V234_PAD_PA6__GPIO_6				0x006 0x006 ALT0 0x0
#define S32V234_PAD_PA6__FLEXRAY_TXEN_A		0x006 0x006 ALT1 0x1
#define S32V234_PAD_PA6__SPI1_CS2			0x006 0x006 ALT2 0x1
#define S32V234_PAD_PA6__DDR0_DEBUG43		0x006 0x006 ALT3 0x1
#define S32V234_PAD_PA6__DDR1_DEBUG43		0x006 0x006 ALT4 0x1
#define S32V234_PAD_PA5__EIRQ_6				0x254 0x054 ALT2 0x0

#define S32V234_PAD_PA7__GPIO_7				0x007 0x007 ALT0 0x0
#define S32V234_PAD_PA7__FLEXRAY_TXEN_B		0x007 0x007 ALT1 0x1
#define S32V234_PAD_PA7__SPI1_CS3			0x007 0x007 ALT2 0x1
#define S32V234_PAD_PA7__DDR0_DEBUG44		0x007 0x007 ALT3 0x1
#define S32V234_PAD_PA7__DDR1_DEBUG44		0x007 0x007 ALT4 0x1
#define S32V234_PAD_PA7__EIRQ_7				0x255 0x055 ALT2 0x0


#define S32V234_PAD_PA8__GPIO_8				0x008 0x008 ALT0 0x0
#define S32V234_PAD_PA8__FLEXRAY_TXD_A		0x008 0x008 ALT1 0x1
#define S32V234_PAD_PA8__SPI0_CS1			0x008 0x008 ALT2 0x1
#define S32V234_PAD_PA8__DDR0_DEBUG45		0x008 0x008 ALT3 0x1
#define S32V234_PAD_PA8__DDR1_DEBUG45		0x008 0x008 ALT4 0x1
#define S32V234_PAD_PA8__EIRQ_8				0x256 0x056 ALT2 0x0


#define S32V234_PAD_PA9__GPIO_9				0x009 0x009 ALT0 0x0
#define S32V234_PAD_PA9__SPI0_CS2			0x009 0x009 ALT1 0x1
#define S32V234_PAD_PA9__DDR0_DEBUG46		0x009 0x009 ALT2 0x1
#define S32V234_PAD_PA9__DDR1_DEBUG46		0x009 0x009 ALT3 0x1
#define S32V234_PAD_PA9__EIRQ_9				0x257 0x057 ALT2 0x0
#define S32V234_PAD_PA9__FLEXRAY_CA_RX		0x3Ff 0x1F4 ALT2 0x0


#define S32V234_PAD_PA10__GPIO_10			0x00A 0x00A ALT0 0x0
#define S32V234_PAD_PA10__ETH_TIMER2_OUT	0x00A 0x00A ALT1 0x1
#define S32V234_PAD_PA10__SPI1_CS2			0x00A 0x00A ALT2 0x1
#define S32V234_PAD_PA10__FLEXTMR0_EXTCLK	0x208 0x008 ALT2 0x0
#define S32V234_PAD_PA10__FLEXTMR1_EXTCLK	0x211 0x011 ALT2 0x0
#define S32V234_PAD_PA10__EIRQ_10			0x258 0x058 ALT2 0x0
#define S32V234_PAD_PA10__ETH_TIMER2_IN		0x3D8 0x1D8 ALT2 0x0

#define S32V234_PAD_PA11__GPIO_11			0x00B 0x00B ALT0 0x0
#define S32V234_PAD_PA11__FLEXTMR_CH2_OUT	0x00B 0x00B ALT1 0x1
#define S32V234_PAD_PA11__DDR0_DEBUG47		0x008 0x00B ALT2 0x1
#define S32V234_PAD_PA11__DDR1_DEBUG47		0x008 0x00B ALT3 0x1
#define S32V234_PAD_PA11__FLEXTMR_CH2_IN	0x20B 0x00B ALT2 0x0
#define S32V234_PAD_PA11__EIRQ_11			0x259 0x059 ALT2 0x0
#define S32V234_PAD_PA11__UART0_RXD			0x2C8 0x0C8 ALT2 0x0


#define S32V234_PAD_PA12__GPIO_12			0x00C 0x00C ALT0 0x0
#define S32V234_PAD_PA12__UART0_TXD			0x00C 0x00C ALT1 0x1
#define S32V234_PAD_PA12__FLEXTMR1_CH3		0x00C 0x00C ALT2 0x1
#define S32V234_PAD_PA12__DDR0_DEBUG48		0x00C 0x00C ALT3 0x1
#define S32V234_PAD_PA12__DDR1_DEBUG48		0x00C 0x00C ALT4 0x1
#define S32V234_PAD_PA12__FLEXTMR1_CH3		0x20C 0x00C ALT2 0x0
#define S32V234_PAD_PA12__EIRQ_12			0x25A 0x05A ALT2 0x0


#define S32V234_PAD_PA13__GPIO_13			0x00D 0x00D ALT0 0x0
#define S32V234_PAD_PA13__FLEXTMR0_CH2		0x00D 0x00D ALT1 0x1
#define S32V234_PAD_PA13__SPI0_CS3			0x00D 0x00D ALT2 0x1
#define S32V234_PAD_PA13__DDR0_DEBUG48		0x00D 0x00D ALT3 0x1
#define S32V234_PAD_PA13__DDR1_DEBUG48		0x00D 0x00D ALT4 0x1
#define S32V234_PAD_PA13__FLEXTMR0_CH2		0x202 0x002 ALT2 0x0
#define S32V234_PAD_PA13__EIRQ_13			0x25B 0x05B ALT2 0x0
#define S32V234_PAD_PA13__UART1_RXD			0x2CA 0x0CA ALT2 0x0

#define S32V234_PAD_PA14__GPIO_14			0x00E 0x00E ALT0 0x0
#define S32V234_PAD_PA14__UART1_TXD			0x00E 0x00E ALT1 0x1
#define S32V234_PAD_PA14__FLEXTMR0_CH3		0x00E 0x00E ALT2 0x1
#define S32V234_PAD_PA14__SPI1_CS1			0x00E 0x00E ALT3 0x1
#define S32V234_PAD_PA14__DDR0_DEBUG50		0x00E 0x00E ALT4 0x1
#define S32V234_PAD_PA14__DDR1_DEBUG50		0x00E 0x00E ALT5 0x1
#define S32V234_PAD_PA12__FLEXTMR0_CH3		0x203 0x003 ALT2 0x0
#define S32V234_PAD_PA12__EIRQ_14			0x25C 0x05C ALT2 0x0

#define S32V234_PAD_PA15__GPIO_15			0x00F 0x00F ALT0 0x0
#define S32V234_PAD_PA15__I2C0_DATA_OUT		0x00F 0x00F ALT1 0x1
#define S32V234_PAD_PA15__EIRQ_15			0x25D 0x05D ALT2 0x0
#define S32V234_PAD_PA15__I2C0_DATA_IN		0x30D 0x10D ALT2 0x0

#define S32V234_PAD_PB0__GPIO_16			0x010 0x010 ALT0 0x0
#define S32V234_PAD_PB0__I2C0_CLK_OUT		0x010 0x010 ALT1 0x1
#define S32V234_PAD_PB0__EIRQ_16			0x25E 0x05E ALT2 0x0
#define S32V234_PAD_PB0__I2C0_CLK_IN		0x30C 0x10C ALT2 0x0

#define S32V234_PAD_PB1__GPIO_17			0x011 0x011 ALT0 0x0
#define S32V234_PAD_PB1__I2C1_DATA_OUT		0x011 0x011 ALT1 0x1
#define S32V234_PAD_PB1__SPI2_CS1			0x011 0x011 ALT2 0x1
#define S32V234_PAD_PB1__EIRQ_17			0x25F 0x05F ALT2 0x0
#define S32V234_PAD_PB1__I2C1_DATA_IN		0x30F 0x10F ALT2 0x0

#define S32V234_PAD_PB2__GPIO_18			0x012 0x012 ALT0 0x0
#define S32V234_PAD_PB2__I2C1_CLK_OUT		0x012 0x012 ALT1 0x1
#define S32V234_PAD_PB2__SPI2_CS2			0x012 0x012 ALT2 0x1
#define S32V234_PAD_PB2__EIRQ_18			0x260 0x060 ALT2 0x0
#define S32V234_PAD_PB2__I2C1_CLK_IN		0x30E 0x10E ALT2 0x0

#define S32V234_PAD_PB3__GPIO_19			0x013 0x013 ALT0 0x0
#define S32V234_PAD_PB3__I2C2_DATA_OUT		0x013 0x013 ALT1 0x1
#define S32V234_PAD_PB3__SPI2_CS2			0x013 0x013 ALT3 0x1
#define S32V234_PAD_PB3__EIRQ_19			0x261 0x061 ALT2 0x0
#define S32V234_PAD_PB3__I2C2_DATA_IN		0x311 0x111 ALT2 0x0

#define S32V234_PAD_PB4__GPIO_20			0x014 0x014 ALT0 0x0
#define S32V234_PAD_PB4__I2C2_CLK_OUT		0x014 0x014 ALT1 0x1
#define S32V234_PAD_PB4__SPI0_CS2			0x014 0x014 ALT2 0x1
#define S32V234_PAD_PB4__FLEXTMR0_EXTCLK	0x208 0x008 ALT2 0x0
#define S32V234_PAD_PB4__FLEXTMR1_EXTCLK	0x211 0x011 ALT2 0x0
#define S32V234_PAD_PB4__EIRQ_20			0x262 0x062 ALT2 0x0
#define S32V234_PAD_PB4__I2C2_CLK_IN		0x310 0x110 ALT2 0x0

#define S32V234_PAD_PB5__GPIO_21			0x015 0x015 ALT0 0x0
#define S32V234_PAD_PB5__SPI0_SCK_OUT		0x015 0x015 ALT1 0x1
#define S32V234_PAD_PB5__EIRQ_21			0x263 0x063 ALT2 0x0
#define S32V234_PAD_PB5__SPI0_SCK_IN		0x321 0x121 ALT2 0x0

#define S32V234_PAD_PB6__GPIO_22			0x016 0x016 ALT0 0x0
#define S32V234_PAD_PB6__SPI0_SOUT			0x016 0x016 ALT1 0x1
#define S32V234_PAD_PB6__EIRQ_22			0x264 0x064 ALT2 0x0

#define S32V234_PAD_PB7__GPIO_23			0x017 0x017 ALT0 0x0
#define S32V234_PAD_PB7__EIRQ_23			0x265 0x065 ALT2 0x0
#define S32V234_PAD_PB7__SPI0_SIN			0x320 0x120 ALT2 0x0

#define S32V234_PAD_PB8__GPIO_24			0x018 0x018 ALT0 0x0
#define S32V234_PAD_PB8__SPI0_CS0_OUT		0x018 0x018 ALT1 0x0
#define S32V234_PAD_PB8__EIRQ_24			0x266 0x066 ALT2 0x0
#define S32V234_PAD_PB8__SPI0_CS0_IN		0x322 0x122 ALT2 0x0

#define S32V234_PAD_PB9__GPIO_25			0x019 0x019 ALT0 0x0
#define S32V234_PAD_PB9__SPI1_SCK_OUT		0x019 0x019 ALT1 0x1
#define S32V234_PAD_PB9__EIRQ_25			0x267 0x067 ALT2 0x0
#define S32V234_PAD_PB9__SPI1_SCK_IN		0x324 0x124 ALT2 0x0


#define S32V234_PAD_PB10__GPIO_26			0x01A 0x01A ALT0 0x0
#define S32V234_PAD_PB10__SPI1_SOUT			0x01A 0x01A ALT1 0x1
#define S32V234_PAD_PB10__EIRQ_26			0x268 0x068 ALT2 0x0

#define S32V234_PAD_PB11__GPIO_27			0x01B 0x01B ALT0 0x0
#define S32V234_PAD_PB11__EIRQ_27			0x269 0x069 ALT2 0x0
#define S32V234_PAD_PB11__SPI1_SIN			0x323 0x123 ALT2 0x0

#define S32V234_PAD_PB12_GPIO_28			0x01C 0x01C ALT0 0x0
#define S32V234_PAD_PB12_SPI1_CS0_OUT		0x01C 0x01C ALT1 0x0
#define S32V234_PAD_PB12_EIRQ_28			0x26A 0x06A ALT2 0x0
#define S32V234_PAD_PB12_SPI1_CS0_IN		0x325 0x125 ALT2 0x0

#define S32V234_PAD_PB13__GPIO_29			0x01D 0x01D ALT0 0x0
#define S32V234_PAD_PB13__SPI2_SCK_OUT		0x01D 0x01D ALT1 0x1
#define S32V234_PAD_PB13__FLEXTMR1_CH2		0x01D 0x01D ALT2 0x1
#define S32V234_PAD_PB13__SPI0_CS1			0x01D 0x01D ALT3 0x1
#define S32V234_PAD_PB13__EIRQ_29			0x26B 0x06B ALT2 0x0
#define S32V234_PAD_PB13__SPI2_SCK_IN		0x327 0x127 ALT2 0x0

#define S32V234_PAD_PB14__GPIO_30			0x01E 0x01E ALT0 0x0
#define S32V234_PAD_PB14__SPI2_SOUT			0x01E 0x01E ALT1 0x1
#define S32V234_PAD_PB14__FLEXTMR1_CH3		0x01E 0x01E ALT2 0x1
#define S32V234_PAD_PB14__SPI0_CS2			0x01E 0x01E ALT3 0x1
#define S32V234_PAD_PB14__EIRQ_30			0x26C 0x06C ALT2 0x0

#define S32V234_PAD_PB15__GPIO_31			0x01F 0x01F ALT0 0x0
#define S32V234_PAD_PB15__FLEXTMR1_CH4_OUT	0x01F 0x01F ALT1 0x1
#define S32V234_PAD_PB15__SPI0_CS3			0x01F 0x01F ALT2 0x1
#define S32V234_PAD_PB15__FLEXTMR1_CH4_IN	0x20D 0x00D ALT2 0x0
#define S32V234_PAD_PB15__EIRQ_31			0x26D 0x06D ALT2 0x0
#define S32V234_PAD_PB15__SPI2_SIN			0x326 0x126 ALT2 0x0

#define S32V234_PAD_PC0__GPIO_32			0x020 0x020 ALT0 0x0
#define S32V234_PAD_PC0__SPI2_CS0_OUT		0x020 0x020 ALT1 0x1
#define S32V234_PAD_PC0__FLEXTMR1_CH5_OUT	0x00F 0x020 ALT2 0x1
#define S32V234_PAD_PC0__FLEXTMR1_CH5_IN	0x20E 0x00E ALT2 0x0
#define S32V234_PAD_PC0__SPI2_CS0_IN		0x328 0x128 ALT2 0x0

#define S32V234_PAD_PC1__GPIO_33			0x021 0x021 ALT0 0x0
#define S32V234_PAD_PC1__SPI3_SCK_OUT		0x021 0x021 ALT1 0x1
#define S32V234_PAD_PC1__FLEXRAY_DEBUG0		0x021 0x021 ALT2 0x1
#define S32V234_PAD_PC1__SPI0_CS5_OUT		0x021 0x021 ALT3 0x1
#define S32V234_PAD_PC1__FLEXTMR0_CH2_OUT	0x021 0x021 ALT4 0x1
#define S32V234_PAD_PC1__FLEXTMR0_CH2_IN	0x202 0x002 ALT3 0x0
#define S32V234_PAD_PC1__SPI3_SCK_OUT		0x32A 0x12A ALT2 0x0

#define S32V234_PAD_PC2__GPIO_34			0x022 0x022 ALT0 0x0
#define S32V234_PAD_PC2__SPI3_SOUT			0x022 0x022 ALT1 0x1
#define S32V234_PAD_PC2__FLEXRAY_DEBU10		0x022 0x022 ALT2 0x1
#define S32V234_PAD_PC2__SPI0_CS6_OUT		0x022 0x022 ALT3 0x1
#define S32V234_PAD_PC2__FLEXTMR0_CH3_OUT	0x022 0x022 ALT4 0x1
#define S32V234_PAD_PC2__FLEXTMR0_CH3_IN	0x203 0x003 ALT2 0x0

#define S32V234_PAD_PC3__GPIO_35			0x023 0x023 ALT0 0x0
#define S32V234_PAD_PC3__FLEXRAY_DEBUG2		0x023 0x023 ALT1 0x1
#define S32V234_PAD_PC3__SPI0_CS7			0x023 0x023 ALT2 0x1
#define S32V234_PAD_PC3__FLEXTMR0_CH4_OUT	0x023 0x023 ALT3 0x1
#define S32V234_PAD_PC3__FLEXTMR0_CH4_IN	0x204 0x004 ALT2 0x0
#define S32V234_PAD_PC3__SPI3_SIN			0x329 0x129 ALT2 0x0

#define S32V234_PAD_PC4__GPIO_36			0x024 0x024 ALT0 0x0
#define S32V234_PAD_PC4__SPI3_CS0			0x024 0x024 ALT1 0x1
#define S32V234_PAD_PC4__FLEXRAY_DEBUG3		0x024 0x024 ALT2 0x1
#define S32V234_PAD_PC4__SPI1_CS1			0x024 0x024 ALT3 0x1
#define S32V234_PAD_PC4__FLEXTMR0_CH5_OUT	0x024 0x024 ALT3 0x1
#define S32V234_PAD_PC4__FLEXTMR0_CH5_IN	0x205 0x005 ALT2 0x0
#define S32V234_PAD_PC4__SPI3_CS0			0x32B 0x12B ALT2 0x0

#define S32V234_PAD_PC5__GPIO_37			0x025 0x025 ALT0 0x0
#define S32V234_PAD_PC5__FLEXTMR0_CH0_OUT	0x025 0x025 ALT1 0x1
#define S32V234_PAD_PC5__SSE_OUT0			0x025 0x025 ALT2 0x1
#define S32V234_PAD_PC5__SPI1_CS2			0x025 0x025 ALT3 0x1
#define S32V234_PAD_PC5__FLEXTMR0_CH0_IN	0x200 0x000 ALT2 0x0

#define S32V234_PAD_PC6__GPIO_38			0x026 0x026 ALT0 0x0
#define S32V234_PAD_PC6__FLEXTMR0_CH1_OUT	0x026 0x026 ALT1 0x1
#define S32V234_PAD_PC6__SSE_OUT1			0x026 0x026 ALT2 0x1
#define S32V234_PAD_PC6__SPI1_CS3			0x026 0x026 ALT3 0x1
#define S32V234_PAD_PC6__FLEXTMR0_CH1_IN	0x201 0x001 ALT2 0x0

#define S32V234_PAD_PC7__GPIO_39			0x027 0x027 ALT0 0x0
#define S32V234_PAD_PC7__FLEXTMR0_CH2_OUT	0x027 0x027 ALT1 0x1
#define S32V234_PAD_PC7__MC_CGL_CLKOUT		0x027 0x027 ALT2 0x1
#define S32V234_PAD_PC7__FLEXTMR0_CH2_IN	0x202 0x002 ALT2 0x0
#define S32V234_PAD_PC7__SSE_IN2			0x3FC 0x1FC ALT2 0x0

#define S32V234_PAD_PC8__GPIO_40			0x028 0x028 ALT0 0x0
#define S32V234_PAD_PC8__FLEXTMR0_CH3_OUT	0x028 0x028 ALT1 0x1
#define S32V234_PAD_PC8__LFAST_REF_CLK		0x028 0x028 ALT2 0x1
#define S32V234_PAD_PC8__LFAST_REF_CLK		0x226 0x026 ALT2 0x0
#define S32V234_PAD_PC8__SSE_IN3			0x3FD 0x1FD ALT2 0x0

#define S32V234_PAD_PC9__GPIO_41			0x029 0x029 ALT0 0x0
#define S32V234_PAD_PC9__FLEXTMR1_CH0_OUT	0x029 0x029 ALT1 0x1
#define S32V234_PAD_PC9__ETH_TIMERO_OUT		0x029 0x029 ALT2 0x0
#define S32V234_PAD_PC9__FLEXTMR1_CH0_IN	0x209 0x009 ALT2 0x0
#define S32V234_PAD_PC9__BOOT_BOOTMOD_0		0x23A 0x03A ALT0 0x0
#define S32V234_PAD_PC9__ETH_TIMERO			0x3D6 0x1D6 ALT2 0x0
#define S32V234_PAD_PC9__SSE_IN0			0x3FA 0x1FA ALT2 0x0

#define S32V234_PAD_PC10__GPIO_42			0x02A 0x02A ALT0 0x0
#define S32V234_PAD_PC10__FLEXTMR1_CH1_OUT	0x02A 0x02A ALT1 0x1
#define S32V234_PAD_PC10__ETH_TIMER1_OUT	0x02A 0x02A ALT2 0x0
#define S32V234_PAD_PC10__FLEXTMR1_CH1_IN	0x20A 0x00A ALT2 0x0
#define S32V234_PAD_PC10__BOOT_BOOTMOD_1	0x23A 0x03A ALT0 0x0
#define S32V234_PAD_PC10__ETH_TIMER1		0x3D7 0x1D7 ALT2 0x0
#define S32V234_PAD_PC10__SSE_IN1			0x3FB 0x1FB ALT2 0x0

#define S32V234_PAD_PC11__GPIO_43			0x02B 0x02B ALT0 0x0
#define S32V234_PAD_PC11__ETH_COL			0x3CB 0x1CB ALT2 0x0

#define S32V234_PAD_PC12__GPIO_44			0x02C 0x02C ALT0 0x0
#define S32V234_PAD_PC12__ETH_CRS			0x3CC 0x1CC ALT2 0x0

#define S32V234_PAD_PC13__GPIO_45			0x02D 0x02D ALT0 0x0
#define S32V234_PAD_PC13__ETH_MDC			0x034 0x034 ALT1 0x1

#define S32V234_PAD_PC14__GPIO_46			0x02E 0x02E ALT0 0x0
#define S32V234_PAD_PC14__ETH_MDIO_OUT		0x034 0x034 ALT1 0x1
#define S32V234_PAD_PC14__ETH_MDIO_IN		0x3D5 0x1D5 ALT2 0x0

#define S32V234_PAD_PC15__GPIO_47			0x02F 0x02F ALT0 0x0
#define S32V234_PAD_PC15__ETH_RMII_CLK		0x035 0x035 ALT1 0x1
#define S32V234_PAD_PC15__ETH_TX_CLK		0x3D2 0x1D2 ALT2 0x0

#define S32V234_PAD_PD0__GPIO_48			0x030 0x030 ALT0 0x0
#define S32V234_PAD_PD0__ETH_RX_CLK			0x3D3 0x1D3 ALT2 0x0
#define S32V234_PAD_PD0__BOOT_TESTMOD_0		0x23C 0x03C ALT0 0x0

#define S32V234_PAD_PD1__GPIO_49			0x031 0x031 ALT0 0x0
#define S32V234_PAD_PD1__ETH_RX_D0			0x3CE 0x1CE ALT2 0x0
#define S32V234_PAD_PD1__BOOT_TESTMOD_1		0x23D 0x03D ALT0 0x0

#define S32V234_PAD_PD2__GPIO_50			0x032 0x032 ALT0 0x0
#define S32V234_PAD_PD2__ETH_RX_D1			0x3CF 0x1CF ALT2 0x0
#define S32V234_PAD_PD2__BOOT_TESTMOD_2		0x23E 0x03E ALT0 0x0

#define S32V234_PAD_PD3__GPIO_51			0x033 0x033 ALT0 0x0
#define S32V234_PAD_PD3__ETH_RX_D2			0x3D0 0x1D0 ALT2 0x0
#define S32V234_PAD_PD3__BOOT_TESTMOD_3		0x23F 0x03F ALT0 0x0

#define S32V234_PAD_PD4__GPIO_52			0x034 0x034 ALT0 0x0
#define S32V234_PAD_PD4__ETH_RX_D3			0x3D1 0x1D1 ALT2 0x0

#define S32V234_PAD_PD5__GPIO_53			0x035 0x035 ALT0 0x0
#define S32V234_PAD_PD5__ETH_RX_DV			0x3CD 0x1CD ALT2 0x0

#define S32V234_PAD_PD6__GPIO_54			0x036 0x036 ALT0 0x0
#define S32V234_PAD_PD6__ETH_RX_ER			0x3CA 0x1CA ALT2 0x0

#define S32V234_PAD_PD7__GPIO_55			0x037 0x037 ALT0 0x0
#define S32V234_PAD_PD7__ETH_TX_D0			0x037 0x037 ALT1 0x1

#define S32V234_PAD_PD8__GPIO_56			0x038 0x038 ALT0 0x0
#define S32V234_PAD_PD8__ETH_TX_D1			0x038 0x038 ALT1 0x1

#define S32V234_PAD_PD9__GPIO_57			0x039 0x039 ALT0 0x0
#define S32V234_PAD_PD9__ETH_TX_D2			0x039 0x039 ALT1 0x1

#define S32V234_PAD_PD10__GPIO_58			0x03A 0x03A ALT0 0x0
#define S32V234_PAD_PD10__ETH_TX_D3			0x03A 0x03A ALT1 0x1

#define S32V234_PAD_PD11__GPIO_59			0x03B 0x03B ALT0 0x0
#define S32V234_PAD_PD11__ETH_TX_D4			0x03B 0x03B ALT1 0x1

#define S32V234_PAD_PD12__GPIO_60			0x03C 0x03C ALT0 0x0
#define S32V234_PAD_PD12__ETH_TX_D5			0x03C 0x03C ALT1 0x1

#define S32V234_PAD_PD13__GPIO_61			0x03D 0x03D ALT0 0x0
#define S32V234_PAD_PD13__IPL_RDY			0x03D 0x03D ALT1 0x1
#define S32V234_PAD_PD13__VIU0_PCLK			0x270 0x070 ALT2 0x0
#define S32V234_PAD_PD13__PCIE_JTAG_TDI		0x214 0x014 ALT0 0x0

#define S32V234_PAD_PD14__GPIO_62			0x03E 0x03E ALT0 0x0
#define S32V234_PAD_PD14__VIU0_HSYNC		0x26E 0x06E ALT2 0x0
#define S32V234_PAD_PD14__IPL_LST			0x2EE 0x0EE ALT2 0x0
#define S32V234_PAD_PD14__PCIE_TRST_B		0x215 0x015 ALT0 0x0

#define S32V234_PAD_PD15__GPIO_63			0x03F 0x03F ALT0 0x0
#define S32V234_PAD_PD15__IPL_CLK			0x03F 0x03F ALT1 0x1
#define S32V234_PAD_PD15__PCIE_JTAG_TDO		0x045 0x045 ALT2 0x1
#define S32V234_PAD_PD15__VIU0_VSYNC		0x26F 0x06F ALT2 0x0
#define S32V234_PAD_PD15__IPL_CLK			0x2EF 0x0EF ALT2 0x0

#define S32V234_PAD_PE8__GPIO_72			0x048 0x048 ALT0 0x0
#define S32V234_PAD_PE8__SPI0_SCK			0x048 0x048 ALT2 0x1

#define S32V234_PAD_PE9__GPIO_73			0x049 0x049 ALT0 0x0
#define S32V234_PAD_PE9__SPI0_SOUT			0x049 0x049 ALT2 0x1

#define S32V234_PAD_PE10__GPIO_74			0x04A 0x04A ALT0 0x0
#define S32V234_PAD_PE10__SPI0_SIN			0x320 0x120 ALT3 0x0

#define S32V234_PAD_PE11__GPIO_75			0x04B 0x04B ALT0 0x0
#define S32V234_PAD_PE11__SPI0_CS0			0x04B 0x04B ALT2 0x1

#define S32V234_PAD_PE12__GPIO_76			0x04C 0x04C ALT0 0x0
#define S32V234_PAD_PE12__I2C0_DATA			0x04C 0x04C ALT2 0x1

#define S32V234_PAD_PE13__GPIO_77			0x04D 0x04D ALT0 0x0
#define S32V234_PAD_PE13__I2C0_CLK			0x04D 0x04D ALT2 0x1

#define S32V234_PAD_PE14__GPIO_78			0x04E 0x04E ALT0 0x0
#define S32V234_PAD_PE14__I2C1_DATA			0x04E 0x04E ALT2 0x1

#define S32V234_PAD_PE15__GPIO_79			0x04F 0x04F ALT0 0x0
#define S32V234_PAD_PE15__I2C1_CLK			0x04F 0x04F ALT2 0x1

#define S32V234_PAD_PF0__GPIO_80			0x050 0x050 ALT0 0x0
#define S32V234_PAD_PF0__USDHC_WP			0x384 0x184 ALT2 0x0

#define S32V234_PAD_PF1__GPIO_81			0x051 0x051 ALT0 0x0
#define S32V234_PAD_PF1__USDHC_CLK_OUT		0x051 0x051 ALT1 0x1
#define S32V234_PAD_PF1__USDHC_CLK_IN		0x386 0x186 ALT2 0x0

#define S32V234_PAD_PF2__GPIO_82			0x052 0x052 ALT0 0x0
#define S32V234_PAD_PF2__USDHC_CMD_OUT		0x052 0x052 ALT1 0x1
#define S32V234_PAD_PF2__USDHC_CMD_IN		0x385 0x185 ALT2 0x0

#define S32V234_PAD_PF3__GPIO_83			0x053 0x053 ALT0 0x0
#define S32V234_PAD_PF3__USDHC_DAT0_OUT		0x053 0x053 ALT1 0x1
#define S32V234_PAD_PF3__USDHC_DAT0_IN		0x387 0x187 ALT2 0x0

#define S32V234_PAD_PF4__GPIO_84			0x054 0x054 ALT0 0x0
#define S32V234_PAD_PF4__USDHC_DAT1_OUT		0x054 0x054 ALT1 0x1
#define S32V234_PAD_PF4__USDHC_DAT1_IN		0x388 0x188 ALT2 0x0

#define S32V234_PAD_PF5__GPIO_85			0x055 0x055 ALT0 0x0
#define S32V234_PAD_PF5__USDHC_DAT2_OUT		0x055 0x055 ALT1 0x1
#define S32V234_PAD_PF5__USDHC_DAT2_IN		0x389 0x189 ALT2 0x0

#define S32V234_PAD_PF6__GPIO_86			0x056 0x056 ALT0 0x0
#define S32V234_PAD_PF6__USDHC_DAT3_OUT		0x056 0x056 ALT1 0x1
#define S32V234_PAD_PF6__USDHC_DAT3_IN		0x38A 0x18A ALT2 0x0

#define S32V234_PAD_PF7__GPIO_87			0x057 0x057 ALT0 0x0
#define S32V234_PAD_PF7__USDHC_DAT4_OUT		0x057 0x057 ALT1 0x1
#define S32V234_PAD_PF7__USDHC_DAT4_IN		0x38B 0x18B ALT2 0x0

#define S32V234_PAD_PF8__GPIO_88			0x058 0x058 ALT0 0x0
#define S32V234_PAD_PF8__USDHC_DAT5_OUT		0x058 0x058 ALT1 0x1
#define S32V234_PAD_PF8__USDHC_DAT5_IN		0x38C 0x18C ALT2 0x0

#define S32V234_PAD_PF9__GPIO_89			0x059 0x059 ALT0 0x0
#define S32V234_PAD_PF9__USDHC_DAT6_OUT		0x059 0x059 ALT1 0x1
#define S32V234_PAD_PF9__USDHC_DAT6_IN		0x38D 0x18D ALT2 0x0

#define S32V234_PAD_PF10__GPIO_90			0x05A 0x05A ALT0 0x0
#define S32V234_PAD_PF10__USDHC_DAT7_OUT	0x05A 0x05A ALT1 0x1
#define S32V234_PAD_PF10__USDHC_DAT7_IN		0x38E 0x18E ALT2 0x0

#define S32V234_PAD_PF11__GPIO_91			0x05B 0x05B ALT0 0x0
#define S32V234_PAD_PF11__USDHC_RESET		0x05B 0x05B ALT1 0x1

#define S32V234_PAD_PF12__GPIO_92			0x05C 0x05C ALT0 0x0
#define S32V234_PAD_PF12__QSPI_A_CS1		0x05C 0x05C ALT1 0x1

#define S32V234_PAD_PF13__GPIO_93			0x05D 0x05D ALT0 0x0
#define S32V234_PAD_PF13__QSPI_B_CS1		0x05D 0x05D ALT1 0x1

#define S32V234_PAD_PF14__GPIO_94			0x05E 0x05E ALT0 0x0
#define S32V234_PAD_PF14__USDHC_VSELECT		0x05E 0x05E ALT1 0x1

#define S32V234_PAD_PF15__GPIO_95			0x05F 0x05F ALT0 0x0
#define S32V234_PAD_PF15__SPI2_CS3			0x05F 0x05F ALT1 0x1

#define S32V234_PAD_PG0__GPIO_96			0x060 0x060 ALT0 0x0
#define S32V234_PAD_PG0__SPI3_CS1			0x060 0x060 ALT1 0x1

#define S32V234_PAD_PG1__GPIO_97			0x061 0x061 ALT0 0x0
#define S32V234_PAD_PG1__SPI3_CS2			0x061 0x061 ALT1 0x1

#define S32V234_PAD_PG2__GPIO_98			0x062 0x062 ALT0 0x0
#define S32V234_PAD_PG2__SPI3_CS3			0x062 0x062 ALT1 0x1

#define S32V234_PAD_PG3__GPIO_99			0x063 0x063 ALT0 0x0
#define S32V234_PAD_PG3__ETH_TIMER0_OUT		0x063 0x063 ALT1 0x1
#define S32V234_PAD_PG3__I2C0_DATA_OUT		0x063 0x063 ALT2 0x1
#define S32V234_PAD_PG3__I2C0_DATA_IN		0x30D 0x10D ALT3 0x0
#define S32V234_PAD_PG3__ETH_TIMER0_IN		0x3D6 0x1D6 ALT3 0x0

#define S32V234_PAD_PG4__GPIO_100			0x064 0x064 ALT0 0x0
#define S32V234_PAD_PG4__ETH_TIMER1_OUT		0x064 0x064 ALT1 0x1
#define S32V234_PAD_PG4__I2C0_CLK_OUT		0x064 0x064 ALT2 0x1
#define S32V234_PAD_PG4__I2C0_CLK_IN		0x30C 0x10C ALT3 0x0
#define S32V234_PAD_PG4__ETH_TIMER1_IN		0x3D7 0x1D7 ALT3 0x0

#define S32V234_PAD_PG5__GPIO_101			0x065 0x065 ALT0 0x0
#define S32V234_PAD_PG5__FLEXTMR0_CH2_OUT	0x065 0x065 ALT1 0x1
#define S32V234_PAD_PG5__I2C1_DATA_OUT		0x065 0x065 ALT2 0x1
#define S32V234_PAD_PG5__FLEXTMR0_CH2_IN	0x202 0x002 ALT5 0x0
#define S32V234_PAD_PG5__I2C0_DATA_IN		0x30F 0x10F ALT3 0x0

#define S32V234_PAD_PG6__GPIO_102			0x066 0x066 ALT0 0x0
#define S32V234_PAD_PG6__FLEXTMR0_CH3_OUT	0x066 0x066 ALT1 0x1
#define S32V234_PAD_PG6__I2C1_CLK_OUT		0x066 0x066 ALT2 0x1
#define S32V234_PAD_PG6__FLEXTMR0_CH3_IN	0x202 0x002 ALT5 0x0
#define S32V234_PAD_PG6__I2C0_CLK_IN		0x30F 0x10F ALT3 0x0

#define S32V234_PAD_PH8__GPIO_120			0x078 0x078 ALT0 0x0
#define S32V234_PAD_PH8__DCU_HSYNC			0x078 0x078 ALT1 0x1

#define S32V234_PAD_PH9__GPIO_121			0x079 0x079 ALT0 0x0
#define S32V234_PAD_PH9__DCU_VSYNC			0x079 0x079 ALT1 0x1

#define S32V234_PAD_PH10__GPIO_122			0x07A 0x07A ALT0 0x0
#define S32V234_PAD_PH10__DCU_DE			0x07A 0x07A ALT1 0x1

#define S32V234_PAD_PH11__GPIO_123			0x07B 0x07B ALT0 0x0
#define S32V234_PAD_PH11__DCU_TAG			0x07B 0x07B ALT1 0x1

#define S32V234_PAD_PH12__GPIO_124			0x07C 0x07C ALT0 0x0
#define S32V234_PAD_PH12__DCU_PCLK			0x07C 0x07C ALT1 0x1

#define S32V234_PAD_PH13__GPIO_125			0x07D 0x07D ALT0 0x0
#define S32V234_PAD_PH13__DCU_R0			0x07D 0x07D ALT1 0x1

#define S32V234_PAD_PH14__GPIO_126			0x07E 0x07E ALT0 0x0
#define S32V234_PAD_PH14__DCU_R1			0x07E 0x07E ALT1 0x1

#define S32V234_PAD_PH15__GPIO_127			0x07F 0x07F ALT0 0x0
#define S32V234_PAD_PH15__DCU_R2			0x07F 0x07F ALT1 0x1

#define S32V234_PAD_PJ0__GPIO_128			0x080 0x080 ALT0 0x0
#define S32V234_PAD_PJ0__DCU_R3				0x080 0x080 ALT1 0x1

#define S32V234_PAD_PJ1__GPIO_129			0x081 0x081 ALT0 0x0
#define S32V234_PAD_PJ1__DCU_R4				0x081 0x081 ALT1 0x1

#define S32V234_PAD_PJ2__GPIO_130			0x082 0x082 ALT0 0x0
#define S32V234_PAD_PJ2__DCU_R5				0x082 0x082 ALT1 0x1

#define S32V234_PAD_PJ3__GPIO_131			0x083 0x083 ALT0 0x0
#define S32V234_PAD_PJ3__DCU_R6				0x083 0x083 ALT1 0x1

#define S32V234_PAD_PJ4__GPIO_132			0x084 0x084 ALT0 0x0
#define S32V234_PAD_PJ4__DCU_R7				0x084 0x084 ALT1 0x1

#define S32V234_PAD_PJ5__GPIO_133			0x085 0x085 ALT0 0x0
#define S32V234_PAD_PJ5__DCU_G0				0x085 0x085 ALT1 0x1

#define S32V234_PAD_PJ6__GPIO_134			0x086 0x086 ALT0 0x0
#define S32V234_PAD_PJ6__DCU_G1				0x086 0x086 ALT1 0x1

#define S32V234_PAD_PJ7__GPIO_135			0x087 0x087 ALT0 0x0
#define S32V234_PAD_PJ7__DCU_G2				0x087 0x087 ALT1 0x1

#define S32V234_PAD_PJ8__GPIO_136			0x088 0x088 ALT0 0x0
#define S32V234_PAD_PJ8__DCU_G3				0x088 0x088 ALT1 0x1

#define S32V234_PAD_PJ9__GPIO_137			0x089 0x089 ALT0 0x0
#define S32V234_PAD_PJ9__DCU_G4				0x089 0x089 ALT1 0x1

#define S32V234_PAD_PJ10__GPIO_138			0x08A 0x08A ALT0 0x0
#define S32V234_PAD_PJ10__DCU_G5			0x08A 0x08A ALT1 0x1

#define S32V234_PAD_PJ11__GPIO_139			0x08B 0x08B ALT0 0x0
#define S32V234_PAD_PJ11__DCU_G6			0x08B 0x08B ALT1 0x1

#define S32V234_PAD_PJ12__GPIO_140			0x08C 0x08C ALT0 0x0
#define S32V234_PAD_PJ12__DCU_G7			0x08C 0x08C ALT1 0x1

#define S32V234_PAD_PJ13__GPIO_141			0x08D 0x08D ALT0 0x0
#define S32V234_PAD_PJ13__DCU_B0			0x08D 0x08D ALT1 0x1

#define S32V234_PAD_PJ14__GPIO_142			0x08E 0x08E ALT0 0x0
#define S32V234_PAD_PJ14__DCU_B1			0x08E 0x08E ALT1 0x1

#define S32V234_PAD_PJ15__GPIO_143			0x08F 0x08F ALT0 0x0
#define S32V234_PAD_PJ15__DCU_B2			0x08F 0x08F ALT1 0x1

#define S32V234_PAD_PK0__GPIO_144			0x090 0x090 ALT0 0x0
#define S32V234_PAD_PK0__DCU_B3				0x090 0x090 ALT1 0x1

#define S32V234_PAD_PK1__GPIO_145			0x091 0x091 ALT0 0x0
#define S32V234_PAD_PK1__DCU_B4				0x091 0x091 ALT1 0x1

#define S32V234_PAD_PK2__GPIO_146			0x092 0x092 ALT0 0x0
#define S32V234_PAD_PK2__DCU_B5				0x092 0x092 ALT1 0x1

#define S32V234_PAD_PK3__GPIO_147			0x093 0x093 ALT0 0x0
#define S32V234_PAD_PK3__DCU_B6				0x093 0x093 ALT1 0x1

#define S32V234_PAD_PK4__GPIO_148			0x094 0x094 ALT0 0x0
#define S32V234_PAD_PK4__DCU_B7				0x094 0x094 ALT1 0x1

#define S32V234_PAD_PK5__GPIO_149			0x095 0x095 ALT0 0x0
#define S32V234_PAD_PK5__QSPI_A_CS0			0x095 0x095 ALT1 0x1
#define S32V234_PAD_PK5__USDHC_WP			0x384 0x184 ALT3 0x0

#define S32V234_PAD_PK6__GPIO_150			0x096 0x096 ALT0 0x0
#define S32V234_PAD_PK6__QSPI_A_SCK			0x096 0x096 ALT1 0x1
#define S32V234_PAD_PK6__USDHC_CLK_OUT		0x096 0x096 ALT2 0x1
#define S32V234_PAD_PK6__USDHC_CLK_IN		0x386 0x186 ALT3 0x0

#define S32V234_PAD_PK7__GPIO_151			0x097 0x097 ALT0 0x0
#define S32V234_PAD_PK7__USDHC_CMD_OUT		0x097 0x097 ALT1 0x1
#define S32V234_PAD_PK7__QSPI_A_DQS			0x333 0x133 ALT2 0x0
#define S32V234_PAD_PK7__USDHC_CMD_IN		0x385 0x185 ALT3 0x0

#define S32V234_PAD_PK8__GPIO_152			0x098 0x098 ALT0 0x0
#define S32V234_PAD_PK8__QSPI_A_DATA0_OUT	0x098 0x098 ALT1 0x1
#define S32V234_PAD_PK8__USDHC_DAT0_OUT		0x098 0x098 ALT2 0x1
#define S32V234_PAD_PK8__QSPI_A_DATA0_IN	0x334 0x134 ALT2 0x0
#define S32V234_PAD_PK8__USDHC_DAT0_IN		0x387 0x187 ALT3 0x0

#define S32V234_PAD_PK9__GPIO_153			0x099 0x099 ALT0 0x0
#define S32V234_PAD_PK9__QSPI_A_DATA1_OUT	0x099 0x099 ALT1 0x1
#define S32V234_PAD_PK9__USDHC_DAT1_OUT		0x099 0x099 ALT2 0x1
#define S32V234_PAD_PK9__QSPI_A_DATA1_IN	0x335 0x135 ALT2 0x0
#define S32V234_PAD_PK9__USDHC_DAT1_IN		0x388 0x188 ALT3 0x0

#define S32V234_PAD_PK10__GPIO_154			0x09A 0x09A ALT0 0x0
#define S32V234_PAD_PK10__QSPI_A_DATA2_OUT	0x09A 0x09A ALT1 0x1
#define S32V234_PAD_PK10__USDHC_DAT2_OUT	0x09A 0x09A ALT2 0x1
#define S32V234_PAD_PK10__QSPI_A_DATA2_IN	0x336 0x136 ALT2 0x0
#define S32V234_PAD_PK10__USDHC_DAT2_IN		0x389 0x189 ALT3 0x0

#define S32V234_PAD_PK11__GPIO_155			0x09B 0x09B ALT0 0x0
#define S32V234_PAD_PK11__QSPI_A_DATA3_OUT	0x09B 0x09B ALT1 0x1
#define S32V234_PAD_PK11__USDHC_DAT3_OUT	0x09B 0x09B ALT2 0x1
#define S32V234_PAD_PK11__QSPI_A_DATA3_IN	0x337 0x137 ALT2 0x0
#define S32V234_PAD_PK11__USDHC_DAT3_IN		0x38A 0x18A ALT3 0x0

#define S32V234_PAD_PK12__GPIO_156			0x09C 0x09C ALT0 0x0
#define S32V234_PAD_PK12__QSPI_B_CS0		0x09C 0x09C ALT1 0x1
#define S32V234_PAD_PK12__USDHC_RESET		0x09C 0x09C ALT2 0x1

#define S32V234_PAD_PK13__GPIO_157			0x09D 0x09D ALT0 0x0
#define S32V234_PAD_PK13__QSPI_B_SCK		0x09D 0x09D ALT1 0x1
#define S32V234_PAD_PK13__QSPI_CK2			0x09D 0x09D ALT2 0x1
#define S32V234_PAD_PK13__USDHC_VSELECT		0x09D 0x09D ALT3 0x1

#define S32V234_PAD_PK15__GPIO_159			0x09F 0x09F ALT0 0x0
#define S32V234_PAD_PK15__QSPI_B_DATA0_OUT	0x09F 0x09F ALT1 0x1
#define S32V234_PAD_PK15__QSPI_A_DATA4_OUT	0x09F 0x09F ALT2 0x1
#define S32V234_PAD_PK15__USDHC_DAT4_OUT	0x09F 0x09F ALT3 0x1
#define S32V234_PAD_PK15__QSPI_A_DATA4_IN	0x338 0x138 ALT2 0x0
#define S32V234_PAD_PK15__QSPI_B_DATA0_IN	0x33D 0x13D ALT2 0x0
#define S32V234_PAD_PK15__USDHC_DAT4_IN		0x38B 0x18B ALT2 0x0

#define S32V234_PAD_PL0__GPIO_160			0x0A0 0x0A0 ALT0 0x0
#define S32V234_PAD_PL0__QSPI_B_DATA1_OUT	0x0A0 0x0A0 ALT1 0x1
#define S32V234_PAD_PL0__QSPI_A_DATA5_OUT	0x0A0 0x0A0 ALT2 0x1
#define S32V234_PAD_PL0__USDHC_DAT5_OUT		0x0A0 0x0A0 ALT3 0x1
#define S32V234_PAD_PL0__QSPI_A_DATA5_IN	0x339 0x139 ALT2 0x0
#define S32V234_PAD_PL0__QSPI_B_DATA1_IN	0x33E 0x13E ALT2 0x0
#define S32V234_PAD_PL0__USDHC_DAT5_IN		0x38C 0x18C ALT2 0x0

#define S32V234_PAD_PL0__GPIO_161			0x0A1 0x0A1 ALT0 0x0
#define S32V234_PAD_PL0__QSPI_B_DATA2_OUT	0x0A1 0x0A1 ALT1 0x1
#define S32V234_PAD_PL0__QSPI_A_DATA6_OUT	0x0A1 0x0A1 ALT2 0x1
#define S32V234_PAD_PL0__USDHC_DAT6_OUT		0x0A1 0x0A1 ALT3 0x1
#define S32V234_PAD_PL0__QSPI_A_DATA6_IN	0x33A 0x13A ALT2 0x0
#define S32V234_PAD_PL0__QSPI_B_DATA2_IN	0x33F 0x13F ALT2 0x0
#define S32V234_PAD_PL0__USDHC_DAT6_IN		0x38D 0x18D ALT2 0x0

#define S32V234_PAD_PL0__GPIO_162			0x0A2 0x0A2 ALT0 0x0
#define S32V234_PAD_PL0__QSPI_B_DATA3_OUT	0x0A2 0x0A2 ALT1 0x1
#define S32V234_PAD_PL0__QSPI_A_DATA7_OUT	0x0A2 0x0A2 ALT2 0x1
#define S32V234_PAD_PL0__USDHC_DAT7_OUT		0x0A2 0x0A2 ALT3 0x1
#define S32V234_PAD_PL0__QSPI_A_DATA7_IN	0x33B 0x13B ALT2 0x0
#define S32V234_PAD_PL0__QSPI_B_DATA3_IN	0x340 0x140 ALT2 0x0
#define S32V234_PAD_PL0__USDHC_DAT7_IN		0x38E 0x18E ALT2 0x0


#endif