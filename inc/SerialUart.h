/*
 * SerialUart.h
 *
 *  Created on: 13.10.2020
 *      Author: emilb
 */

#ifndef SERIALUART_H_
#define SERIALUART_H_


class SerialUart{
public:
	SerialUart();
	virtual ~SerialUart();
	void UartReceive();
private:
	std::string whole;
	char str[80];
	int count;
	char c;
	LpcUartConfig cfg1;
};


#endif /* SERIALUART_H_ */
