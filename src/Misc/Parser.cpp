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
using namespace std;

GcodeParser::GcodeParser(string str) {
	//Checks the Gcode type if exist
	if(str.length()<sizeof(fullCommand)/sizeof(char)){
		strcpy(fullCommand,str.c_str());
	}

	x=0;
	int i = 0;
	while (str.c_str()[i+1] != ' '&& (int)str.length()>i) {
		i++;
	}
	string code = str.substr(0, i + 1);
	if(code.length()<sizeof(Cmnd)/sizeof(char)){
		strcpy(Cmnd,code.c_str());
	}
	char array[50]= {};

	strcpy(array,str.c_str());
	if (code.compare("M10") == 0) {
		if (str.compare("M10") == 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (code.compare("M11") == 0) {
		if (str.compare("M11") == 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (code.compare("M2") == 0) {
		if(sscanf(str.c_str(), "M2 U%d D%d", &limx, &limy)==2){

		}
		if (limx <= 255 && limx >= 0 && limy <= 255 && limy >= 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (code.compare("M1") == 0) {
		if(sscanf(str.c_str(), "M1 %d", &penPos)==1){
			if (penPos <= 255 && penPos >= 0) {
				valid = true;
			} else {
				valid = false;
			}
		}else{
			valid = false;
		}
	}
	else if (code.compare("M4") == 0) {
		if(sscanf(str.c_str(), "M4 %d", &laserPwr)==1){
			if (laserPwr <= 255 && laserPwr >= 0) {
				valid = true;
			} else {
				valid = false;
			}
		}else{
			valid=false;
		}
	}
	else if (code.compare("G28") == 0) {
		if (str.compare("G28") == 0) {
			valid = true;
		} else {
			valid = false;
		}

	}
	else if (code.compare("G1") == 0) {
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
bool GcodeParser::runCommand(XYdriver *driver,Laser *laser, Servo *servo){
	if(valid==true){

		if (strcmp(Cmnd,"M10") == 0) {

		}
		else if (strcmp(Cmnd,"M11") == 0) {
			//reply limit switch states
			//Limit switches read one (high) when switch is open and zero (low) when closed

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
		else if (strcmp(Cmnd,"G1") == 0) {
			driver->step(x, y);

		}
		return valid;

	}else{
		return valid;
	}

}





