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
#include "string"
#include "string.h"

#include "task.h"
#include <mutex>
#include "semphr.h"
#include <cmath>
#include "ITM_write.h"
#include "Fmutex.h"
#include "heap_lock_monitor.h"
#include "DigitalIoPin.h"
#include "chip.h"
#include "LpcUart.h"

#include <stdio.h>
#include "init.h"
#include "SerialUart.h"
#include "XYdriver.h"
#include "Servo.h"
#include "Parser.h"

SerialUart::SerialUart(){
	count = 0;
}
SerialUart::~SerialUart(){
}
void SerialUart::UartReceive(XYdriver *xydriver, Laser *laser, Servo *servo) {
	cfg1 = UartCreate();
	LpcUart vallox(cfg1);
	vTaskDelay(50);

	while (1) {
		vallox.read(c);
		if(c != EOF && c != '\n' && count < sizeof(str) && c != '\0') {
			str[count] = c;
			count++;
		}
		else if(c == '\n' || c == '\r' ){
			str[count] = '\n';
			str[count+1] = '\0';
<<<<<<< HEAD

			ITM_write(str);
			GcodeParser parser(str);
			parser.runCommand(xydriver, laser, servo, &vallox);
			//do{}while(xSemaphoreTake(servo->sDone, 10) == pdFALSE||xSemaphoreTake(xydriver->xyDone, 10) == pdFALSE);
			vallox.write("OK\r\n");
			memset(str, 0, sizeof(str));
=======
			ITM_write(str);

			GcodeParser parser(str);
			parser.runCommand(xydriver, laser, servo, &vallox);

			do{}while(xSemaphoreTake(servo->sDone, 10) == pdFALSE||xSemaphoreTake(xydriver->xyDone, 10) == pdFALSE);
			vallox.write("OK\r\n");
>>>>>>> parent of fd8aefd... Merge branch 'Testi' of https://github.com/Egiboi/Plotter_Project into Testi
			count = 0;
		}

		vTaskDelay(configTICK_RATE_HZ/100);
	}
}
