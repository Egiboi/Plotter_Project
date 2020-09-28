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
#include "semphr.h"
#include <stdlib.h>
#include <string>
#include <cstring>
#include "Parser.h"
using namespace std;
SemaphoreHandle_t mutex;
SemaphoreHandle_t sema;

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
class DigitalIoPin {
public:
	DigitalIoPin(int Mport, int Mpin, bool Minput = true, bool Mpullup = true,
			bool Minvert = false) {
		uint32_t Modefunc;
		port = Mport;
		pin = Mpin;
		input = Minput;
		if (Minput) {
			if (!Minvert) {
				if (Mpullup) {
					Modefunc = (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN
							| IOCON_INV_EN);
				} else {
					Modefunc = (IOCON_DIGMODE_EN | IOCON_INV_EN);
				}

			} else {
				if (Mpullup) {
					Modefunc = (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN);
				} else {
					Modefunc = (IOCON_DIGMODE_EN);
				}

			}
			Chip_IOCON_PinMuxSet(LPC_IOCON, Mport, Mpin, Modefunc);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, Mport, Mpin);

		} else {
			Chip_IOCON_PinMuxSet(LPC_IOCON, Mport, Mpin, (IOCON_DIGMODE_EN));
			Chip_GPIO_SetPinDIROutput(LPC_GPIO, Mport, Mpin);
		}

	}
	virtual ~DigitalIoPin() {
	}
	;
	bool read() {
		if (input) {
			return Chip_GPIO_GetPinState(LPC_GPIO, port, pin);
		} else {
			return false;
		}
	}
	void write(bool value) {
		Chip_GPIO_SetPinState(LPC_GPIO, port, pin, value);
	}
private:
	int port;
	int pin;
	bool input;

};

static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();
	heap_monitor_setup();
	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* the following is required if runtime statistics are to be collected */
extern "C" {

void vConfigureTimerForRunTimeStats(void) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}

/* end runtime statictics collection */

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void) {
	prvSetupHardware();
	int maxLine=100;
	char arr[101]={};
		int temp =0;;
		int i=0;
		while (1) {
			temp =Board_UARTGetChar();
			if(temp !=EOF && temp != '\r'){
				//if(xSemaphoreTake(mutex, portMAX_DELAY)==pdTRUE){
					arr[i]=temp;
					Board_UARTPutChar(temp);
					//xSemaphoreGive(mutex);
				//}

				i++;
			}if(temp =='\r'){
				Board_UARTPutSTR("\n\r");
			}

			if(i== maxLine|| temp=='\n' || temp=='\r'){

				string str(arr);
				GcodeParser parser(str);
				if(parser.IsValid()){
					//if(xSemaphoreTake(mutex, portMAX_DELAY)==pdTRUE){

					Board_UARTPutSTR("ok");

					//}
				}else{
					Board_UARTPutSTR("fail");
				}
				Board_UARTPutSTR("\n\r");
				//xSemaphoreGive(mutex);
				for(int size=0;size<(int)sizeof(arr) / (int)sizeof(char);size++){
					arr[size]='\0';
				}
				i=0;
			}
		}

	return 1;
}

