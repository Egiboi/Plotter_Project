/*
 * Parser.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: danie
 */
#include "Parser.h"
#include <stdlib.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include "SerialUart.h"
#include "init.h"
using namespace std;

GcodeParser::GcodeParser(char *str) {

	if(strlen(str)<sizeof(fullCommand)/sizeof(char)){
		strcpy(fullCommand,str);
	}
	x=0;
	int i = 0;
	while (str[i] != ' '&& strlen(str)>i) {
		i++;
	}

	for(int j = 0; j < i; ++j){
		code[j] = str[j];
		code[j+1] = '\n';
		code[j+2] = '\0';
	}

	char array[50]= {};
	strcpy(array,str);

	if (strcmp("M10\n", code) == 0) {
		if (strcmp("M10\n", code) == 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (strcmp("M11\n", code) == 0) {
		if(strcmp("M11\n", str) == 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (strcmp("M2\n", code) == 0) {
		if(sscanf(str, "M2 U%d D%d", &limx, &limy)==2){

		}
		if (limx <= 255 && limx >= 0 && limy <= 255 && limy >= 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (strcmp("M1\n", code) == 0) {
		if(sscanf(str, "M1 %d", &penPos)==1){
			if (penPos <= 255 && penPos >= 0) {
				valid = true;
			} else {
				valid = false;
			}
		}else{
			valid = false;
		}
	}
	else if (strcmp("M4\n", code) == 0) {
		if(sscanf(str, "M4 %d", &laserPwr)==1){
			if (laserPwr <= 255 && laserPwr >= 0) {
				valid = true;
			} else {
				valid = false;
			}
		}else{
			valid=false;
		}
	}
	else if (strcmp("G28\n", code) == 0) {
		if (strcmp("G28\n", code) == 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (strcmp("G1\n", code) == 0) {
		if(sscanf(array,"G1 X%f Y%f A%d", &x, &y, &a)==3){
			if (x <= 500 && x >= -500 && y <= 500 && y >= -500 && (a == 0 || a == 1)) {
				valid = true;
			} else {
				valid = false;
			}
		}else{
			valid = false;
		}
	} else {
		valid = false;
	}
}
GcodeParser::~GcodeParser() {
}
//Run the command, return bool is command valid and has it been run. Check value in call
bool GcodeParser::runCommand(XYdriver *driver,Laser *laser, Servo *servo, LpcUart *vallox){

	if(valid==true){

		if (strcmp(code,"M10\n") == 0) {
			//Send init values
			vallox->write("M10 XY 380 310 0.00 0.00 A0 B0 H0 S80 U160 D90\r\nOK\r\n");
		}
		else if (strcmp(Cmnd,"M11") == 0) {
			int state1=-1,state2=-1,state3=-1,state4=-1;
			char buffer[40]={};
            //reply limit switch states
            //Limit switches read one (high) when switch is open and zero (low) when closed
            if(driver->limitSwitch(4)){
                state4 = 1;
            }
            else if(!driver->limitSwitch(4)){
                state4 = 0;
            }
            if(driver->limitSwitch(3)){
                state3 = 1;
            }
            else if(!driver->limitSwitch(3)){
                state3 = 0;
            }
            if(driver->limitSwitch(2)){
                state2 = 1;
            }
            else if(!driver->limitSwitch(2)){
                state2 = 0;
            }
            if(driver->limitSwitch(1)){
                state1 = 1;
            }
            else if(!driver->limitSwitch(1)){
                state1 = 0;
            }
            sprintf(buffer,"M11 %d %d %d %d\r\nOK\r\n",state4, state3, state2 , state1);
            vallox->write(buffer);

		}
		else if (strcmp(Cmnd,"M2") == 0) {
			//Save pen value
		}
		else if (strcmp(Cmnd,"M1") == 0) {
			double value = 1000+1000/255*penPos;
			servo->move(value);
		}
		else if (strcmp(Cmnd,"M4") == 0) {
			laser->changeLaserPower(laserPwr);
		}
		else if (strcmp(Cmnd,"G28") == 0) {
			driver->step(0, 0);

		}
		else if (strcmp(code,"G1\n") == 0) {
			driver->step(x, y);

		}
		return valid;

	}else{
		return valid;
	}

}

