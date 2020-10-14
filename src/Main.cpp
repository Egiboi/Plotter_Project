/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

#include "FreeRTOS.h"
#include "task.h"
#include "init.h"
#include "SerialUart.h"


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

XYdriver *driver;
Laser *laser;
Servo *servo;


/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters) {
	SerialUart read;
	while (1) {
		if(driver->calibrate){
			driver->calibration();
		}
		read.UartReceive(driver,laser,servo);
	}
}

/* LED2 toggle thread */


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* the following is required if runtime statistics are to be collected */

/* end runtime statictics collection */

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */

//EMILIN TESTIPUSH

int main(void)
{
	prvSetupHardware();
	driver= driverSetup();
	laser = new Laser();
	laser->changeLaserPower(0);
	servo = new Servo();
	//mutex = xSemaphoreCreateMutex();

	/* LED1 toggle thread */
	xTaskCreate(vLEDTask1, "vTaskLed1",
				configMINIMAL_STACK_SIZE * 10, NULL, (tskIDLE_PRIORITY + 1UL),
				(TaskHandle_t *) NULL);

	/* LED2 toggle thread */


	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
extern "C" {
void RIT_IRQHandler(void) {
	if(driver->calibrate){
		portEND_SWITCHING_ISR(driver->IRQHandlerCali());
	}else{
		portEND_SWITCHING_ISR(driver->IRQHandler());
	}
}
}
