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
#include "heap_lock_monitor.h"
#else
#include "board.h"
#include "ITM_write.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "DigitalIoPin.h"

#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <string>
#include "FreeRTOS.h"
#include "task.h"
#include "DigitalIoPin.h"
#include <mutex>
#include "semphr.h"
#include <cmath>
#include <cstring>

#include "chip.h"
#include "ITM_write.h"
#include "Fmutex.h"

#include "heap_lock_monitor.h"
#include "DigitalIoPin.h"
#include "chip.h"
#include "LpcUart.h"

#include <stdio.h>
#include "init.h"
#include "SerialUart.h"

SerialUart::SerialUart(){
	count = 0;
}
SerialUart::~SerialUart(){
}
void SerialUart::UartReceive() {

	cfg1 = UartCreate();
	LpcUart vallox(cfg1);

	while (1) {
		vallox.read(c);

		if(c != EOF && c != '\n' && count < sizeof(str) && c != '\0') {
			str[count] = c;
			count++;

		}
		else if(c == '\n' || c == '\r' ){
			str[count] = '\n';
			str[count+1] = '\0';
			ITM_write(str);

			if(strcmp (str,"M10\n") == 0){
				vallox.write("M10 XY 380 310 0.00 0.00 A0 B0 H0 S80 U160 D90\r\nOK\r\n");
			}

			whole = std::string(str);


			count = 0;
			memset(str, 0, sizeof str);
		}

		vTaskDelay(configTICK_RATE_HZ);
	}
}
