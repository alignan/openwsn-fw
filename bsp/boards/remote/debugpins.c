/**
 * Author: Xavier Vilajosana (xvilajosana@eecs.berkeley.edu)
 *         Pere Tuset (peretuset@openmote.com)
 * Date:   July 2013
 * Description: CC2538-specific definition of the "debugpins" bsp module.
 */

#include <headers/hw_memmap.h>
#include <headers/hw_types.h>

#include "debugpins.h"
#include "gpio.h"
#include "board.h"

//=========================== defines =========================================
// Board dbPINS defines
#define BSP_PINA_BASE           GPIO_A_BASE

#define BSP_PINA_4              GPIO_PIN_4      //!< PA4 -- frame -RF1.5
#define BSP_PINA_5              GPIO_PIN_5      //!< PA5 -- isr   -RF1.11

#define BSP_PIND_3              GPIO_PIN_3      //!< PD3 -- slot  -RF1.6
#define BSP_PIND_2              GPIO_PIN_2      //!< PD2 -- fsm   -RF1.8
#define BSP_PIND_1              GPIO_PIN_1      //!< PD1 -- task  -RF1.10
#define BSP_PIND_0              GPIO_PIN_0      //!< PD0 -- radio -RF1-12

//=========================== variables =======================================

//=========================== prototypes ======================================

void bspDBpinToggle(uint32_t base,uint8_t ui8Pin);

//=========================== public ==========================================

void debugpins_init() {
   /* FIXME */
}

void debugpins_frame_toggle() {
   /* FIXME */
}
void debugpins_frame_clr() {
   /* FIXME */
}
void debugpins_frame_set() {
   /* FIXME */
}

void debugpins_slot_toggle() {
   /* FIXME */
}
void debugpins_slot_clr() {
   /* FIXME */
}
void debugpins_slot_set() {
   /* FIXME */
}

void debugpins_fsm_toggle() {
   /* FIXME */
}
void debugpins_fsm_clr() {
   /* FIXME */
}
void debugpins_fsm_set() {
   /* FIXME */
}

void debugpins_task_toggle() {
   /* FIXME */
}
void debugpins_task_clr() {
   /* FIXME */
}
void debugpins_task_set() {
   /* FIXME */
}

void debugpins_isr_toggle() {
   /* FIXME */
}
void debugpins_isr_clr() {
   /* FIXME */
}
void debugpins_isr_set() {
   /* FIXME */
}

void debugpins_radio_toggle() {
   /* FIXME */
}
void debugpins_radio_clr() {
   /* FIXME */
}
void debugpins_radio_set() {
   /* FIXME */
}

//------------ private ------------//

void bspDBpinToggle(uint32_t base, uint8_t ui8Pin)
{
    //
    // Get current pin values of selected bits
    //
    uint32_t ui32Toggle = GPIOPinRead(base, ui8Pin);

    //
    // Invert selected bits
    //
    ui32Toggle = (~ui32Toggle) & ui8Pin;

    //
    // Set GPIO
    //
    GPIOPinWrite(base, ui8Pin, ui32Toggle);
}
