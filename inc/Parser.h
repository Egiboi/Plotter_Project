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
using namespace std;



class GcodeParser {
private:
	float y,x;
	int a, limx, limy, penPos, laserPwr;
	char Cmnd[10];
	bool valid;
	char fullCommand[100];


public:
	GcodeParser(string str);
	virtual ~GcodeParser();
	bool runCommand(XYdriver *driver,Laser *laser, Servo *servo);
};


#endif /* PARSER_H_ */
