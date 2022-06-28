/** @addtogroup adc_file ADC peripheral API
@ingroup peripheral_apis

@author @htmlonly &copy; @endhtmlonly
2009 Edward Cheeseman <evbuilder@users.sourceforge.net>
@author @htmlonly &copy; @endhtmlonly
2012 Ken Sarkies <ksarkies@internode.on.net>
@author @htmlonly &copy; @endhtmlonly
2014 Karl Palsson <karlp@tweak.net.au>

This library supports one style of the Analog to Digital Conversion System in
the STM32 series of ARM Cortex Microcontrollers by ST Microelectronics.

The style of ADC Peripheral supported by this code is found in the F1, F2,
F37x, F38x, F4, and L1 series devices (at the time of writing) but is quite
different to the style found on the F0 and F30x and F31x.
Devices can have up to three A/D converters each with their own set of
registers.
However all the A/D converters share a common clock.  On most devices, this is
prescaled from the APB2 clock by default by a minimum factor of 2 to a maximum
of 8, though on the L1 this is always a divider from the HSI. (And therefore HSI
_must_ be enabled before attempting to enable the ADC)

Each A/D converter has up to ADC_MAX_CHANNELS channels:
@li On ADC1 the analog channels 16 and 17 are internally connected to the
temperature sensor and V<sub>REFINT</sub>, respectively.
@li On ADC2 (if available) the analog channels 16 and 17 are internally
connected to V<sub>SS</sub>.
@li On ADC3 (if available) the analog channels 9, 14, 15, 16 and 17 are
internally connected to V<sub>SS</sub>.

The conversions can occur as a one-off conversion whereby the process stops once
conversion is complete. The conversions can also be continuous wherein a new
conversion starts immediately the previous conversion has ended.

Conversion can occur as a single channel conversion or a scan of a group of
channels in either continuous or one-off mode. If more than one channel is
converted in a scan group, DMA must be used to transfer the data as there is
only one result register available. An interrupt can be set to occur at the end
of conversion, which occurs after all channels have been scanned.

A discontinuous mode allows a subgroup of group of a channels to be converted in
bursts of a given length.

Injected conversions allow a second group of channels to be converted separately
from the regular group. An interrupt can be set to occur at the end of
conversion, which occurs after all channels have been scanned.

@section adc_api_ex Basic ADC Handling API.

Example 1: Simple single channel conversion polled. Enable the peripheral clock
and ADC, reset ADC and set the prescaler divider. Set dual mode to independent
(default). Enable triggering for a software trigger.

@code
    rcc_periph_clock_enable(RCC_ADC1);
    adc_power_off(ADC1);
    rcc_periph_reset_pulse(RST_ADC1);
    rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV2);
    adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
    adc_disable_scan_mode(ADC1);
    adc_set_single_conversion_mode(ADC1);
    adc_set_sample_time(ADC1, ADC_CHANNEL0, ADC_SMPR1_SMP_1DOT5CYC);
    adc_enable_trigger(ADC1, ADC_CR2_EXTSEL_SWSTART);
    adc_power_on(ADC1);
    adc_reset_calibration(ADC1);
    adc_calibration(ADC1);
    adc_start_conversion_regular(ADC1);
    while (! adc_eoc(ADC1));
    reg16 = adc_read_regular(ADC1);
@endcode

LGPL License Terms @ref lgpl_license
 */

/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2014 Karl Palsson <karlp@tweak.net.au>
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

#include <libopencm3/gd32/adc.h>

/*---------------------------------------------------------------------------*/
/** @brief ADC On

Turn on the ADC.

@param[in] adc Unsigned int32. ADC block register address base @ref
adc_reg_base.
*/

void adc_power_on(uint32_t adc)
{
    ADC_CTL1(adc) |= ADC_CTL1_ADCON;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Off

Turn off the ADC to reduce power consumption to a few microamps.

@param[in] adc Unsigned int32. ADC block register address base @ref
adc_reg_base.
*/

void adc_power_off(uint32_t adc)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_ADCON;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable Automatic Injected Conversions

The ADC converts a defined injected group of channels immediately after the
regular channels have been converted. The external trigger on the injected
channels is disabled as required.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
*/

void adc_enable_automatic_inserted_group_conversion(uint32_t adc)
{
	adc_disable_external_trigger_inserted(adc);
	ADC_CTL0(adc) |= ADC_CTL0_ICA;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable Automatic Injected Conversions

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
*/

void adc_disable_automatic_inserted_group_conversion(uint32_t adc)
{
	ADC_CTL0(adc) &= ~ADC_CTL0_ICA;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Set the Data as Left Aligned

@param[in] adc Unsigned int32. ADC block register address base @ref
adc_reg_base.
*/

void adc_set_left_aligned(uint32_t adc)
{
	ADC_CTL1(adc) |= ADC_CTL1_DAL;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Set the Data as Right Aligned

@param[in] adc Unsigned int32. ADC block register address base @ref
adc_reg_base.
*/

void adc_set_right_aligned(uint32_t adc)
{
	ADC_CTL1(adc) &= ~ADC_CTL1_DAL;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Read from the Regular Conversion Result Register

The result read back is 12 bits, right or left aligned within the first 16 bits.
For ADC1 only, the higher 16 bits will hold the result from ADC2 if
an appropriate dual mode has been set @see adc_set_dual_mode.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
@returns Unsigned int32 conversion result.
*/

uint32_t adc_read_regular(uint32_t adc)
{
    return ADC_RDATA(adc);
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Read from an Inserted Conversion Result Register

The result read back from the selected injected result register (one of four)
is 12 bits, right or left aligned within the first 16 bits. The result can have
a negative value if the injected channel offset has been set @see
adc_set_injected_offset.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
@param[in] reg Unsigned int8. Register number (0 ... 3).
@returns Unsigned int32 conversion result.
*/

uint32_t adc_read_inserted(uint32_t adc, uint8_t reg)
{
	switch (reg) {
	case 0:
		return ADC_IDATA0(adc);
	case 1:
		return ADC_IDATA1(adc);
	case 2:
		return ADC_IDATA2(adc);
	case 3:
		return ADC_IDATA3(adc);
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
/** @brief ADC Set the Inserted Channel Data Offset

This value is subtracted from the injected channel results after conversion is
complete, and can result in negative results. A separate value can be specified
for each injected data register.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
@param[in] reg Unsigned int8. Register number (1 ... 4).
@param[in] offset Unsigned int32.
*/

void adc_set_inserted_offset(uint32_t adc, uint8_t reg, uint32_t offset)
{
    switch (reg) {
	case 0:
	    ADC_IOFF0(adc) = offset;
	    break;
	case 1:
	    ADC_IOFF1(adc) = offset;
	    break;
	case 2:
	    ADC_IOFF2(adc) = offset;
	    break;
	case 3:
	    ADC_IOFF3(adc) = offset;
	    break;
    }
}

//--------------------------------------------------
void adc_enable_vref_temperature_sensor(uint32_t adc)
{
    ADC_CTL1(adc) |= ADC_CTL1_TSVREN;
}

//--------------------------------------------------
void adc_disable_vref_temperature_sensor(uint32_t adc)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_TSVREN;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Software Triggered Conversion on Regular Channels

This starts conversion on a set of defined regular channels if the ADC trigger
is set to be a software trigger. It is cleared by hardware once conversion
starts.

Special F1 Note this is a software trigger and requires triggering to be
enabled and the trigger source to be set appropriately otherwise conversion
will not start. This is not the same as the ADC start conversion operation.

@param[in] adc Unsigned int32. ADC block register address base @ref
adc_reg_base.
*/

void adc_start_conversion_regular(uint32_t adc)
{
    /* Start conversion on regular channels. */
    ADC_CTL1(adc) |= ADC_CTL1_SWRCST;

    /* Wait until the ADC starts the conversion. */
    while (adc_get_strc_flag(adc) == 0);
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Software Triggered Conversion on Injected Channels

This starts conversion on a set of defined injected channels if the ADC trigger
is set to be a software trigger. It is cleared by hardware once conversion
starts.

Special F1 Note this is a software trigger and requires triggering to be
enabled and the trigger source to be set appropriately otherwise conversion
will not start. This is not the same as the ADC start conversion operation.

@param[in] adc Unsigned int32. ADC block register address base @ref
adc_reg_base.
*/

void adc_start_conversion_inserted(uint32_t adc)
{
	/* Start conversion on injected channels. */
	ADC_CTL1(adc) |= ADC_CTL1_SWICST;

	/* Wait until the ADC starts the conversion. */
	while (adc_get_stic_flag(adc) == 0);
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Enable DMA Transfers

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
*/

void adc_enable_dma(uint32_t adc)
{
    ADC_CTL1(adc) |= ADC_CTL1_DMA;
}

/*---------------------------------------------------------------------------*/
/** @brief ADC Disable DMA Transfers

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
*/

void adc_disable_dma(uint32_t adc)
{
    ADC_CTL1(adc) &= ~ADC_CTL1_DMA;
}

/*---------------------------------------------------------------------------*/

/**@}*/
