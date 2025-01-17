/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2019 Iceonwy Zheng <icenowy@aosc.io>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBOPENCM3_MEMORYMAP_H
#define LIBOPENCM3_MEMORYMAP_H

#include <libopencm3/cm3/memorymap.h>

/* --- GD32 specific peripheral definitions ------------------------------- */

/* Memory map for all buses */
#define FLASH_BASE			(0x08000000U)
#define PERIPH_BASE			(0x40000000U)
#define INFO_BASE			(0x1ffff000U)
#define PERIPH_BASE_APB1		(PERIPH_BASE + 0x00000)
#define PERIPH_BASE_APB2		(PERIPH_BASE + 0x10000)
#define PERIPH_BASE_AHB1		(PERIPH_BASE + 0x20000)
#define PERIPH_BASE_AHB2		(PERIPH_BASE + 0x8000000)

/* Register boundary addresses */

/* APB1 */
#define TIM1_BASE			(PERIPH_BASE_APB1 + 0x0000)
#define TIM2_BASE			(PERIPH_BASE_APB1 + 0x0400)
/* PERIPH_BASE_APB1 + 0x0800 (0x4000 0800 - 0x4000 0FFF): Reserved */
#define TIM5_BASE			(PERIPH_BASE_APB1 + 0x1000)
/* PERIPH_BASE_APB1 + 0x1400 (0x4000 1400 - 0x4000 1FFF): Reserved */
#define TIM13_BASE			(PERIPH_BASE_APB1 + 0x2000)
/* Only F170/F190 inside reserved area */
#define SLCD_BASE			(PERIPH_BASE_APB1 + 0x2400)
#define RTC_BASE			(PERIPH_BASE_APB1 + 0x2800)
#define BACKUP_REGS_BASE		(RTC_BASE + 0x50) 
#define WWDGT_BASE			(PERIPH_BASE_APB1 + 0x2c00)
#define FWDGT_BASE			(PERIPH_BASE_APB1 + 0x3000)
/* PERIPH_BASE_APB1 + 0x3400 (0x4000 3400 - 0x4000 37FF): Reserved */
#define SPI1_BASE			(PERIPH_BASE_APB1 + 0x3800)
/* Only F170/F190 inside reserved area */
#define SPI2_BASE			(PERIPH_BASE_APB1 + 0x3C00)
/* PERIPH_BASE_APB1 + 0x4000 (0x4000 4000 - 0x4000 43FF): Reserved */
#define USART1_BASE			(PERIPH_BASE_APB1 + 0x4400)
/* PERIPH_BASE_APB1 + 0x4800 (0x4000 4800 - 0x4000 53FF): Reserved */
#define I2C0_BASE			(PERIPH_BASE_APB1 + 0x5400)
#define I2C1_BASE			(PERIPH_BASE_APB1 + 0x5800)
#define USB_DEV_FS_BASE			(PERIPH_BASE_APB1 + 0x5c00)
#define USB_PMA_BASE			(PERIPH_BASE_APB1 + 0x6000)
#define USB_SRAM_BASE			(PERIPH_BASE_APB1 + 0x6000)
/* PERIPH_BASE_APB1 + 0x6400 (0x4000 6400 - 0x4000 6FFF): Reserved */
#define POWER_CONTROL_BASE		(PERIPH_BASE_APB1 + 0x7000)
#define DAC_BASE			(PERIPH_BASE_APB1 + 0x7400)
#define CEC_BASE			(PERIPH_BASE_APB1 + 0x7800)
/* Only F170/F190 inside reserved area */
#define I2C2_BASE			(PERIPH_BASE_APB1 + 0xc000)
/* PERIPH_BASE_APB1 + 0xC400 (0x4000 C400 - 0x4000 FFFF): Reserved */

/* APB2 */
#define SYSCFG_COMP_BASE		(PERIPH_BASE_APB2 + 0x0000)
#define EXTI_BASE			(PERIPH_BASE_APB2 + 0x0400)
/* PERIPH_BASE_APB2 + 0x0800 (0x4001 0800 - 0x4001 23FF): Reserved */
#define ADC_BASE			(PERIPH_BASE_APB2 + 0x2400)
/* PERIPH_BASE_APB2 + 0x2800 (0x4001 2800 - 0x4001 2BFF): Reserved */
#define TIM0_BASE			(PERIPH_BASE_APB2 + 0x2c00)
#define SPI0_BASE			(PERIPH_BASE_APB2 + 0x3000)
/* PERIPH_BASE_APB2 + 0x3400 (0x4001 3400 - 0x4001 37FF): Reserved */
#define USART0_BASE			(PERIPH_BASE_APB2 + 0x3800)
/* PERIPH_BASE_APB2 + 0x3C00 (0x4001 3C00 - 0x4001 3FFF): Reserved */
#define TIM14_BASE			(PERIPH_BASE_APB2 + 0x4000)
#define TIM15_BASE			(PERIPH_BASE_APB2 + 0x4400)
#define TIM16_BASE			(PERIPH_BASE_APB2 + 0x4800)
/* PERIPH_BASE_APB2 + 0x4C00 (0x4001 4C00 - 0x4001 FFFF): Reserved */

/* AHB1 */
#define DMA0_BASE			(PERIPH_BASE_AHB1 + 0x0000)
/* PERIPH_BASE_AHB1 + 0x0400 (0x4002 0400 - 0x4002 0FFF): Reserved */
#define RCU_BASE			(PERIPH_BASE_AHB1 + 0x1000)
/* PERIPH_BASE_AHB1 + 0x1400 (0x4002 1400 - 0x4002 1FFF): Reserved */
#define FLASH_MEM_INTERFACE_BASE	(PERIPH_BASE_AHB1 + 0x2000)
/* PERIPH_BASE_AHB1 + 0x2400 (0x4002 2400 - 0x4002 2FFF): Reserved */
#define CRC_BASE			(PERIPH_BASE_AHB1 + 0x3000)
/* PERIPH_BASE_AHB1 + 0x3400 (0x4002 3400 - 0x4002 3FFF): Reserved */
#define TSC_BASE			(PERIPH_BASE_AHB1 + 0x4000)
/* PERIPH_BASE_AHB1 + 0x4400 (0x4002 4400 - 0x47FF FFFF): Reserved */

/* AHB 2 */
#define GPIO_PORT_A_BASE		(PERIPH_BASE_AHB2 + 0x0000)
#define GPIO_PORT_B_BASE		(PERIPH_BASE_AHB2 + 0x0400)
#define GPIO_PORT_C_BASE		(PERIPH_BASE_AHB2 + 0x0800)
#define GPIO_PORT_D_BASE		(PERIPH_BASE_AHB2 + 0x0c00)
/* PERIPH_BASE_AHB2 + 0x1000 (0x4800 1000 - 0x4800 13FF): Reserved */
#define GPIO_PORT_F_BASE		(PERIPH_BASE_AHB2 + 0x1400)
/* PERIPH_BASE_AHB2 + 0x1800 (0x4800 1800 - 0x4FFF FFFF): Reserved */

/* Device Electronic Signature */
#define DESIG_FLASH_SIZE_BASE		(INFO_BASE + 0x7e0)
#define DESIG_UNIQUE_ID_BASE		(INFO_BASE + 0x7ac)
/* Ignore the "reserved for future use" half of the first word */
#define DESIG_UNIQUE_ID0		MMIO32(DESIG_UNIQUE_ID_BASE)
#define DESIG_UNIQUE_ID1		MMIO32(DESIG_UNIQUE_ID_BASE + 4)
#define DESIG_UNIQUE_ID2		MMIO32(DESIG_UNIQUE_ID_BASE + 8)

#endif
