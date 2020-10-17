/*
 * Parser.h
 *
 *  Created on: 1 Sep 2020
 *      Author: danie
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include "XYdriver.h"
#include "Laser.h"
#include "Servo.h"
#include "commandData.h"
using namespace std;



class GcodeParser {
private:
	float y,x;
	int a, limUp, limDown, penPos, laserPwr;
	bool valid;
	char fullCommand[100];
	char code[8];
	char error[12] = "error1";
public:
	GcodeParser(char *str, XYdriver *xydriver);
	virtual ~GcodeParser();
	data getData();
};


#endif /* PARSER_H_ */
