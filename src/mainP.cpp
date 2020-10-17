#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "string.h"
#include "math.h"

#include "FreeRTOS.h"
#include "user_vcom.h"
#include "task.h"
#include "math.h"
#include "queue.h"
#include "semphr.h"
#include "ITM_write.h"
#include "string.h"
#include "DigitalIoPin.h"
#include "XYdriver.h"
#include "Servo.h"
#include "Laser.h"
#include "LpcUart.h"
#include "parser.h"
#include "commandData.h"


DigitalIoPin* dirX;
DigitalIoPin* stepX;
DigitalIoPin* lim1;
DigitalIoPin* lim2;
DigitalIoPin* lim3;
DigitalIoPin* lim4;
DigitalIoPin* dirY;
DigitalIoPin* stepY;
XYdriver *xydriver;
Servo *servo;
Laser *laser;
LpcUart *vallox;
QueueHandle_t xQueue;
SemaphoreHandle_t semaBinary,semaMutex;

void setupHardware();
void vExecuteTask(void *vParameters);
void vReceiveTask(void *vParameters);



int main(void){
	setupHardware();
	semaMutex = xSemaphoreCreateMutex();
	semaBinary = xSemaphoreCreateMutex();

	xQueue = xQueueCreate( 10, sizeof(data));

	xTaskCreate(vExecuteTask, "Execute Task", configMINIMAL_STACK_SIZE * 5, NULL,
			(tskIDLE_PRIORITY + 2UL), (TaskHandle_t *) NULL);
	xTaskCreate(vReceiveTask, "Receive Task", configMINIMAL_STACK_SIZE * 6, NULL,
			(tskIDLE_PRIORITY + 1UL), (TaskHandle_t *) NULL);
	xTaskCreate(cdc_task, "CDC Task", configMINIMAL_STACK_SIZE * 2, NULL,
			(tskIDLE_PRIORITY + 2UL), (TaskHandle_t *) NULL);

	vQueueAddToRegistry(xQueue, "Queue Command");

	vTaskStartScheduler();

	while (1);

	return 0;
}
void setupHardware() {
	SystemCoreClockUpdate();
	Board_Init();
	ITM_init();
	Chip_RIT_Init(LPC_RITIMER);

	// set the priority level of the interrupt
	NVIC_SetPriority(RITIMER_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);

	Board_LED_Set(0, false);

	dirX = new DigitalIoPin(1,0,DigitalIoPin::output,false);
	stepX = new DigitalIoPin(0,24,DigitalIoPin::output,false);
	lim1 = new DigitalIoPin(0,9,DigitalIoPin::pullup);
	lim2 = new DigitalIoPin(0,29,DigitalIoPin::pullup);
	lim3 = new DigitalIoPin(1,3,DigitalIoPin::pullup);
	lim4 = new DigitalIoPin(0,0,DigitalIoPin::pullup);
	dirY = new DigitalIoPin(0,28,DigitalIoPin::output,false);
	stepY = new DigitalIoPin(0,27,DigitalIoPin::output,false);
	xydriver = new XYdriver(dirX, stepX, lim1, lim2, lim3, lim4, dirY, stepY);
	servo = new Servo(0,10);
	laser = new Laser(0,12);

	laser->changeLaserPower(-1); 		// Sets laser power to zero
}
void vReceiveTask(void *vParameters) {

	int i = 0, SIZE = 80;
	char c;
	int count = 0;
	char str[80];
	data d;
	char ok[] = "OK\r\n";

	char buffer[SIZE];

	vTaskDelay(configTICK_RATE_HZ);

	while(1){
		int len = USB_receive((uint8_t *) (buffer + i), SIZE);
		char *pos = strstr((buffer + i), "\n");
		if(pos != NULL){
			ITM_write(buffer);
			GcodeParser parser(buffer, xydriver);
			d = parser.runCommand();
			xQueueSendToBack(xQueue, &d, portMAX_DELAY);
			xSemaphoreTake(semaBinary, portMAX_DELAY);
			USB_send((uint8_t *) ok, strlen(ok));
			memset(buffer, '\0', sizeof(buffer));
			i = 0;
		}

	}
}
void vExecuteTask(void *vParameters) {
	data d;
	char buffer[64];
	int state1,state2,state3,state4;
	int limUp,limDown;
	vTaskDelay(configTICK_RATE_HZ);

	while(1){
		if(xydriver->calibrate){
			xydriver->calibration();
		}
		else if(xQueueReceive( xQueue, &d , portMAX_DELAY) == pdTRUE){
			if (strcmp(d.command,"M10\n") == 0) {
				sprintf(buffer, "M10 XY %ld %ld 0.00 0.00 A0 B0 H0 S80 U160 D90\n\r", xydriver->totalStepsX,xydriver->totalStepsY);
				USB_send((uint8_t *) buffer, strlen(buffer));
				limUp = 160;
				limDown = 90;
				memset(buffer,'\0',sizeof(buffer));
				xSemaphoreGive(semaBinary);
			}
			else if (strcmp(d.command,"M11\n") == 0) {
				if(lim1->read() ==  1) state1 = 1;
				else state1 = 0;
				if(lim2->read() ==  1) state2 = 1;
				else state2 = 0;
				if(lim3->read() ==  1) state3 = 1;
				else state3 = 0;
				if(lim4->read() ==  1) state4 = 1;
				else state4 = 0;
				sprintf(buffer,"M11 %d %d %d %d\r\n",state4, state3, state2 , state1);
				USB_send((uint8_t *) buffer, strlen(buffer));
				memset(buffer,'\0',sizeof(buffer));
				xSemaphoreGive(semaBinary);

			}
			else if (strcmp(d.command,"M2") == 0) {

			}
			else if (strcmp(d.command,"M1") == 0) {
				/*if(d.penP == limDown){
					servo->move(1350);

				}else if(d.penP == limUp){
					servo->move(1650);
				}*/
				double value = servo->getMin()+((servo->getMax()-servo->getMin())/255*d.penP);
				servo->move(value);
				xSemaphoreGive(semaBinary);
			}
			else if (strcmp(d.command,"M4") == 0) {
				if(d.laserPow == 0){
					laser->changeLaserPower(0);
				}else{
					laser->changeLaserPower(d.laserPow);
				}
				xSemaphoreGive(semaBinary);

			}
			else if (strcmp(d.command,"G28\n") == 0) {
				xydriver->step(1, 1);
				xSemaphoreGive(semaBinary);
			}
			else if (strcmp(d.command,"G1") == 0) {
				if(d.x == -1 || d.y == -1){
					//skip
				}else{
					xydriver->step(d.x,d.y);
				}
				xSemaphoreGive(semaBinary);
			}
		}else{vTaskDelay(configTICK_RATE_HZ/1000);}
	}
}

extern "C" {

void RIT_IRQHandler(void) {
	if(xydriver->calibrate){
		portEND_SWITCHING_ISR(xydriver->IRQHandlerCali());
	}else{
		portEND_SWITCHING_ISR(xydriver->IRQHandler());
	}
}
void vConfigureTimerForRunTimeStats(void) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}
}
