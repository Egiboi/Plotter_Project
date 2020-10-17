/*
 * Parser.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: danie
 */
#include "Parser.h"
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include "commandData.h"
using namespace std;

GcodeParser::GcodeParser(char *str, XYdriver *xydriver) {
	data d;

	if(strlen(str)<sizeof(fullCommand)/sizeof(char)){
		strcpy(fullCommand,str);
	}
	x=0;
	size_t i = 0;
	while (str[i] != ' '&& strlen(str)>i && str[i] && str[i] != 165) {
		i++;
	}

	for(size_t j = 0; j < i; ++j){
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
	else if (strcmp("M2", code) == 0) {
		if(sscanf(str, "M2 U%d D%d", &limUp, &limDown)==2){

		}
		if (limUp <= 255 && limUp >= 0 && limDown <= 255 && limDown >= 0) {
			valid = true;
		} else {
			valid = false;
		}
	}
	else if (strcmp("M1", code) == 0) {
		if(sscanf(str, "M1 %d", &penPos)==1){

			if (penPos <= 160 && penPos >= 80) {
				valid = true;
			} else {
				valid = false;
			}
		}else{
			valid = false;
		}
	}
	else if (strcmp("M4", code) == 0) {
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
	else if (strcmp("G1", code) == 0) {
		if(sscanf(array,"G1 X%f Y%f A%d", &x, &y, &a)==3){
			if (x <= xydriver->totalStepsX  && y <= xydriver->totalStepsY && (a >= 0 || a <= 100000 )) {
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
data GcodeParser::runCommand(){
	data d;
	if(valid==true){

		if (strcmp(code,"M10\n") == 0) {
			strcpy(d.command, code);
		}
		else if (strcmp(code,"M11\n") == 0) {
			strcpy(d.command, code);
			d.penP = penPos;
		}
		else if (strcmp(code,"M2") == 0) {
			strcpy(d.command, code);
			d.limUP = limUp;
			d.limDOWN = limDown;
		}
		else if (strcmp(code,"M1") == 0) {
			strcpy(d.command, code);
			d.penP = penPos;
		}
		else if (strcmp(code,"M4") == 0) {
			strcpy(d.command, code);
			d.laserPow = laserPwr;

		}
		else if (strcmp(code,"G28\n") == 0) {
			strcpy(d.command, code);

		}
		else if (strcmp(code,"G1") == 0) {
			strcpy(d.command, code);
			d.x = x;
			d.y = y;
		}
		return d;

	}else{
		return d;
	}
}

