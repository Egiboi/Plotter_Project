#include <XYdriver.h>
#include <stdlib.h>
#include "math.h"
#include "ITM_write.h"
#include "DigitalIoPin.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

XYdriver::XYdriver(DigitalIoPin* dirX, DigitalIoPin* stepX, DigitalIoPin* lim1, DigitalIoPin* lim2,
		DigitalIoPin* lim3, DigitalIoPin* lim4, DigitalIoPin* dirY, DigitalIoPin* stepY):
		dirX(dirX),stepX(stepX),lim1(lim1),lim2(lim2),lim3(lim3),lim4(lim4),dirY(dirY),stepY(stepY){

	dirXToOrigin = false;
	dirYToOrigin = false;
	sbRIT = xSemaphoreCreateBinary();
	xyDone = xSemaphoreCreateBinary();

	totalStepsX = 0;
	totalStepsY = 0;

	calibrate = true;
}
XYdriver::~XYdriver(){}
void XYdriver::calibration(){
	int pps = 500, count = 0, rcount = 0, sum = 0;
	dirX->write(0);
	xState = true;
	while(!lim1->read() && !lim2->read() && !lim3->read() && !lim4->read()){
		Board_LED_Set(2,true);
		vTaskDelay(500);
		Board_LED_Set(2,false);
	}
	for(int i = 0; i < 2; i++){
		dirX->write(!dirX->read());
		while(lim2->read()){
			RIT_start(2,1000000/(pps*2));
			while(!lim1->read() && !lim2->read()) vTaskDelay(configTICK_RATE_HZ*5);
		}
		dirX->write(!dirX->read());
		while(lim1->read()){
			RIT_start(2,1000000/(pps*2));
			count++;
			while(!lim2->read() && !lim1->read()) vTaskDelay(configTICK_RATE_HZ*5);
		}
		rcount++;
		sum += count;
		count = 0;
	}
	vTaskDelay(50);
	totalStepsX = sum / rcount;
	rcount = 0;
	sum = 0;
	xState = false;

	yState = true;
	for(int i = 0; i < 2; i++){
		dirY->write(!dirY->read());
		while(lim3->read()){
			RIT_start(2,1000000/(pps*2));
			while(!lim3->read() && !lim4->read()) vTaskDelay(configTICK_RATE_HZ*5);
		}
		dirY->write(!dirY->read());
		while(lim4->read()){
			RIT_start(2,1000000/(pps*2));
			count++;
			while(!lim3->read() && !lim4->read()) vTaskDelay(configTICK_RATE_HZ*5);
		}
		rcount++;
		sum += count;
		count = 0;
	}
	vTaskDelay(50);
	totalStepsY = sum / rcount;
	yState = false;

	xState = true;
	dirX->write(1);
	RIT_start(totalStepsX,1000000/(pps*2));
	xState = false;

	yState = true;
	dirY->write(!dirY->read());
	RIT_start(totalStepsY,1000000/(pps*2));
	yState = false;

	currentX = totalStepsX/2;
	currentY = totalStepsY/2;

	calibrate = false;
}
void XYdriver::step(float x, float y){
	int pps = 500;
	currentLeadSteps = 0;
	currentFolSteps = 0;
	int dx = x - currentX;
	int dy = y - currentY;

    dX = (dx < 0) ? dirXToOrigin : !dirXToOrigin;
    dirX->write(dX);
    dY = (dy < 0) ? dirYToOrigin : !dirYToOrigin;
    dirY->write(dY);

	if(abs(dx) > abs(dy)){
		totalLeadSteps = abs(dx);
		totalFolSteps = abs(dy);
		lead = stepX;
		follow = stepY;
	}else{
		totalLeadSteps = abs(dy);
		totalFolSteps = abs(dx);
		lead = stepY;
		follow = stepX;
	}

	p = 2 * totalFolSteps - totalLeadSteps;

	while(currentLeadSteps < totalLeadSteps){
		RIT_start(2,1000000/(pps*2));
	}
	xSemaphoreGive(xyDone);
	if (abs(dx) > abs(dy)) {
		currentX = (dX == dirXToOrigin) ? (currentX - currentLeadSteps) : (currentX + currentLeadSteps);
		currentY = (dY == dirYToOrigin) ? (currentY - currentFolSteps) : (currentY + currentFolSteps);
	}else{
		currentX = (dX == dirXToOrigin) ? (currentX - currentFolSteps) : (currentX + currentFolSteps);
		currentY = (dY == dirYToOrigin) ? (currentY - currentLeadSteps) : (currentY + currentLeadSteps);
	}
}
bool XYdriver::IRQHandlerCali(void)
{
	// This used to check if a context switch is required
	portBASE_TYPE xHigherPriorityWoken = pdFALSE;

	Chip_RIT_ClearIntStatus(LPC_RITIMER); // clear IRQ flag

	if((RIT_count > 0) && ((RIT_count % 2) == 0) && xState == true) {
		RIT_count--;
		stepX->write(1);
	}else if((RIT_count > 0) && ((RIT_count % 2) != 0) && xState == true){
		RIT_count--;
		stepX->write(0);
	}
	else if((RIT_count > 0) && ((RIT_count % 2) == 0) && yState == true) {
		RIT_count--;
		stepY->write(1);
	}else if((RIT_count > 0) && ((RIT_count % 2) != 0) && yState == true){
		RIT_count--;
		stepY->write(0);
	}
	else{
		Chip_RIT_Disable(LPC_RITIMER);
		xSemaphoreGiveFromISR(sbRIT, &xHigherPriorityWoken);
	}

	// End the ISR and (possibly) do a context switch
	portEND_SWITCHING_ISR(xHigherPriorityWoken);
}
bool XYdriver::IRQHandler(void){
	portBASE_TYPE xHigherPriorityWoken = pdFALSE;

	Chip_RIT_ClearIntStatus(LPC_RITIMER); // clear IRQ flag

	bool minX = lim1->read() && (dX == dirXToOrigin);
	bool maxX = lim2->read() && (dX == !dirXToOrigin);
	bool minY = lim3->read() && (dY == dirYToOrigin);
	bool maxY = lim4->read() && (dY == !dirYToOrigin);

	if (minX || maxX || minY || maxY) {
        // motors hit limit switches, stop
        Chip_RIT_Disable(LPC_RITIMER);
        xSemaphoreGiveFromISR(sbRIT, &xHigherPriorityWoken);
    }

	if ((RIT_count > 0) && ((RIT_count % 2) == 0)) {
		RIT_count--;
		lead->write(1);
		if (p > 0) {
			follow->write(1);
		}
	} else if ((RIT_count > 0) && ((RIT_count % 2) != 0)) {
		RIT_count--;
		currentLeadSteps += 1;
		lead->write(0);

		if (p > 0) {
			currentFolSteps += 1;
			follow->write(0);
			p = p - 2 * totalLeadSteps;
		}
		p = p + 2 * totalFolSteps;
	} else {
		Chip_RIT_Disable(LPC_RITIMER);
		xSemaphoreGiveFromISR(sbRIT, &xHigherPriorityWoken);
	}

	return xHigherPriorityWoken;
}
void XYdriver::RIT_start(int count, int pps)
{
	uint64_t cmp_value;

	// Determine approximate compare value based on clock rate and passed interval
	cmp_value = (uint64_t) Chip_Clock_GetSystemClockRate() * (uint64_t) pps / 1000000;

	// disable timer during configuration
	Chip_RIT_Disable(LPC_RITIMER);
	RIT_count = count;

	// enable automatic clear on when compare value==timer value
	// this makes interrupts trigger periodically
	Chip_RIT_EnableCompClear(LPC_RITIMER);

	// reset the counter
	Chip_RIT_SetCounter(LPC_RITIMER, 0);
	Chip_RIT_SetCompareValue(LPC_RITIMER, cmp_value);

	// start counting
	Chip_RIT_Enable(LPC_RITIMER);

	// Enable the interrupt signal in NVIC (the interrupt controller)
	NVIC_EnableIRQ(RITIMER_IRQn);

	// wait for ISR to tell that we're done
	if(xSemaphoreTake(sbRIT, portMAX_DELAY) == pdTRUE) {
		// Disable the interrupt signal in NVIC (the interrupt controller)
		NVIC_DisableIRQ(RITIMER_IRQn);
	}
	else {
		// unexpected error
	}
}
