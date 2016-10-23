/*
 * motor.c
 *
 *  Created on: Oct 15, 2016
 *      Author: boris
 */

#include "motor.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.c"

//#include "driverlib/gpio.h"
#define MOTOR_CONTROL (GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7)

void Drive(uint8_t direction){
    GPIOPinWrite(GPIO_PORTD_BASE, MOTOR_CONTROL, direction);
}
