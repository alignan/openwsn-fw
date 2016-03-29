/**
\brief This is a standalone test program for the button of the RE-Mote board 
\author Antonio Lignan <alinan@zolertia.com>, March 2016
*/

#include "stdint.h"
#include "stdio.h"

#include "board.h"
#include "button.h"
#include "leds.h"
#include "openserial.h"

void button_callback(uint8_t value) {
  leds_all_toggle();
}

/**
\brief The program starts executing here.
*/
int mote_main(void) {

  board_init();

  REMOTE_BUTTON_REGISTER_INT(button_callback);

  while (1) {
    board_sleep();
  }

  return 0;
}
