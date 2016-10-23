/*
 * motor.h
 *
 *  Created on: Oct 15, 2016
 *      Author: boris
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

//gpio output signal for motors
#define RIGHT_MOTOR_FW 0x04
#define RIGHT_MOTOR_BW 0x08

#define LEFT_MOTOR_FW 0x40
#define LEFT_MOTOR_BW 0x80

// output states
#define FW RIGHT_MOTOR_FW|LEFT_MOTOR_FW
#define RIGHT LEFT_MOTOR_FW|RIGHT_MOTOR_BW
#define LEFT LEFT_MOTOR_BW|RIGHT_MOTOR_FW
#define STOP 0x00

void Drive(uint8_t direction);

#endif /* MOTOR_H_ */
