/*
 * SerialUart.h
 *
 *  Created on: 13.10.2020
 *      Author: emilb
 */

#ifndef SERIALUART_H_
#define SERIALUART_H_
#include "string"
#include "LpcUart.h"


class SerialUart{
public:
	SerialUart();
	virtual ~SerialUart();
	void UartReceive(XYdriver *xydriver, Laser *laser, Servo *servo);
	LpcUartConfig cfg1;

private:
	std::string whole;
	char str[80];
	int count;
	char c;
};


#endif /* SERIALUART_H_ */
