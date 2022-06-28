/** @addtogroup adc_file ADC peripheral API
 * @ingroup peripheral_apis
 *
 * based on F3 file
 *
 * @date 14 July 2013
 *
 * LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2012 Ken Sarkies <ksarkies@internode.on.net>
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

#include <libopencm3/cm3/assert.h>
#include <libopencm3/gd32/adc.h>

/**@{*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @defgroup adc_api_opmode ADC Operation mode API
 * @ingroup adc_file
 *
 * @brief ADC Result API
 *
 *@{*/

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable Discontinuous Mode for Regular Conversions

In this mode the ADC converts, on each trigger, a subgroup of up to 8 of the
defined regular channel group. The subgroup is defined by the number of
consecutive channels to be converted. After a subgroup has been converted
the next trigger will start conversion of the immediately following subgroup
of the same length or until the whole group has all been converted. When the
the whole group has been converted, the next trigger will restart conversion
of the subgroup at the beginning of the whole group.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
@param[in] length Unsigned int8. Number of channels in the group @ref
adc_cr1_discnum
*/

void adc_enable_regular_discontinuous_mode(uint32_t adc, uint8_t length)
{
    if ((length-1) > 7) {
	    return;
    }
    ADC_CTL0(adc) |= ADC_CTL0_DISRC;
    ADC_CTL0(adc) &= ~ADC_CTL0_DISNUM;
    ADC_CTL0(adc) |= ADC_CTL0_DISNUM_VAL(length-1);
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable Discontinuous Mode for Regular Conversions
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_disable_regular_discontinuous_mode(uint32_t adc)
{
    ADC_CTL0(adc) &= ~ADC_CTL0_DISRC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable Discontinuous Mode for Regular Conversions
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_enable_inserted_discontinuous_mode(uint32_t adc)
{
    ADC_CTL0(adc) |= ADC_CTL0_DISIC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable Discontinuous Mode for Regular Conversions
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_disable_inserted_discontinuous_mode(uint32_t adc)
{
    ADC_CTL0(adc) &= ~ADC_CTL0_DISIC;
}

/*---------------------------------------------------------------------------*/
/** ADC Set operation mode
 *
 * There are some operation modes, common for entire stm32 branch. In the text
 * the braces are describing result to single trigger event. The trigger event
 * is described by character T in the description. The ADC is configured to
 * convert list of inputs [0, 1, 2, 3]. In Grouped modes, there is used group
 * size of 2 conversions in the examples
 *
 * @li @c ADC_MODE_SEQUENTIAL:  T(0) T(1) T(2) T(3)[EOC] T(0) T(1) T(2) ...
 *
 *  In this mode, after the trigger event a single channel is converted and the
 *  next channel in the list is prepared to convert on next trigger edge.
 *
 *  @note This mode can be emulated by ADC_MODE_GROUPED with group size
 *  of 1.
 *
 * @li @c ADC_MODE_SCAN:        T(0123)[EOC] T(0123)[EOC] T(0123)[EOC]
 *
 *  In this mode, after the trigger event, all channels will be converted once,
 *  storing results sequentially.
 *
 *  @note The DMA must be configured properly for more than single channel to
 *  convert.
 *
 * @li @c ADC_MODE_SCAN_INFINITE: T(0123[EOC]0123[EOC]0123[EOC]...)
 *
 *  In this mode, after the trigger event, all channels from the list are
 *  converted. At the end of list, the conversion continues from the beginning.
 *
 *  @note The DMA must be configured properly to operate in this mode.@par
 *
 * @li @c ADC_MODE_GROUPED:     T(12) T(34)[EOC] T(12) T(34)[EOC] T(12)
 *
 *  In this mode, after the trigger event, a specified group size of channels
 *  are converted. If the end of channel list occurs, the EOC is generated
 *  and on the next trigger it wraps to the beginning.
 *
 *  @note The DMA must be configured properly to operate on more than single
 *  channel conversion groups.
 *
 * @warning not all families supports all modes of operation of ADC.
 *
 */

/*---------------------------------------------------------------------------*/
/** @brief ADC Set conversion operation mode
 *
 * @note on SEQUENTIAL mode, the trigger event is necessary to start conversion.
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] opmode ADC operation mode
 */

void adc_set_operation_mode(uint32_t adc, enum adc_opmode opmode)
{
    switch (opmode) {
	case ADC_MODE_SINGLE:
	    ADC_CTL0(adc) &= ~(ADC_CTL0_DISIC | ADC_CTL0_DISRC | ADC_CTL0_SM);
	    ADC_CTL1(adc) &= ~(ADC_CTL1_CTN);
	    break;
	case ADC_MODE_CONTINUOUS:
	    ADC_CTL0(adc) &= ~(ADC_CTL0_DISIC | ADC_CTL0_DISRC | ADC_CTL0_SM);
	    ADC_CTL1(adc) |= ADC_CTL1_CTN;
	    break;
	case ADC_MODE_SCAN:
	    ADC_CTL0(adc) &= ~(ADC_CTL0_DISIC | ADC_CTL0_DISRC);
	    ADC_CTL0(adc) |= ADC_CTL0_SM;
	    ADC_CTL1(adc) &= ~ADC_CTL1_CTN;
	    break;
	case ADC_MODE_SCAN_CONTINUOUS:
	    ADC_CTL0(adc) &= ~(ADC_CTL0_DISIC | ADC_CTL0_DISRC);
	    ADC_CTL0(adc) |= ADC_CTL0_SM;
	    ADC_CTL1(adc) |= ADC_CTL1_CTN;
	    break;
    }
}

/**@}*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @defgroup adc_api_trigger ADC Trigger API
 * @ingroup adc_file
 *
 * @brief ADC Trigger API
 *
 *@{*/

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable an External Trigger for Regular Channels
 *
 * This enables an external trigger for set of defined regular channels
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] trigger Unsigned int32. Trigger identifier
 * @ref adc_trigger_regular
 */

void adc_enable_external_trigger_regular(uint32_t adc, uint32_t trigger)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_ETSRC_MASK;
    ADC_CTL1(adc) |= trigger & ADC_CTL1_ETSRC_MASK;
    ADC_CTL1(adc) |= ADC_CTL1_ETERC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable an External Trigger for Regular Channels
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_disable_external_trigger_regular(uint32_t adc)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_ETERC;
    ADC_CTL1(adc) &= ~ADC_CTL1_ETSRC_MASK;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable an External Trigger for Inserted Channels
 *
 * This enables an external trigger for set of defined inserted channels
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] trigger Unsigned int32. Trigger identifier
 * @ref adc_trigger_inserted
 */

void adc_enable_external_trigger_inserted(uint32_t adc, uint32_t trigger)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_ETSIC_MASK;
    ADC_CTL1(adc) |= trigger & ADC_CTL1_ETSIC_MASK;
    ADC_CTL1(adc) |= ADC_CTL1_ETEIC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable an External Trigger for Regular Channels
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_disable_external_trigger_inserted(uint32_t adc)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_ETEIC;
    ADC_CTL1(adc) &= ~ADC_CTL1_ETSIC_MASK;
}

/**@}*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @defgroup adc_api_interrupts ADC Interrupt configuration API
 * @ingroup adc_file
 *
 * @brief ADC Interrupt configuration API
 *
 *@{*/

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable Analog Watchdog Interrupt
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_enable_watchdog_interrupt(uint32_t adc)
{
	ADC_CTL0(adc) |= ADC_CTL0_WDEIE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable Regular End-Of-Conversion Interrupt
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_disable_watchdog_interrupt(uint32_t adc)
{
	ADC_CTL0(adc) &= ~ADC_CTL0_WDEIE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Read the Analog Watchdog Flag
 *
 * This flag is set when the converted voltage crosses the high or low
 * thresholds.
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @returns bool true, if the signal is out of defined analog range.
 */

bool adc_get_watchdog_flag(uint32_t adc)
{
	return ADC_STAT(adc) & ADC_STAT_WDE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Clear Analog Watchdog Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_clear_watchdog_flag(uint32_t adc)
{
	ADC_STAT(adc) &= ~ADC_STAT_WDE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable Regular End-Of-Conversion Sequence Interrupt
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_enable_eoc_sequence_interrupt(uint32_t adc)
{
	ADC_CTL0(adc) |= ADC_CTL0_EOCIE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable Regular End-Of-Conversion Sequence Interrupt
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_disable_eoc_sequence_interrupt(uint32_t adc)
{
	ADC_CTL0(adc) &= ~ADC_CTL0_EOCIE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Read the Regular End-Of-Conversion Sequence Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

bool adc_get_eoc_sequence_flag(uint32_t adc)
{
	return ADC_STAT(adc) & ADC_STAT_EOC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Clear Regular End-Of-Conversion Sequence Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_clear_eoc_sequence_flag(uint32_t adc)
{
	ADC_STAT(adc) = ADC_STAT_EOC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable Inserted End-Of-Conversion Sequence Interrupt
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_enable_eoic_sequence_interrupt(uint32_t adc)
{
	ADC_CTL0(adc) |= ADC_CTL0_EOICIE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable Inserted End-Of-Conversion Sequence Interrupt
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_disable_eoic_sequence_interrupt(uint32_t adc)
{
	ADC_CTL0(adc) &= ~ADC_CTL0_EOICIE;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Read the Inserted End-Of-Conversion Sequence Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

bool adc_get_eoic_sequence_flag(uint32_t adc)
{
	return ADC_STAT(adc) & ADC_STAT_EOIC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Clear Inserted End-Of-Conversion Sequence Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_clear_eoic_sequence_flag(uint32_t adc)
{
	ADC_STAT(adc) &= ~ADC_STAT_EOIC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Read the Start Of Regular Conversion Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

bool adc_get_strc_flag(uint32_t adc)
{
	return ADC_STAT(adc) & ADC_STAT_STRC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Clear the Start Of Regular Conversion Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_clear_strc_flag(uint32_t adc)
{
	ADC_STAT(adc) &= ~ADC_STAT_STRC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Read the Start Of Inserted Conversion Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

bool adc_get_stic_flag(uint32_t adc)
{
	return ADC_STAT(adc) & ADC_STAT_STIC;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Clear the Start Of Inserted Conversion Flag
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_clear_stic_flag(uint32_t adc)
{
	ADC_STAT(adc) &= ~ADC_STAT_STIC;
}

/**@}*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @defgroup adc_api_config ADC Basic configuration API
 * @ingroup adc_file
 *
 * @brief ADC Basic configuration API
 *
 *@{*/

/*---------------------------------------------------------------------------*/
/** @brief ADC Set a Regular Channel Conversion Sequence
 *
 * Define a sequence of channels to be converted as a regular group with a
 * length from 1 to 18 channels. If this is called during conversion, the
 * current conversion is reset and conversion begins again with the newly
 * defined group.
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] length Unsigned int8. Number of channels in the group.
 * @param[in] channel Unsigned int8[]. Set of channels to convert, integers
 * 0..18.
 */

void adc_set_regular_sequence(uint32_t adc, uint8_t length, const uint8_t channel[])
{
    ADC_RSQ0(adc) &= ~ADC_RSQ0_RL_MASK;
    ADC_RSQ0(adc) |= ADC_RSQ0_RL_VAL(length) & ADC_RSQ0_RL_MASK;
    if (length == 0) {
	return;
    }
    if (length > 0) {
	ADC_RSQ2(adc) |= channel[0] << ADC_RSQ2_RSQ0_SHIFT;
    }
    if (length > 1) {
	ADC_RSQ2(adc) |= channel[1] << ADC_RSQ2_RSQ1_SHIFT;
    }
    if (length > 2) {
	ADC_RSQ2(adc) |= channel[2] << ADC_RSQ2_RSQ2_SHIFT;
    }
    if (length > 3) {
	ADC_RSQ2(adc) |= channel[3] << ADC_RSQ2_RSQ3_SHIFT;
    }
    if (length > 4) {
	ADC_RSQ2(adc) |= channel[4] << ADC_RSQ2_RSQ4_SHIFT;
    }
    if (length > 5) {
	ADC_RSQ2(adc) |= channel[5] << ADC_RSQ2_RSQ5_SHIFT;
    }
    if (length > 6) {
	ADC_RSQ1(adc) |= channel[6] << ADC_RSQ1_RSQ6_SHIFT;
    }
    if (length > 7) {
	ADC_RSQ1(adc) |= channel[7] << ADC_RSQ1_RSQ7_SHIFT;
    }
    if (length > 8) {
	ADC_RSQ1(adc) |= channel[8] << ADC_RSQ1_RSQ8_SHIFT;
    }
    if (length > 9) {
	ADC_RSQ1(adc) |= channel[9] << ADC_RSQ1_RSQ9_SHIFT;
    }
    if (length > 10) {
	ADC_RSQ1(adc) |= channel[10] << ADC_RSQ1_RSQ10_SHIFT;
    }
    if (length > 11) {
	ADC_RSQ1(adc) |= channel[11] << ADC_RSQ1_RSQ11_SHIFT;
    }
    if (length > 12) {
	ADC_RSQ0(adc) |= channel[12] << ADC_RSQ0_RSQ12_SHIFT;
    }
    if (length > 13) {
	ADC_RSQ0(adc) |= channel[13] << ADC_RSQ0_RSQ13_SHIFT;
    }
    if (length > 14) {
	ADC_RSQ0(adc) |= channel[14] << ADC_RSQ0_RSQ14_SHIFT;
    }
    if (length > 15) {
	ADC_RSQ0(adc) |= channel[15] << ADC_RSQ0_RSQ15_SHIFT;
    }
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Set a Inserted Channel Conversion Sequence
 *
 * Define a sequence of channels to be converted as a inserted group with a
 * length from 1 to 18 channels. If this is called during conversion, the
 * current conversion is reset and conversion begins again with the newly
 * defined group.
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] length Unsigned int8. Number of channels in the group.
 * @param[in] channel Unsigned int8[]. Set of channels to convert, integers
 * 0..18.
 */

void adc_set_inserted_sequence(uint32_t adc, uint8_t length, const uint8_t channel[])
{
    ADC_ISQ(adc) &= ~ADC_ISQ_IL_MASK;
    ADC_ISQ(adc) |= ADC_ISQ_IL_VAL(length - 1) & ADC_ISQ_IL_MASK;
    if (length == 0) {
	return;
    }
    if (length == 1) {
	ADC_ISQ(adc) |= channel[0] << ADC_ISQ_ISQ3_SHIFT;
    }
    if (length == 2) {
	ADC_ISQ(adc) |= channel[0] << ADC_ISQ_ISQ2_SHIFT;
	ADC_ISQ(adc) |= channel[1] << ADC_ISQ_ISQ3_SHIFT;
    }
    if (length == 3) {
	ADC_ISQ(adc) |= channel[0] << ADC_ISQ_ISQ1_SHIFT;
	ADC_ISQ(adc) |= channel[1] << ADC_ISQ_ISQ2_SHIFT;
	ADC_ISQ(adc) |= channel[2] << ADC_ISQ_ISQ3_SHIFT;
    }
    if (length == 4) {
	ADC_ISQ(adc) |= channel[0] << ADC_ISQ_ISQ0_SHIFT;
	ADC_ISQ(adc) |= channel[1] << ADC_ISQ_ISQ1_SHIFT;
	ADC_ISQ(adc) |= channel[2] << ADC_ISQ_ISQ2_SHIFT;
	ADC_ISQ(adc) |= channel[3] << ADC_ISQ_ISQ3_SHIFT;
    }
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Set the Sample Time for One Channel
 *
 * The sampling time can be selected in ADC clock cycles from 1.5 to 239.5
 * each channel individually
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] channel Unsigned int8. Channel number
 * @param[in] time Unsigned int8. Sampling time selection (@ref adc_api_smptime)
 */

void adc_set_sample_time_on_channel(uint32_t adc, uint8_t channel, uint8_t time)
{
    if (channel < 10) {
	ADC_SAMPT1(adc) &= ADC_SAMPT_MASK << ADC_SAMPT1_SPT_SHIFT(channel);
	ADC_SAMPT1(adc) |= (time & ADC_SAMPT_MASK) << ADC_SAMPT1_SPT_SHIFT(channel);
    } else if (channel < 18) {
	ADC_SAMPT0(adc) &= ADC_SAMPT_MASK << ADC_SAMPT0_SPT_SHIFT(channel);
	ADC_SAMPT0(adc) |= (time & ADC_SAMPT_MASK) << ADC_SAMPT0_SPT_SHIFT(channel);
    }
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable The VBat Sensor
 *
 * This enables the battery voltage measurements on channel 17.
 */

void adc_enable_vbat_sensor(uint32_t adc)
{
    ADC_CTL1(adc) |= ADC_CTL1_VBATEN;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable The VBat Sensor
 *
 * Disabling this will reduce power consumption from the battery voltage
 * measurement.
 */

void adc_disable_vbat_sensor(uint32_t adc)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_VBATEN;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Start the calibration procedure
 * @deprecated Replaced by adc_calibrate/_async/is_calibrating
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_calibrate_start(uint32_t adc)
{
    ADC_CTL1(adc) |= ADC_CTL1_RSTCLB; /* optional, but so we can call this
				       * thing repeatedly */
    while (ADC_CTL1(adc) & ADC_CTL1_RSTCLB) /* wait for end of calibration
					     * reset */
	{ }

    ADC_CTL1(adc) |= ADC_CTL1_CLB;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Wait to finish the ADC calibration procedure
 * @deprecated Replaced by adc_calibrate/_async/is_calibrating
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */

void adc_calibrate_wait_finish(uint32_t adc)
{
    while (ADC_CTL1(adc) & ADC_CTL1_CLB)
	{ }
}

//--------------------------------------------------
void adc_reset_calibration(uint32_t adc)
{
    ADC_CTL1(adc) |= ADC_CTL1_RSTCLB;
}
/**@}*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @defgroup adc_api_wdg ADC Analog watchdog API
 * @ingroup adc_file
 *
 * @brief ADC analog watchdog API definitions.
 *
 * The analog watchdog allows the monitoring of an analog signal between two
 * threshold levels. The thresholds must be preset. Analog watchdog is disabled
 * by default.
 *
 * @warning Comparison is done before data alignment takes place, so the
 * thresholds are left-aligned.
 *
 * Example 1: Enable watchdog checking on all channels
 *
 * @code
 * // in configuration
 * adc_enable_analog_watchdog_on_all_channels(ADC1);
 * adc_set_watchdog_high_threshold(ADC1, 0xE00);
 * adc_set_watchdog_low_threshold(ADC1, 0x200);
 *
 * // in the main application thread
 * if (adc_get_watchdog_flag(ADC1)) {
 *     // the converted signal is out of AWD ranges
 *     adc_clear_watchdog_flag(ADC1);
 * }
 * @endcode
 *
 * Example 2: Enable watchdog checking on channel 5
 *
 * @code
 * // in configuration
 * adc_enable_analog_watchdog_on_selected_channel(ADC1,5);
 * adc_set_watchdog_high_threshold(ADC1, 0xE00);
 * adc_set_watchdog_low_threshold(ADC1, 0x200);
 *
 * // in the main application thread
 * if (adc_get_watchdog_flag(ADC1)) {
 *     // the converted signal is out of AWD ranges
 *     adc_clear_watchdog_flag(ADC1);
 * }
 * @endcode
 *@{*/

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable Analog Watchdog for a Selected Channel
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] chan Unsigned int8. ADC channel number @ref adc_api_channel
 */

void adc_enable_analog_watchdog_on_selected_channel(uint32_t adc, uint8_t channel)
{
    ADC_CTL0(adc) &= ~ADC_CTL0_WDCHSEL_MASK;
    ADC_CTL0(adc) |= (ADC_CTL0_WDCHSEL_VAL(channel) & ADC_CTL0_WDCHSEL_MASK);
    ADC_CTL0(adc) |= ADC_CTL0_RWDEN | ADC_CTL0_IWDEN;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable Analog Watchdog
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 */
void adc_disable_analog_watchdog(uint32_t adc)
{
    ADC_CTL0(adc) &= ~(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN);
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Set Analog Watchdog Upper Threshold
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] threshold Upper threshold value
 */

void adc_set_watchdog_high_threshold(uint32_t adc, uint16_t threshold)
{
	ADC_WDHT(adc) = threshold & ~ADC_WDHT_MASK;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Set Analog Watchdog Lower Threshold
 *
 * @param[in] adc Unsigned int32. ADC base address (@ref adc_reg_base)
 * @param[in] threshold Lower threshold value
 */

void adc_set_watchdog_low_threshold(uint32_t adc, uint16_t threshold)
{
	ADC_WDLT(adc) = threshold & ~ADC_WDLT_MASK;
}

/**@}*/

/*---------------------------------------------------------------------------*/

/**@}*/
