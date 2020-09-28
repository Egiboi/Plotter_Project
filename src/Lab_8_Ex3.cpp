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
#include "heap_lock_monitor.h"
#include <stdlib.h>
#include "semphr.h"
#include "LpcUart.h"

//#include "semaphore.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
class DigitalIoPin {
public:
	DigitalIoPin(int Mport, int Mpin, bool Minput = true, bool Mpullup = true, bool Minvert = false){
		uint32_t Modefunc;
		port = Mport;
		pin = Mpin;
		input=Minput;
		if(Minput){
			if(!Minvert){
				if(Mpullup){
					Modefunc = (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN);
				}else{
					Modefunc = (IOCON_DIGMODE_EN | IOCON_INV_EN);
				}

			}else{
				if(Mpullup){
					Modefunc = (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN) ;
				}else{
					Modefunc = (IOCON_DIGMODE_EN);
				}

			}
			Chip_IOCON_PinMuxSet(LPC_IOCON,Mport,Mpin,Modefunc);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, Mport, Mpin);

		}else{
			Chip_IOCON_PinMuxSet(LPC_IOCON,Mport,Mpin,(IOCON_DIGMODE_EN));
			Chip_GPIO_SetPinDIROutput(LPC_GPIO, Mport, Mpin);
		}


	}
	virtual ~DigitalIoPin(){};
	bool read(){
		if(input){
			return Chip_GPIO_GetPinState(LPC_GPIO, port,pin);
		}else{
			return false;
		}
	}
	void write(bool value){
		Chip_GPIO_SetPinState(LPC_GPIO, port, pin, value);
	}
private:
	int port;
	int pin;
	bool input;

};




DigitalIoPin *button1;
DigitalIoPin *button2;
DigitalIoPin *button3;
LpcUart *my_uart;
volatile int filter;
volatile uint32_t last;
volatile int code[8];
SemaphoreHandle_t mutex;
SemaphoreHandle_t queue;
SemaphoreHandle_t bin;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

extern "C" {
void PIN_INT0_IRQHandler(void){

	int button=0;
	uint32_t current = xTaskGetTickCountFromISR();
	if(uxQueueSpacesAvailable(queue)>1){
		xQueueSendToBackFromISR(queue, &button, NULL);
	}
	last=current;
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(0));

}
void PIN_INT1_IRQHandler(void){

	int button=1;
	uint32_t current = xTaskGetTickCountFromISR();
	if(uxQueueSpacesAvailable(queue)>1){
		xQueueSendToBackFromISR(queue, &button, NULL);
	}
	last=current;
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(1));
}

}


/* LED1 toggle thread */


/* LED2 toggle thread */
static void vLEDTask1(void *pvParameters) {
	uint32_t count = 0;
	int resetVal=-1;
	vTaskDelay(configTICK_RATE_HZ*2);
	while (1) {
		if(button3->read()){
			count=xTaskGetTickCount();
			while(button3->read());
			if(xTaskGetTickCount()-count>3000){
				xQueueSendToFront(queue,&resetVal, configTICK_RATE_HZ);
				my_uart->write("Pin Reset requested, enter new code\r\n");
			}
		}

		vTaskDelay(configTICK_RATE_HZ/5);
	}

}



/* LED2 toggle thread */
static void vLEDTask2(void *pvParameters) {
	uint32_t count = 0;
	bool open = false;
	Board_LED_Set(1, false);
	Board_LED_Set(0, true);
	vTaskDelay(configTICK_RATE_HZ*2);
	while (1) {
		if(xSemaphoreTake(bin, 1) == pdTRUE){
			open = true;
			Board_LED_Set(0, false);
			Board_LED_Set(1, true);
			count = xTaskGetTickCount();
			my_uart->write("Door opened\r\n\r\n");
		}
		if(open){
			if(xTaskGetTickCount()-count>5000){
				open = false;
				Board_LED_Set(1, false);
				Board_LED_Set(0, true);
				my_uart->write("Door closed\r\n\r\n");
			}
		}


		vTaskDelay(configTICK_RATE_HZ/5);
	}

}



/* UART (or output) thread */
static void vUARTTask(void *pvParameters) {

	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);
	NVIC_EnableIRQ(PIN_INT0_IRQn);
	NVIC_ClearPendingIRQ(PIN_INT1_IRQn);
	NVIC_EnableIRQ(PIN_INT1_IRQn);

	bool setPin=false;
	LpcPinMap none = { .port = -1, .pin = -1}; // unused pin has negative values in it
	LpcPinMap txpin1 = { .port = 0, .pin = 18 }; //
	LpcPinMap rxpin1 = { .port = 0, .pin = 13 }; //
	LpcUartConfig cfg1 = {
			.pUART = LPC_USART0,
			.speed = 115200,
			.data = UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1,
			.rs485 = false,
			.tx = txpin1,
			.rx = rxpin1,
			.rts = none,
			.cts = none
	};

	my_uart = new LpcUart(cfg1);
	vTaskDelay(configTICK_RATE_HZ*2);
	while(uxQueueSpacesAvailable(queue)!=9){
		//Clear init entries
		int temp;
		xQueueReceive(queue,&temp,configTICK_RATE_HZ);
	}



	my_uart->write("Ready to go\r\n");
	while (1) {
		int peek=0;
		if(xQueuePeek(queue, &peek,configTICK_RATE_HZ/20)==pdTRUE){
			if(peek==-1){
				xQueueReceive(queue,&peek,configTICK_RATE_HZ);
				setPin=true;
			}
		}
		if(uxQueueSpacesAvailable(queue)<=1&&!setPin){
			if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE){
				bool codeCheck=true;
				int nums[8] = {0};
				int index=0;
				while(index<8){

					int button;
					xQueueReceive(queue,&button,configTICK_RATE_HZ);
					nums[index]=button;
					char buff[10]={};
					sprintf(buff,"%d",button);
					my_uart->write(buff);
					xQueueSendToBack(queue,&button,configTICK_RATE_HZ);

					if(nums[index]==code[index]&&codeCheck){
						if(index==7){
							my_uart->write("\r\n");
							xSemaphoreGive(bin);
							my_uart->write("Code correct!\r\n");
							while(uxQueueSpacesAvailable(queue)!=9){
								//Clear entries
								int temp;
								xQueueReceive(queue,&temp,configTICK_RATE_HZ);
							}
						}
					}else{
						codeCheck = false;
						if(index==7){
							my_uart->write("\r\n");
							//disgard latest entry if code wrong
							xQueueReceive(queue,&button,configTICK_RATE_HZ);
							my_uart->write("Code incorrect\r\n");
						}
					}
					index++;

				}


				xSemaphoreGive(mutex);
			}
		}
		if(xTaskGetTickCount()-last >15000 && uxQueueSpacesAvailable(queue)!=9){
			while(uxQueueSpacesAvailable(queue)!=9){
				//Clear entries
				int temp;
				xQueueReceive(queue,&temp,configTICK_RATE_HZ);
			}
			my_uart->write("Timeout\r\n\r\n");
		}
		if(setPin == true){
			if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE){
				Board_LED_Set(0, false);
				Board_LED_Set(1, false);
				Board_LED_Set(2, true);
				while(uxQueueSpacesAvailable(queue)>1);
				int temp=0;
				my_uart->write("New code: ");
				for(int i=0;i<8;i++){
					xQueueReceive(queue,&temp,configTICK_RATE_HZ);
					code[i]=temp;
					char buff[10]={};
					sprintf(buff,("%d"),temp);
					my_uart->write(buff);
				}
				my_uart->write("\r\n");

				Board_LED_Set(0, true);
				Board_LED_Set(1, false);
				Board_LED_Set(2, false);
				setPin=false;
				xSemaphoreGive(mutex);
			}
		}
		vTaskDelay(configTICK_RATE_HZ);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* the following is required if runtime statistics are to be collected */
extern "C" {

void vConfigureTimerForRunTimeStats( void ) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}



/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();

	Board_Init();
	heap_monitor_setup();
	last = 0;
	filter = 100;

	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	/* Set pin back to GPIO (on some boards may have been changed to something
		   else by Board_Init()) */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 17,(IOCON_MODE_PULLUP |IOCON_DIGMODE_EN | IOCON_MODE_INACT) );
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 11,(IOCON_MODE_PULLUP |IOCON_DIGMODE_EN | IOCON_MODE_INACT) );
	/* Configure GPIO pin as input */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 17);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 11);

	/* Enable PININT clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PININT);

	/* Reset the PININT block */
	Chip_SYSCTL_PeriphReset(RESET_PININT);

	/* Configure interrupt channel for the GPIO pin in INMUX block */
	Chip_INMUX_PinIntSel(0, 0, 17);
	Chip_INMUX_PinIntSel(1, 1, 11);

	/* Configure channel interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(0));
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(1));

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(0));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(1));
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(0));
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(1));

	/* Enable interrupt in the NVIC */
	NVIC_SetPriority(PIN_INT0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY+1);
	NVIC_SetPriority(PIN_INT1_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY+1);




	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

/* end runtime statictics collection */

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{

	prvSetupHardware();

	code[0] = 1;
	code[1] = 1;
	code[2] = 1;
	code[3] = 1;
	code[4] = 0;
	code[5] = 1;
	code[6] = 1;
	code[7] = 0;
	button1 = new DigitalIoPin(0,17,true,true,false);
	button2 = new DigitalIoPin(1,11,true, true, false);
	button3 = new DigitalIoPin(1,9,true, true, false);


	//button1 = new DigitalIoPin(0,8,true,true,false);
	//button2 = new DigitalIoPin(1,6,true,true,false);
	//button3 = new DigitalIoPin(1,8,true,true,false);
	mutex = xSemaphoreCreateMutex();
	queue = xQueueCreate(9, sizeof(int));
	bin = xSemaphoreCreateBinary();

	/* LED2 toggle thread */
	xTaskCreate(vLEDTask2, "vTaskLed2",
			configMINIMAL_STACK_SIZE+128, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);

	/* UART output thread, simply counts seconds */
	xTaskCreate(vUARTTask, "vTaskUart",
			configMINIMAL_STACK_SIZE + 128, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);

	/* UART output thread, simply counts seconds */
	xTaskCreate(vLEDTask1, "vTaskLed1",
			configMINIMAL_STACK_SIZE + 128, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

