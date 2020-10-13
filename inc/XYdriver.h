/*
 * XYdriver.h
 *
 *  Created on: 4.10.2020
 *      Author: winte
 */

#ifndef XYDRIVER_H_
#define XYDRIVER_H_

#include "DigitalIoPin.h"
#include "FreeRTOS.h"
#include "semphr.h"

class XYdriver {
public:
	XYdriver(DigitalIoPin* dirX, DigitalIoPin* stepX, DigitalIoPin* dirY, DigitalIoPin* stepY, DigitalIoPin* lim1, DigitalIoPin* lim2,
			DigitalIoPin* lim3, DigitalIoPin* lim4);
	virtual ~XYdriver();

	void step(float x, float y);
	void calibration();
	bool IRQHandlerCali(void);
	bool IRQHandler(void);
	void RIT_start(int count, int pps);
    bool calibrate = true;
	volatile uint32_t RIT_count;
    SemaphoreHandle_t sbRIT;
    SemaphoreHandle_t xyDone;

    bool dirXToOrigin;
    bool dirYToOrigin;
    long totalStepsX;
    long totalStepsY;
private:
	DigitalIoPin* dirX;
	DigitalIoPin* stepX;

	DigitalIoPin* lim1;
	DigitalIoPin* lim2;
	DigitalIoPin* lim3;
	DigitalIoPin* lim4;
	DigitalIoPin* dirY;
	DigitalIoPin* stepY;

    DigitalIoPin* lead;  			// leading motor
    DigitalIoPin* follow;	 		// other motor
    int totalLeadSteps;             // total steps of the leading motor
    int totalFolSteps;              // total step of the following motor
    int currentLeadSteps;     		// current step of the leading motor
    int currentFolSteps;         	// current step of the dependent motor
    volatile int p;

    bool dX;
    bool dY;
    volatile int currentX = 0;
    volatile int currentY = 0;
    bool xState = false;
    bool yState = false;

};
#endif /* XYDRIVER_H_ */
