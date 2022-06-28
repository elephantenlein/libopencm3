/** @addtogroup adc_defines

@author @htmlonly &copy; @endhtmlonly 2015 Karl Palsson <karlp@tweak.net.au>

 */

/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2015 Karl Palsson <karlp@tweak.net.au>
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

/**@{*/

/* THIS FILE SHOULD NOT BE INCLUDED DIRECTLY, BUT ONLY VIA ADC.H
The order of header inclusion is important. adc.h includes the device
specific memorymap.h header before including this header file.*/

/** @cond */
#ifdef LIBOPENCM3_ADC_H
/** @endcond */
#ifndef LIBOPENCM3_ADC_COMMON_H
#define LIBOPENCM3_ADC_COMMON_H

/** @defgroup adc_registers ADC registers
@{*/
/* ----- ADC registers  -----------------------------------------------------*/
/** Status register **/
#define ADC_STAT(ADC)		MMIO32((adc) + 0x00)
/** Control register 0 **/
#define ADC_CTL0(ADC)		MMIO32((adc) + 0x04)
/** Control register 1 **/
#define ADC_CTL1(ADC)		MMIO32((adc) + 0x08)
/** Sampling time register 0 **/
#define ADC_SAMPT0(ADC)		MMIO32((adc) + 0x0C)
/** Sampling time register 1 **/
#define ADC_SAMPT1(ADC)		MMIO32((adc) + 0x10)
/** Inserted channel data offset register 0 **/
#define ADC_IOFF0(ADC)		MMIO32((adc) + 0x14)
/** Inserted channel data offset register 1 **/
#define ADC_IOFF1(ADC)		MMIO32((adc) + 0x18)
/** Inserted channel data offset register 2 **/
#define ADC_IOFF2(ADC)		MMIO32((adc) + 0x1C)
/** Inserted channel data offset register 3 **/
#define ADC_IOFF3(ADC)		MMIO32((adc) + 0x20)
/** Watchdog high threshold register **/
#define ADC_WDHT(ADC)		MMIO32((adc) + 0x24)
/** Watchdog low threshold register **/
#define ADC_WDLT(ADC)		MMIO32((adc) + 0x28)
/** Regular sequence register 0 **/
#define ADC_RSQ0(ADC)		MMIO32((adc) + 0x2C)
/** Regular sequence register 1 **/
#define ADC_RSQ1(ADC)		MMIO32((adc) + 0x30)
/** Regular sequence register 2 **/
#define ADC_RSQ2(ADC)		MMIO32((adc) + 0x34)
/** Inserted sequence register **/
#define ADC_ISQ(ADC)		MMIO32((adc) + 0x38)
/** Inserted data register 0 **/
#define ADC_IDATA0(ADC)		MMIO32((adc) + 0x3C)
/** Inserted data register 1 **/
#define ADC_IDATA1(ADC)		MMIO32((adc) + 0x40)
/** Inserted data register 2 **/
#define ADC_IDATA2(ADC)		MMIO32((adc) + 0x44)
/** Inserted data register 3 **/
#define ADC_IDATA3(ADC)		MMIO32((adc) + 0x48)
/** Regular data register **/
#define ADC_RDATA(ADC)		MMIO32((adc) + 0x4C)

/* Oversampling only for F170 and F190 */
#define ADC_OVSAMPCTL(ADC)	MMIO32((adc) + 0x80)
/**@}*/

/* --- Register values -------------------------------------------------------*/

/* ADC_STAT Values -----------------------------------------------------------*/
/** @defgroup adc_stat STAT ADC status register
@{*/

/** STRC: Start flag of regular channel group **/
#define ADC_STAT_STRC		(1 << 4)

/** STIC: Start flag of inserted channel group **/
#define ADC_STAT_STIC (1<<3)
/** EOIC: End of inserted group conversion flag **/
#define ADC_STAT_EOIC (1<<2)
/** EOC: End of group conversion flag **/
#define ADC_STAT_EOC (1<<1)
/** WDE: Analog watchdog event flag **/
#define ADC_STAT_WDE (1<<0)
/**@}*/

/* ADC_CTL0 Values -----------------------------------------------------------*/
/** @defgroup adc_ctl0 CTL0 ADC control register 0
@{*/

/** RWDEN: Regular channel analog watchdog enable **/
#define ADC_CTL0_RWDEN (1<<23)
/** IWDEN: Inserted channel analog watchdog enable **/
#define ADC_CTL0_IWDEN (1<<22)

#define ADC_CTL0_DISNUM_SHIFT	13
#define ADC_CTL0_DISNUM		(0x07 << ADC_CTL0_DISNUM_SHIFT)
/** DISNUM: Number of conversions in discontinuous mode **/
#define ADC_CTL0_DISNUM_VAL(x)	((x) << ADC_CTL0_DISNUM_SHIFT)

/** DISIC: Discontinuous mode on inserted channels **/
#define ADC_CTL0_DISIC (1<<12)
/** DISRC: Discontinuous mode on regular channels **/
#define ADC_CTL0_DISRC (1<<11)
/** ICA: Inserted channel group convert automatically **/
#define ADC_CTL0_ICA (1<<10)
/** WDSC: When in scan mode, analog watchdog is effective on a single channel **/
#define ADC_CTL0_WDSC (1<<9)
/** SM: Scan mode **/
#define ADC_CTL0_SM (1<<8)
/** EOICIE: Interrupt enable for EOIC **/
#define ADC_CTL0_EOICIE (1<<7)
/** WDEIE: Interrupt enable for WDE **/
#define ADC_CTL0_WDEIE (1<<6)
/** EOCIE: Interrupt enable for EOC **/
#define ADC_CTL0_EOCIE (1<<5)

#define ADC_CTL0_WDCHSEL_SHIFT	0
#define ADC_CTL0_WDCHSEL_MASK	(0x3F << ADC_CTL0_WDCHSEL_SHIFT)
/** WDCHSEL: **/
#define ADC_CTL0_WDCHSEL_VAL(x) ((x) << ADC_CTL0_WDCHSEL_SHIFT)
/**@}*/

/* ADC_CTL1 Values -----------------------------------------------------------*/
/** @defgroup adc_ctl1 CTL1 ADC control register 1
@{*/

/** VBATEN: Enable Vbat channel **/
#define ADC_CTL1_VBATEN (1<<24)
/** TSVREN: Channel 16 and 17 enable **/
#define ADC_CTL1_TSVREN (1<<23)
/** SWRCST: Start on regular channel **/
#define ADC_CTL1_SWRCST (1<<22)
/** SWICST: Start on inserted channel **/
#define ADC_CTL1_SWICST (1<<21)
/** ETERC: External trigger enable for regular channel **/
#define ADC_CTL1_ETERC (1<<20)

#define ADC_CTL1_ETSRC_SHIFT	17
#define ADC_CTL1_ETSRC_MASK	(0x07 << ADC_CTL1_ETSRC_SHIFT)
/** ETSRC: External trigger select for regular channel **/
#define ADC_CTL1_ETSRC_TIM0_CH0		(0 << ADC_CTL1_ETSRC_SHIFT)
#define ADC_CTL1_ETSRC_TIM0_CH1		(1 << ADC_CTL1_ETSRC_SHIFT)
#define ADC_CTL1_ETSRC_TIM0_CH2		(2 << ADC_CTL1_ETSRC_SHIFT)
#define ADC_CTL1_ETSRC_TIM1_CH1		(3 << ADC_CTL1_ETSRC_SHIFT)
#define ADC_CTL1_ETSRC_TIM2_TRGO	(4 << ADC_CTL1_ETSRC_SHIFT)
#define ADC_CTL1_ETSRC_TIM14_CH0	(5 << ADC_CTL1_ETSRC_SHIFT)
#define ADC_CTL1_ETSRC_EXTI11		(6 << ADC_CTL1_ETSRC_SHIFT)
#define ADC_CTL1_ETSRC_SWRCST		(7 << ADC_CTL1_ETSRC_SHIFT)

/** ETEIC: External trigger enable for inserted channel **/
#define ADC_CTL1_ETEIC (1<<15)

#define ADC_CTL1_ETSIC_SHIFT	12
#define ADC_CTL1_ETSIC_MASK	(0x07 << ADC_CTL1_ETSIC_SHIFT)
/** ETSIC: External trigger select for regular channel **/
#define ADC_CTL1_ETSIC_TIM0_TRGO	(0 << ADC_CTL1_ETSIC_SHIFT)
#define ADC_CTL1_ETSIC_TIM0_CH3		(1 << ADC_CTL1_ETSIC_SHIFT)
#define ADC_CTL1_ETSIC_TIM1_TRGO	(2 << ADC_CTL1_ETSIC_SHIFT)
#define ADC_CTL1_ETSIC_TIM1_CH0		(3 << ADC_CTL1_ETSIC_SHIFT)
#define ADC_CTL1_ETSIC_TIM2_CH3		(4 << ADC_CTL1_ETSIC_SHIFT)
#define ADC_CTL1_ETSIC_TIM14_TRGO	(5 << ADC_CTL1_ETSIC_SHIFT)
#define ADC_CTL1_ETSIC_EXTI15		(6 << ADC_CTL1_ETSIC_SHIFT)
#define ADC_CTL1_ETSIC_SWICST		(7 << ADC_CTL1_ETSIC_SHIFT)

/** DAL: Data alignment **/
#define ADC_CTL1_DAL (1<<11)
/** DMA: DMA request enable **/
#define ADC_CTL1_DMA (1<<8)
/** RSTCLB: Reset calibration **/
#define ADC_CTL1_RSTCLB (1<<3)
/** CLB: ADC calibration **/
#define ADC_CTL1_CLB (1<<2)
/** CTN: Continuous mode **/
#define ADC_CTL1_CTN (1<<1)
/** ADCON: ADC ON, zero to one for wakeup, one to one for start conversion **/
#define ADC_CTL1_ADCON (1<<0)
/**@}*/

/* ADC_SAMPT0 Values ---------------------------------------------------------*/
/** @defgroup adc_sampt0 SAMPT0 ADC sample time register
@{*/

#define ADC_SAMPT0_SPT_SHIFT(x) (3*(x - 10))

#define ADC_SAMPT0_SPT17_SHIFT 21
#define ADC_SAMPT0_SPT16_SHIFT 18
#define ADC_SAMPT0_SPT15_SHIFT 15
#define ADC_SAMPT0_SPT14_SHIFT 12
#define ADC_SAMPT0_SPT13_SHIFT 9
#define ADC_SAMPT0_SPT12_SHIFT 6
#define ADC_SAMPT0_SPT11_SHIFT 3
#define ADC_SAMPT0_SPT10_SHIFT 0
/**@}*/

/* ADC_SAMPT1 Values ---------------------------------------------------------*/
/** @defgroup adc_sampt1 SAMPT0 ADC sample time register
@{*/

#define ADC_SAMPT1_SPT_SHIFT(x) (3*x)

#define ADC_SAMPT1_SPT9_SHIFT 27
#define ADC_SAMPT1_SPT8_SHIFT 24
#define ADC_SAMPT1_SPT7_SHIFT 21
#define ADC_SAMPT1_SPT6_SHIFT 18
#define ADC_SAMPT1_SPT5_SHIFT 15
#define ADC_SAMPT1_SPT4_SHIFT 12
#define ADC_SAMPT1_SPT3_SHIFT 9
#define ADC_SAMPT1_SPT2_SHIFT 6
#define ADC_SAMPT1_SPT1_SHIFT 3
#define ADC_SAMPT1_SPT0_SHIFT 0
/**@}*/

#define ADC_SAMPT_1_5	0
#define ADC_SAMPT_7_5	1
#define ADC_SAMPT_13_5	2
#define ADC_SAMPT_28_5	3
#define ADC_SAMPT_41_5	4
#define ADC_SAMPT_55_5	5
#define ADC_SAMPT_71_5	6
#define ADC_SAMPT_239_5	7
#define ADC_SAMPT_MASK  0x07

/* ADC_IOFF Values -----------------------------------------------------------*/
/** @defgroup adc_ioff IOFF ADC inserted data offset register
@{*/

#define ADC_IOFF_MASK 0x00000FFF
/**@}*/

/* ADC_WDHT Values -----------------------------------------------------------*/
/** @defgroup adc_wdht WDHT ADC analog watchdog high threshold
@{*/

#define ADC_WDHT_MASK 0x00000FFF
/**@}*/

/* ADC_WDLT Values -----------------------------------------------------------*/
/** @defgroup adc_wdlt WDLT ADC analog watchdog low threshold
@{*/

#define ADC_WDLT_MASK 0x00000FFF
/**@}*/

/* ADC_RSQ0 Values ---------------------------------------------------------*/
/** @defgroup adc_rsq0 RSQ0 ADC regular sequence register 0
@{*/
#define ADC_RSQ0_RL_SHIFT	20
#define ADC_RSQ0_RL_MASK	(0x0F << ADC_RSQ0_RL_SHIFT)
#define ADC_RSQ0_RL_VAL(x)	((x - 1) << ADC_RSQ0_RL_SHIFT)

#define ADC_RSQ0_RSQ15_SHIFT	15
#define ADC_RSQ0_RSQ14_SHIFT	10
#define ADC_RSQ0_RSQ13_SHIFT	5
#define ADC_RSQ0_RSQ12_SHIFT	0
/**@}*/

/* ADC_RSQ1 Values ---------------------------------------------------------*/
/** @defgroup adc_rsq1 RSQ1 ADC regular sequence register 0
@{*/
#define ADC_RSQ1_RSQ11_SHIFT	25
#define ADC_RSQ1_RSQ10_SHIFT	20
#define ADC_RSQ1_RSQ9_SHIFT	15
#define ADC_RSQ1_RSQ8_SHIFT	10
#define ADC_RSQ1_RSQ7_SHIFT	5
#define ADC_RSQ1_RSQ6_SHIFT	0
/**@}*/

/* ADC_RSQ2 Values ---------------------------------------------------------*/
/** @defgroup adc_rsq2 RSQ2 ADC regular sequence register 0
@{*/
#define ADC_RSQ2_RSQ5_SHIFT	25
#define ADC_RSQ2_RSQ4_SHIFT	20
#define ADC_RSQ2_RSQ3_SHIFT	15
#define ADC_RSQ2_RSQ2_SHIFT	10
#define ADC_RSQ2_RSQ1_SHIFT	5
#define ADC_RSQ2_RSQ0_SHIFT	0
/**@}*/

/* ADC_ISQ Values ---------------------------------------------------------*/
/** @defgroup adc_isq ISQ ADC inserted sequence register
@{*/
#define ADC_ISQ_IL_SHIFT	20
#define ADC_ISQ_IL_MASK		(0x03 << ADC_ISQ_IL_SHIFT)
#define ADC_ISQ_IL_VAL(x)	((x) << ADC_ISQ_IL_SHIFT)

#define ADC_ISQ_ISQ3_SHIFT	15
#define ADC_ISQ_ISQ2_SHIFT	10
#define ADC_ISQ_ISQ1_SHIFT	5
#define ADC_ISQ_ISQ0_SHIFT	0
/**@}*/

/* ADC_IDATA Values -----------------------------------------------------------*/
/** @defgroup adc_idata IDATA ADC Inserted data registers 0-3
@{*/
/**@}*/

/* ADC_RDATA Values -----------------------------------------------------------*/
/** @defgroup adc_rdata RDATA ADC Inserted data registers 0-3
@{*/
/**@}*/

/* ADC_OVSAMPCTL Values -----------------------------------------------------------*/
/** @defgroup adc_ovsampctl OVSAMPCTL ADC Inserted data registers 0-3
@{*/
/** TOVS: Triggered oversampling **/
#define ADC_OVSAMPCTL_TOVS	(1<<9)

#define ADC_OVSAMPCTL_OVSS_SHIFT	5
#define ADC_OVSAMPCTL_OVSS_MASK		0x0F
#define ADC_OVSAMPCTL_OVSS		(ADC_OVSAMPCTL_OVSS_MASK << ADC_OVSAMPCTL_OVSS_SHIFT)
/** OVSS: Oversampling shift, no more than 8 **/
#define ADC_OVSAMPCTL_OVSS_VAL(X)	((x) << ADC_OVSAMPCTL_OVSS_SHIFT)

#define ADC_OVSAMPCTL_OVSR_SHIFT	2
#define ADC_OVSAMPCTL_OVSR_MASK		0x07
#define ADC_OVSAMPCTL_OVSR		(ADC_OVSAMPCTL_OVSR_MASK << ADC_OVSAMPCTL_OVSR_SHIFT)
/** OVSR: Oversampling ratio **/
#define ADC_OVSAMPCTL_OVSR_2x		(0 << ADC_OVSAMPCTL_OVSR_SHIFT)
#define ADC_OVSAMPCTL_OVSR_4x		(1 << ADC_OVSAMPCTL_OVSR_SHIFT)
#define ADC_OVSAMPCTL_OVSR_8x		(2 << ADC_OVSAMPCTL_OVSR_SHIFT)
#define ADC_OVSAMPCTL_OVSR_16x		(3 << ADC_OVSAMPCTL_OVSR_SHIFT)
#define ADC_OVSAMPCTL_OVSR_32x		(4 << ADC_OVSAMPCTL_OVSR_SHIFT)
#define ADC_OVSAMPCTL_OVSR_64x		(5 << ADC_OVSAMPCTL_OVSR_SHIFT)
#define ADC_OVSAMPCTL_OVSR_128x		(6 << ADC_OVSAMPCTL_OVSR_SHIFT)
#define ADC_OVSAMPCTL_OVSR_256x		(7 << ADC_OVSAMPCTL_OVSR_SHIFT)

/** OVSEN: Oversampling enable **/
#define ADC_OVSAMPCTL_OVSEN (1<<0)
/**@}*/

/* --- Function prototypes ------------------------------------------------- */

BEGIN_DECLS

void adc_power_on_async(uint32_t adc);
void adc_power_on(uint32_t adc);
bool adc_is_power_on(uint32_t adc);
void adc_power_off_async(uint32_t adc);
void adc_power_off(uint32_t adc);
bool adc_is_power_off(uint32_t adc);
void adc_calibrate_async(uint32_t adc);
bool adc_is_calibrating(uint32_t adc);
void adc_calibrate(uint32_t adc);
void adc_reset_calibration(uint32_t adc);
void adc_set_continuous_conversion_mode(uint32_t adc);
void adc_set_single_conversion_mode(uint32_t adc);
void adc_set_regular_sequence(uint32_t adc, uint8_t length, const uint8_t channel[]);
void adc_set_inserted_sequence(uint32_t adc, uint8_t length, const uint8_t channel[]);
void adc_set_sample_time_on_channel(uint32_t adc, uint8_t channel, uint8_t time);
void adc_enable_automatic_inserted_group_conversion(uint32_t adc);
void adc_disable_automatic_inserted_group_conversion(uint32_t adc);
void adc_set_inserted_offset(uint32_t adc, uint8_t reg, uint32_t offset);
void adc_enable_vref_temperature_sensor(uint32_t adc);
void adc_disable_vref_temperature_sensor(uint32_t adc);
void adc_set_left_aligned(uint32_t adc);
void adc_set_right_aligned(uint32_t adc);
void adc_enable_dma(uint32_t adc);
void adc_disable_dma(uint32_t adc);
bool adc_eoc(uint32_t adc);
bool adc_eos(uint32_t adc);
void adc_enable_eoc_interrupt(uint32_t adc);
void adc_disable_eoc_interrupt(uint32_t adc);
void adc_enable_overrun_interrupt(uint32_t adc);
void adc_disable_overrun_interrupt(uint32_t adc);
bool adc_get_overrun_flag(uint32_t adc);
void adc_clear_overrun_flag(uint32_t adc);
uint32_t adc_read_regular(uint32_t adc);
uint32_t adc_read_inserted(uint32_t adc, uint8_t reg);
void adc_start_conversion_regular(uint32_t adc);
void adc_start_conversion_inserted(uint32_t adc);

END_DECLS

#endif
/** @cond */
#endif
/** @endcond */
/**@}*/
