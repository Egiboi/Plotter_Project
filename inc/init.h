/*
 * init.h
 *
 *  Created on: 6 Oct 2020
 *      Author: danie
 */

#ifndef INIT_H_
#define INIT_H_

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif


#include <XYdriver.h>
#include "heap_lock_monitor.h"
#include "ITM_write.h"
#include "DigitalIoPin.h"
#include "Laser.h"
#include "Servo.h"


//Stepper motor port and pins
#define directionXPort 1
#define directionXPin 0

#define directionYPort 0
#define directionYPin 28

#define driverYPort 0
#define driverYPin 27

#define driverXPort 0
#define driverXPin 24


//Limit switch ports and pins
#define limit1Port 1
#define limit1Pin 3

#define limit2Port 0
#define limit2Pin 0

#define limit3Port 0
#define limit3Pin 9

#define limit4Port 0
#define limit4Pin 29


//Button ports and Pins
#define sw1Port 0
#define sw1Pin 8

#define sw2Port 1
#define sw2Pin 6

#define sw3Port 1
#define sw3Pin 8


//PenServo port and pin
#define penPort 1
#define penPin 8


//Laser port and pin
#define laserPort 1
#define laserPin 8


void prvSetupHardware(void);
XYdriver* driverSetup(void);
//pen init(void);
//laser init(void);
void irqSetup(int port, int pin, int channel);
extern "C" {
void vConfigureTimerForRunTimeStats( void );
void RIT_IRQHandler(void);
}

#endif /* INIT_H_ */
