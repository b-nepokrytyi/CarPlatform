/*
 * system_init.c
 *
 *  Created on: Jun 19, 2016
 *      Author: boris
 */

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_comp.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/comp.h"
//#include "driverlib/comp.c"
#include "system_init.h"


void Ready(){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        SysCtlDelay(40000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
        SysCtlDelay(40000000);
}

void PWMInit(){
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        SysCtlDelay(5);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlDelay(5);

        GPIOPinConfigure(GPIO_PD0_M1PWM0);
        GPIOPinConfigure(GPIO_PD1_M1PWM1);  // configuring PB6 PB7 as PWM outputs
        GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
        GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

        SysCtlPWMClockSet(SYSCTL_PWMDIV_32);
        PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, 250); // 10khz freq 250; 25khz-100
        PWMPulseWidthSet (PWM1_BASE, PWM_OUT_0, 150);
        PWMPulseWidthSet (PWM1_BASE, PWM_OUT_1, 150);

        PWMGenEnable(PWM1_BASE, PWM_GEN_0); //enable generator
        PWMOutputState(PWM1_BASE, (PWM_OUT_0_BIT|PWM_OUT_1_BIT), true);

}

void PeriphInit(){
        SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
        SysCtlDelay(5);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        SysCtlDelay(5);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlDelay(5);
        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3 |GPIO_PIN_6| GPIO_PIN_7);//control motors

        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);//LED
}

void CompInit(){
        SysCtlPeripheralEnable(SYSCTL_PERIPH_COMP0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlDelay(5);
        GPIOPinTypeComparator(GPIO_PORTC_BASE,GPIO_PIN_7| GPIO_PIN_4); // C0- signal
        ComparatorRefSet(COMP_BASE,COMP_REF_0_1375V);
        ComparatorConfigure(COMP_BASE,0, COMP_TRIG_NONE|COMP_ASRCP_REF|COMP_OUTPUT_NORMAL);

        ComparatorConfigure(COMP_BASE,1, COMP_TRIG_NONE|COMP_ASRCP_REF|COMP_OUTPUT_NORMAL);
}

uint32_t Input(){
    uint32_t left_sens = HWREG(COMP_BASE + COMP_O_ACSTAT0)&0x02;
    uint32_t right_sens = (HWREG(COMP_BASE + COMP_O_ACSTAT1)&0x02)>>1;
    return (left_sens|right_sens);
}
