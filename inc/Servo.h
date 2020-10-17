/*
 * Servo.h
 *
 *  Created on: 11.10.2020
 *      Author: winte
 */

#ifndef SERVO_H_
#define SERVO_H_

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#include "sct_15xx.h"
#else
#include "board.h"
#endif
#endif

#include "ITM_write.h"
#include "FreeRTOS.h"
#define hardMin 999
#define hardMax 2001

class Servo{
public:
	Servo(int port = 0, int pin = 10);
	void move(double value);
	virtual ~Servo();
	bool setMin(int value);
	bool setMax(int value);
	int getMin();
	int getMax();
private:
	int port;
	int pin;

	int times;
	double remain;
	double lastValue;
	double dutyCycle;
	int min,max;

};

#endif /* SERVO_H_ */
