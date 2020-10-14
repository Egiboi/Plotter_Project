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
	while (str[i+1] != ' '&& strlen(str)>i) {
		i++;
	}

	for(int j = 0; j < i; ++j){
		code[j] = str[j];
		code[j+1] = '\0';
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
			vallox->write("M10 XY 380 310 0.00 0.00 A0 B0 H0 S80 U160 D90\r\nOK\r\n");
		}
		else if (strcmp(Cmnd,"M11") == 0) {

		}
		else if (strcmp(Cmnd,"M2") == 0) {
			//Save pen value
		}
		else if (strcmp(Cmnd,"M1") == 0) {
			//set pen position
		}
		else if (strcmp(Cmnd,"M4") == 0) {
			//Laser power
		}
		else if (strcmp(Cmnd,"G28") == 0) {
			//Go to origin

		}
		else if (strcmp(code,"G1\n") == 0) {
			driver->step(x, y);

		}
		return valid;

	}else{
		return valid;
	}

}

