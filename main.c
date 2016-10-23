/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
//#include "driverlib/sysctl.c"
#include "driverlib/debug.h"

#include "system_init.h"
#include "motor.h"

typedef const struct {
    uint32_t out;
    uint32_t delay;
    uint32_t next[4];
} State;

#define Center 0
#define Left 1
#define Right 2
State fsm[3] = {
        {FW, 10, {Center, Right, Left, Right}},
        {LEFT, 10, {Center, Right, Center, Left}},
        {RIGHT, 10, {Center, Center, Left, Right}}
};

const uint32_t ms=(1.0/(80*1000000)*80000);
int main(void) {
        volatile uint32_t clocks;
        uint32_t input, next_state;


        PeriphInit();
        CompInit();
        PWMInit();
	  //------------device ready
	  Ready();
	  while(1){
	      input = Input();
	      switch (input){
	          case 0x00: next_state = FW; break;
	          case 0x01: next_state = RIGHT_MOTOR_FW; break;
	          case 0x02: next_state = LEFT_MOTOR_FW; break;
	          case 0x03: next_state = STOP; break;
	      };
	      Drive(next_state);
	      SysCtlDelay(800000);
	  }
}


