/** @defgroup adc_defines ADC Defines
 *
 * @brief <b>Defined Constants and Types for the STM32F0xx Analog to Digital
 * Converter</b>
 *
 * @ingroup STM32F0xx_defines
 *
 * @version 1.0.0
 *
 * @date 11 July 2013
 *
 * LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2013 Frantisek Burian <BuFran@seznam.cz>
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

#ifndef LIBOPENCM3_ADC_H
#define LIBOPENCM3_ADC_H

#include <libopencm3/gd32/common/adc_common.h>

/*****************************************************************************/
/* Module definitions                                                        */
/*****************************************************************************/

/** @defgroup adc_reg_base ADC register base addresses
 * @ingroup adc_defines
 *
 *@{*/
#define ADC				ADC_BASE
#define ADC0				ADC_BASE/* for API compatibility */
/**@}*/

/*****************************************************************************/
/* Register definitions                                                      */
/*****************************************************************************/

#define ADC0_STAT			ADC_STAT(ADC)
#define ADC0_CTL0			ADC_CTL0(ADC)
#define ADC0_CTL1			ADC_CTL1(ADC)
#define ADC0_SAMPT0			ADC_SAMPT0(ADC)
#define ADC0_SAMPT1			ADC_SAMPT1(ADC)
#define ADC0_IOFF0			ADC_IOFF0(ADC)
#define ADC0_IOFF1			ADC_IOFF1(ADC)
#define ADC0_IOFF2			ADC_IOFF2(ADC)
#define ADC0_IOFF3			ADC_IOFF3(ADC)
#define ADC0_WDHT			ADC_WDHT(ADC)
#define ADC0_WDLT			ADC_WDLT(ADC)
#define ADC0_RSQ0			ADC_RSQ0(ADC)
#define ADC0_RSQ1			ADC_RSQ1(ADC)
#define ADC0_RSQ2			ADC_RSQ2(ADC)
#define ADC0_ISQ			ADC_ISQ(ADC)
#define ADC0_IDATA0			ADC_IDATA0(ADC)
#define ADC0_IDATA1			ADC_IDATA1(ADC)
#define ADC0_IDATA2			ADC_IDATA2(ADC)
#define ADC0_IDATA3			ADC_IDATA3(ADC)
#define ADC0_RDATA			ADC_RDATA(ADC)
#define ADC0_OVSAMPCTL			ADC_OVSAMPCTL(ADC)

/*****************************************************************************/
/* API definitions                                                           */
/*****************************************************************************/

/** @defgroup adc_api_opmode ADC Operation Modes
 * @ingroup adc_defines
 *
 *@{*/
enum adc_opmode {
    ADC_MODE_SINGLE,
    ADC_MODE_CONTINUOUS,
    ADC_MODE_SCAN,
    ADC_MODE_SCAN_CONTINUOUS,
};
/**@}*/

/*****************************************************************************/
/* API Functions                                                             */
/*****************************************************************************/

BEGIN_DECLS

/* Operation mode API */
void adc_enable_regular_discontinuous_mode(uint32_t adc, uint8_t length);
void adc_disable_regular_discontinuous_mode(uint32_t adc);
void adc_enable_inserted_discontinuous_mode(uint32_t adc);
void adc_disable_inserted_discontinuous_mode(uint32_t adc);
void adc_set_operation_mode(uint32_t adc, enum adc_opmode opmode);

/* Trigger setup */
void adc_enable_external_trigger_regular(uint32_t adc, uint32_t trigger);
void adc_disable_external_trigger_regular(uint32_t adc);
void adc_enable_external_trigger_inserted(uint32_t adc, uint32_t trigger);
void adc_disable_external_trigger_inserted(uint32_t adc);

/* Interrupt configuration */
void adc_enable_watchdog_interrupt(uint32_t adc);
void adc_disable_watchdog_interrupt(uint32_t adc);
bool adc_get_watchdog_flag(uint32_t adc);
void adc_clear_watchdog_flag(uint32_t adc);

void adc_enable_eoc_sequence_interrupt(uint32_t adc);
void adc_disable_eoc_sequence_interrupt(uint32_t adc);
bool adc_get_eoc_sequence_flag(uint32_t adc);
void adc_clear_eoc_sequence_flag(uint32_t adc);

void adc_enable_eoic_sequence_interrupt(uint32_t adc);
void adc_disable_eoic_sequence_interrupt(uint32_t adc);
bool adc_get_eoic_sequence_flag(uint32_t adc);
void adc_clear_eoic_sequence_flag(uint32_t adc);

bool adc_get_strc_flag(uint32_t adc);
void adc_clear_strc_flag(uint32_t adc);

bool adc_get_stic_flag(uint32_t adc);
void adc_clear_stic_flag(uint32_t adc);

/* Basic configuration */
void adc_enable_vbat_sensor(uint32_t adc);
void adc_disable_vbat_sensor(uint32_t adc);
void adc_calibrate_start(uint32_t adc)
	LIBOPENCM3_DEPRECATED("see adc_calibrate/_async");
void adc_calibrate_wait_finish(uint32_t adc)
	LIBOPENCM3_DEPRECATED("see adc_is_calibrating");

/* Analog Watchdog */
void adc_enable_analog_watchdog_on_selected_channel(uint32_t adc, uint8_t chan);
void adc_disable_analog_watchdog(uint32_t adc);
void adc_set_watchdog_high_threshold(uint32_t adc, uint16_t threshold);
void adc_set_watchdog_low_threshold(uint32_t adc, uint16_t threshold);

END_DECLS

#endif
