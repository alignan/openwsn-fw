/**
 * Author: Xavier Vilajosana (xvilajosana@eecs.berkeley.edu)
 *         Pere Tuset (peretuset@openmote.com)
 * Modified: Antonio Lignan (antonio.lignan@gmail.com)
 * Date: March 2016
 * Description: CC2538-specific definition of the "leds" bsp module.
 */

#include <headers/hw_memmap.h>
#include <headers/hw_types.h>

#include "stdint.h"
#include "leds.h"
#include "gpio.h"
#include "board.h"
#include "board_info.h"


// Board LED defines
#define BSP_LED_BASE            LEDS_BASE_CONF
#define BSP_LED_1               LEDS_RED_PIN_CONF
#define BSP_LED_2               LEDS_BLUE_PIN_CONF
#define BSP_LED_3               LEDS_GREEN_PIN_CONF

#define BSP_LED_ALL             (BSP_LED_1 | \
                                 BSP_LED_2 | \
                                 BSP_LED_3)

//=========================== defines =========================================

//=========================== variables =======================================

//=========================== prototypes ======================================

void bspLedSet(uint8_t ui8Leds);
void bspLedClear(uint8_t ui8Leds);
void bspLedToggle(uint8_t ui8Leds);

//=========================== public ==========================================

void leds_init() {
    GPIOPinTypeGPIOOutput(BSP_LED_BASE, BSP_LED_ALL);
	GPIOPinWrite(BSP_LED_BASE, BSP_LED_ALL, 0);
}

void    leds_error_on() {
	bspLedSet(BSP_LED_1);
}
void    leds_error_off() {
	bspLedClear(BSP_LED_1);
}
void    leds_error_toggle() {
	bspLedToggle(BSP_LED_1);
}
uint8_t leds_error_isOn() {
	  uint32_t ui32Toggle = GPIOPinRead(BSP_LED_BASE, BSP_LED_1);
	  return (uint8_t)(ui32Toggle & BSP_LED_1)>>4;
}


void    leds_sync_on() {
	bspLedSet(BSP_LED_2);
}
void    leds_sync_off() {
	bspLedClear(BSP_LED_2);
}
void    leds_sync_toggle() {
	bspLedToggle(BSP_LED_2);
}
uint8_t leds_sync_isOn() {
	uint32_t ui32Toggle = GPIOPinRead(BSP_LED_BASE, BSP_LED_2);
    return (uint8_t)(ui32Toggle & BSP_LED_2)>>5;
}


void    leds_radio_on() {
	bspLedSet(BSP_LED_3);
}
void    leds_radio_off() {
	bspLedClear(BSP_LED_3);
}
void    leds_radio_toggle() {
	bspLedToggle(BSP_LED_3);
}
uint8_t leds_radio_isOn() {
	uint32_t ui32Toggle = GPIOPinRead(BSP_LED_BASE, BSP_LED_3);
	return (uint8_t)(ui32Toggle & BSP_LED_3)>>7;
}

void    leds_debug_on() {
	bspLedSet(BSP_LED_3);
}
void    leds_debug_off() {
	bspLedClear(BSP_LED_3);
}
void    leds_debug_toggle() {
	bspLedToggle(BSP_LED_3);
}
uint8_t leds_debug_isOn() {
	uint32_t ui32Toggle = GPIOPinRead(BSP_LED_BASE, BSP_LED_3);
	return (uint8_t)(ui32Toggle & BSP_LED_3)>>7;
}

// all
void leds_all_on() {
	bspLedSet(BSP_LED_ALL);
}
void leds_all_off() {
	bspLedClear(BSP_LED_ALL);
}
void leds_all_toggle() {
	bspLedToggle(BSP_LED_ALL);
}

void leds_error_blink() {
   uint8_t i;
   volatile uint16_t delay;
   
   // turn all LEDs off
   bspLedClear(BSP_LED_ALL);
     
   // blink error LED for ~10s
   for (i=0;i<80;i++) {
	  bspLedToggle(BSP_LED_1);
      for (delay=0xffff;delay>0;delay--);
      for (delay=0xffff;delay>0;delay--);
   }
}

void leds_circular_shift() {
}

void leds_increment() {
}

//=========================== private =========================================

port_INLINE void bspLedSet(uint8_t ui8Leds)
{
    //
    // Turn on specified LEDs
    //
    GPIOPinWrite(BSP_LED_BASE, ui8Leds, ui8Leds);
}

port_INLINE void bspLedClear(uint8_t ui8Leds)
{
    //
    // Turn off specified LEDs
    //
    GPIOPinWrite(BSP_LED_BASE, ui8Leds, 0);
}

port_INLINE void bspLedToggle(uint8_t ui8Leds)
{
    //
    // Get current pin values of selected bits
    //
    uint32_t ui32Toggle = GPIOPinRead(BSP_LED_BASE, ui8Leds);

    //
    // Invert selected bits
    //
    ui32Toggle = (~ui32Toggle) & ui8Leds;

    //
    // Set GPIO
    //
    GPIOPinWrite(BSP_LED_BASE, ui8Leds, ui32Toggle);
}

