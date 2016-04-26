/*
 * s32v234 pinctrl driver based on imx pinmux and pinconf core
 *
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/err.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-s32v.h"

enum s32v234_pads {
	S32V234_PAD_PA12_UART0_TXD = 12,
	S32V234_PAD_PA11_UART0_RXD_OUT = 11,
	S32V234_PAD_PA11_UART0_RXD_IN = 712,
	S32V234_PAD_PA14_UART1_TXD = 14,
	S32V234_PAD_PA13_UART1_RXD_OUT = 13,
	S32V234_PAD_PA13_UART1_RXD_IN = 714,
	S32V234_PAD_PK6_USDHC_CLK_OUT = 150,
	S32V234_PAD_PK6_USDHC_CLK_IN = 902,
	S32V234_PAD_PK7_USDHC_CMD_OUT = 151,
	S32V234_PAD_PK7_USDHC_CMD_IN = 901,
	S32V234_PAD_PK8_USDHC_DAT0_OUT = 152,
	S32V234_PAD_PK8_USDHC_DAT0_IN = 903,
	S32V234_PAD_PK9_USDHC_DAT1_OUT = 153,
	S32V234_PAD_PK9_USDHC_DAT1_IN = 904,
	S32V234_PAD_PK10_USDHC_DAT2_OUT = 154,
	S32V234_PAD_PK10_USDHC_DAT2_IN = 905,
	S32V234_PAD_PK11_USDHC_DAT3_OUT = 155,
	S32V234_PAD_PK11_USDHC_DAT3_IN = 906,
	S32V234_PAD_PK15_USDHC_DAT4_OUT = 159,
	S32V234_PAD_PK15_USDHC_DAT4_IN = 907,
	S32V234_PAD_PL0_USDHC_DAT5_OUT = 160,
	S32V234_PAD_PL0_USDHC_DAT5_IN = 908,
	S32V234_PAD_PL1_USDHC_DAT6_OUT = 161,
	S32V234_PAD_PL1_USDHC_DAT6_IN = 909,
	S32V234_PAD_PL2_USDHC_DAT7_OUT = 162,
	S32V234_PAD_PL2_USDHC_DAT7_IN = 910,
	S32V234_PAD_PG3_I2C0_DATA_OUT = 99,
	S32V234_PAD_PG3_I2C0_DATA_IN = 781,
	S32V234_PAD_PG4_I2C0_SCLK_OUT = 100,
	S32V234_PAD_PG4_I2C0_SCLK_IN = 780,
	S32V234_PAD_PG5_I2C1_DATA_OUT = 101,
	S32V234_PAD_PG5_I2C1_DATA_IN = 783,
	S32V234_PAD_PG6_I2C1_SCLK_OUT = 102,
	S32V234_PAD_PG6_I2C1_SCLK_IN = 782,
	S32V234_PAD_PB3_I2C2_DATA_OUT = 19,
	S32V234_PAD_PB3_I2C2_DATA_IN = 785,
	S32V234_PAD_PB4_I2C2_SCLK_OUT = 20,
	S32V234_PAD_PB5_I2C2_SCLK_IN = 784,
	S32V234_PAD_PC13_MDC = 45,
	S32V234_PAD_PC14_MDIO_OUT = 46,
	S32v234_PAD_PC14_MDIO_IN = 981,
	S32V234_PAD_PC15_TXCLK_OUT = 47,
	S32V234_PAD_PC15_TXCLK_IN = 978,
	S32V234_PAD_PD0_RXCLK_OUT = 48,
	S32V234_PAD_PD0_RXCLK_IN = 979,
	S32V234_PAD_PD1_RX_D1_OUT = 49,
	S32V234_PAD_PD1_RX_D1_IN = 974,
	S32V234_PAD_PD2_RX_D2_OUT = 50,
	S32V234_PAD_PD2_RX_D2_IN = 975,
	S32V234_PAD_PD3_RX_D3_OUT = 51,
	S32V234_PAD_PD3_RX_D3_IN = 976,
	S32V234_PAD_PD4_RX_D4_OUT = 52,
	S32V234_PAD_PD4_RX_D4_IN = 977,
	S32V234_PAD_PD4_RX_DV_OUT = 53,
	S32V234_PAD_PD4_RX_DV_IN = 973,
	S32V234_PAD_PD7_TX_D0_OUT = 55,
	S32V234_PAD_PD8_TX_D1_OUT = 56,
	S32V234_PAD_PD9_TX_D2_OUT = 57,
	S32V234_PAD_PD10_TX_D3_OUT = 58,
	S32V234_PAD_PD11_TX_EN_OUT = 59,
	S32V234_PAD_PH8__DCU_HSYNC_C1 = 120,
	S32V234_PAD_PH9__DCU_VSYNC_C2 = 121,
	S32V234_PAD_PH10__DCU_DE_C3 = 122,
	S32V234_PAD_PH10__DCU_PCLK_D1 = 124,
	S32V234_PAD_PH13__DCU_R0_D2 = 125,
	S32V234_PAD_PH14__DCU_R1_D3 = 126,
	S32V234_PAD_PH15__DCU_R2_D4 = 127,
	S32V234_PAD_PJ0__DCU_R3_D5 = 128,
	S32V234_PAD_PJ1__DCU_R4_D6 = 129,
	S32V234_PAD_PJ2__DCU_R5_D7 = 130,
	S32V234_PAD_PJ3__DCU_R6_D8 = 131,
	S32V234_PAD_PJ4__DCU_R7_D9 = 132,
	S32V234_PAD_PJ5__DCU_G0_D10 = 133,
	S32V234_PAD_PJ6__DCU_G1_D11 = 134,
	S32V234_PAD_PJ7__DCU_G2_D12 = 135,
	S32V234_PAD_PJ8__DCU_G3_D13 = 136,
	S32V234_PAD_PJ9__DCU_G4_D14 = 137,
	S32V234_PAD_PJ10__DCU_G5_D15 = 138,
	S32V234_PAD_PJ11__DCU_G6_D16 = 139,
	S32V234_PAD_PJ12__DCU_G7_D17 = 140,
	S32V234_PAD_PJ13__DCU_B0_D18 = 141,
	S32V234_PAD_PJ14__DCU_B1_D19 = 142,
	S32V234_PAD_PJ15__DCU_B2_D20 = 143,
	S32V234_PAD_PK0__DCU_B3_D21 = 144,
	S32V234_PAD_PK1__DCU_B4_D22 = 145,
	S32V234_PAD_PK2__DCU_B5_D23 = 146,
	S32V234_PAD_PK3__DCU_B6_D24 = 147,
	S32V234_PAD_PK4__DCU_B7_D25 = 148,
};

/* Pad names for the pinmux subsystem */
static const struct pinctrl_pin_desc s32v234_pinctrl_pads[] = {
	S32V_PINCTRL_PIN(S32V234_PAD_PA12_UART0_TXD),
	S32V_PINCTRL_PIN(S32V234_PAD_PA11_UART0_RXD_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PA11_UART0_RXD_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PA14_UART1_TXD),
	S32V_PINCTRL_PIN(S32V234_PAD_PA13_UART1_RXD_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PA13_UART1_RXD_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PK6_USDHC_CLK_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PK6_USDHC_CLK_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PK7_USDHC_CMD_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PK7_USDHC_CMD_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PK8_USDHC_DAT0_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PK8_USDHC_DAT0_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PK9_USDHC_DAT1_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PK9_USDHC_DAT1_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PK10_USDHC_DAT2_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PK10_USDHC_DAT2_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PK11_USDHC_DAT3_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PK11_USDHC_DAT3_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PK15_USDHC_DAT4_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PK15_USDHC_DAT4_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PL0_USDHC_DAT5_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PL0_USDHC_DAT5_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PL1_USDHC_DAT6_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PL1_USDHC_DAT6_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PL2_USDHC_DAT7_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PL2_USDHC_DAT7_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PG3_I2C0_DATA_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PG3_I2C0_DATA_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PG4_I2C0_SCLK_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PG4_I2C0_SCLK_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PG5_I2C1_DATA_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PG5_I2C1_DATA_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PG6_I2C1_SCLK_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PG6_I2C1_SCLK_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PB3_I2C2_DATA_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PB3_I2C2_DATA_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PB4_I2C2_SCLK_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PB5_I2C2_SCLK_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PC13_MDC),
	S32V_PINCTRL_PIN(S32V234_PAD_PC14_MDIO_OUT),
	S32V_PINCTRL_PIN(S32v234_PAD_PC14_MDIO_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PC15_TXCLK_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PC15_TXCLK_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PD0_RXCLK_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD0_RXCLK_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PD1_RX_D1_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD1_RX_D1_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PD2_RX_D2_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD2_RX_D2_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PD3_RX_D3_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD3_RX_D3_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PD4_RX_D4_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD4_RX_D4_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PD4_RX_DV_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD4_RX_DV_IN),
	S32V_PINCTRL_PIN(S32V234_PAD_PD7_TX_D0_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD8_TX_D1_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD9_TX_D2_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD10_TX_D3_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PD11_TX_EN_OUT),
	S32V_PINCTRL_PIN(S32V234_PAD_PH8__DCU_HSYNC_C1),
	S32V_PINCTRL_PIN(S32V234_PAD_PH9__DCU_VSYNC_C2),
	S32V_PINCTRL_PIN(S32V234_PAD_PH10__DCU_DE_C3),
	S32V_PINCTRL_PIN(S32V234_PAD_PH10__DCU_PCLK_D1),
	S32V_PINCTRL_PIN(S32V234_PAD_PH13__DCU_R0_D2),
	S32V_PINCTRL_PIN(S32V234_PAD_PH14__DCU_R1_D3),
	S32V_PINCTRL_PIN(S32V234_PAD_PH15__DCU_R2_D4),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ0__DCU_R3_D5),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ1__DCU_R4_D6),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ2__DCU_R5_D7),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ3__DCU_R6_D8),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ4__DCU_R7_D9),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ5__DCU_G0_D10),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ6__DCU_G1_D11),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ7__DCU_G2_D12),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ8__DCU_G3_D13),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ9__DCU_G4_D14),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ10__DCU_G5_D15),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ11__DCU_G6_D16),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ12__DCU_G7_D17),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ13__DCU_B0_D18),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ14__DCU_B1_D19),
	S32V_PINCTRL_PIN(S32V234_PAD_PJ15__DCU_B2_D20),
	S32V_PINCTRL_PIN(S32V234_PAD_PK0__DCU_B3_D21),
	S32V_PINCTRL_PIN(S32V234_PAD_PK1__DCU_B4_D22),
	S32V_PINCTRL_PIN(S32V234_PAD_PK2__DCU_B5_D23),
	S32V_PINCTRL_PIN(S32V234_PAD_PK3__DCU_B6_D24),
	S32V_PINCTRL_PIN(S32V234_PAD_PK4__DCU_B7_D25)
};

static struct s32v_pinctrl_soc_info s32v234_pinctrl_info = {
	.pins = s32v234_pinctrl_pads,
	.npins = ARRAY_SIZE(s32v234_pinctrl_pads),
};

static struct of_device_id s32v234_pinctrl_of_match[] = {
	{ .compatible = "fsl,s32v234-siul2", },
	{ /* sentinel */ }
};

static int s32v234_pinctrl_probe(struct platform_device *pdev)
{
	return s32v_pinctrl_probe(pdev, &s32v234_pinctrl_info);
}

static struct platform_driver s32v234_pinctrl_driver = {
	.driver = {
		.name = "s32v234-siul2",
		.owner = THIS_MODULE,
		.of_match_table = s32v234_pinctrl_of_match,
	},
	.probe = s32v234_pinctrl_probe,
	.remove = s32v_pinctrl_remove,
};

static int __init s32v234_pinctrl_init(void)
{
	return platform_driver_register(&s32v234_pinctrl_driver);
}
arch_initcall(s32v234_pinctrl_init);

static void __exit s32v234_pinctrl_exit(void)
{
	platform_driver_unregister(&s32v234_pinctrl_driver);
}
module_exit(s32v234_pinctrl_exit);

MODULE_DESCRIPTION("Freescale S32V234 pinctrl driver");
MODULE_LICENSE("GPL v2");
