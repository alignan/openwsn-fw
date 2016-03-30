/**
 * Author: Antonio Lignan (alinan@zolertia.com)
 * Date:   March 2016
 * Description: User button driver file
 */

#include <headers/hw_ioc.h>
#include <headers/hw_memmap.h>
#include <headers/hw_ssi.h>
#include <headers/hw_sys_ctrl.h>
#include <headers/hw_types.h>

#include "board.h"
#include "leds.h"
#include "ioc.h"
#include "gpio.h"
#include "gptimer.h"
#include "sys_ctrl.h"
#include "interrupt.h"
#include "board_info.h"

//=========================== variables =======================================

//=========================== prototypes ======================================

void button_init(void);
static void UserButtonIntHandler(void);
void (*button_int_callback)(uint8_t value);

//=========================== public ==========================================

/**
 * Configures the user button as input source
 */
void button_init(void) {
    volatile uint32_t i;

    /* Delay to avoid pin floating problems */
    for (i = 0xFFFF; i != 0; i--);

    button_int_callback = NULL;

    /* The button is an input GPIO on falling edge */
    GPIOPinTypeGPIOInput(BSP_BUTTON_BASE, BSP_BUTTON_USER);
    IOCPadConfigSet(BSP_BUTTON_BASE, BSP_BUTTON_USER, IOC_OVERRIDE_PUE);
    GPIOIntTypeSet(BSP_BUTTON_BASE, BSP_BUTTON_USER, GPIO_FALLING_EDGE);

    /* Register the interrupt */
    GPIOPortIntRegister(BSP_BUTTON_BASE, &UserButtonIntHandler);

    /* Clear and enable the interrupt */
    GPIOPinIntClear(BSP_BUTTON_BASE, BSP_BUTTON_USER);
    IntMasterEnable();
    GPIOPinIntEnable(BSP_BUTTON_BASE, BSP_BUTTON_USER);
}

//=========================== interrupt handlers ==============================

/**
 * GPIO_A interrupt handler. User button is GPIO_A_3
 * 
 */
static void UserButtonIntHandler(void) {
    uint32_t ui32GPIOIntStatus;

    /* Disable the interrupts and get the interrupt state */
    IntMasterDisable();
    ui32GPIOIntStatus = GPIOPinIntStatus(BSP_BUTTON_BASE, 1);

    /* Debounce */
    while(!GPIOPinRead(BSP_BUTTON_BASE, BSP_BUTTON_USER));

    /* Notify the user about the button being pressed */
    if(button_int_callback != NULL) {
      button_int_callback(0);
    }

    GPIOPinIntClear(BSP_BUTTON_BASE, ui32GPIOIntStatus);

    /* Enable back the interrupts */
    IntMasterEnable();
}

