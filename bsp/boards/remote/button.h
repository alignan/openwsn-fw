/**
 * Author: Antonio Lignan (alinan@zolertia.com)
 * Date:   March 2016
 * Description: User button header file
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#define BSP_BUTTON_BASE                 ( GPIO_A_BASE )
#define BSP_BUTTON_USER                 ( GPIO_PIN_3 )

/*---------------------------------------------------------------------------*/
/**
 * \brief Initializes the user button
 */
void button_init(void);
/*---------------------------------------------------------------------------*/
/**
 * \brief Register the user button callback
 */
#define REMOTE_BUTTON_REGISTER_INT(ptr) button_int_callback = ptr;
extern void (*button_int_callback)(uint8_t value);

/*---------------------------------------------------------------------------*/
#endif /* BUTTON_H_ */
