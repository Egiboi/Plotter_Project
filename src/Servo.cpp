#include "Servo.h"
#include <stdlib.h>
#include <math.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

Servo::Servo(int port0, int pin0): port(port0), pin(pin0){

	Chip_SWM_MovablePortPinAssign(SWM_SCT0_OUT0_O, port, pin);
	Chip_SCT_Init(LPC_SCT0);

	LPC_SCT0->CONFIG |= (1 << 17);              // two 16-bit timers, auto limit
	LPC_SCT0->CTRL_L |= (72 - 1) << 5;          // set prescaler, SCTimer/PWM clock = 1 MHz
	LPC_SCT0->MATCHREL[0].L = 20000 - 1;     	// match 0 @ 1000/1MHz = (1 kHz PWM freq)
	LPC_SCT0->MATCHREL[1].L = 1650;        		// match 1 used for duty cycle (in 10 steps)
	LPC_SCT0->EVENT[0].STATE = 0xFFFFFFFF;      // event 0 happens in all states
	LPC_SCT0->EVENT[0].CTRL = (1 << 12);        // match 0 condition only
	LPC_SCT0->EVENT[1].STATE = 0xFFFFFFFF;      // event 1 happens in all states
	LPC_SCT0->EVENT[1].CTRL = (1 << 0) | (1 << 12);    // match 1 condition only
	LPC_SCT0->OUT[0].SET = (1 << 0);            // event 0 will set SCTx_OUT0
	LPC_SCT0->OUT[0].CLR = (1 << 1);            // event 1 will clear SCTx_OUT0
	LPC_SCT0->CTRL_L &= ~(1 << 2);
	//Default min, max
	min = 1000;
	max = 2000;
}
//Function to drive servo arm to desired level. Jump to new level is not immediately done, it is run to new level once per tick
void Servo::move(double value){
	if(value > LPC_SCT0->MATCHREL[1].L){
		while(LPC_SCT0->MATCHREL[1].L <= value){
			++LPC_SCT0->MATCHREL[1].L;
			vTaskDelay(1);
		}
	}
	else if(value < LPC_SCT0->MATCHREL[1].L){
		while(LPC_SCT0->MATCHREL[1].L >= value){
			--LPC_SCT0->MATCHREL[1].L;
			vTaskDelay(1);
		}
	}
	dutyCycle = value/20000;
	lastValue = value;
	//xSemaphoreGive(sDone);
}
//Function to set level for pen down in microcontroller
bool Servo::setMin(int value){
	if(value>hardMin&&value<max){
		min=value;
		return true;
		//Changed min value
	}else{
		return false;
		//Change value out of hard bounds
	}
}
//Function to set level for pen up in microcontroller
bool Servo::setMax(int value){
	if(value<hardMax&&value>min){
		max=value;
		return true;
		//changed  max value
	}else{
		return false;
		//Change value out of hard bounds
	}
}
//Get down level set in microcontroller
int Servo::getMin(){
	return min;
}
//Get up level set in microcontroller
int Servo::getMax(){
	return max;
}
Servo::~Servo(){}
