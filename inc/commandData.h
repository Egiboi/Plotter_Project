/*
 * commandData.h
 *
 *  Created on: 14.10.2020
 *      Author: winte
 */

#ifndef COMMANDDATA_H_
#define COMMANDDATA_H_

struct data {
	char command[16];
	double x = -1.0;
	double y = -1.0;
	int penP = 0;
	int laserPow = 0;
	long totalX = 0;
	long totalY = 0;
	int limUP = 0;
	int limDOWN = 0;

	char error[16] = "Error!\r\n";

};



#endif /* COMMANDDATA_H_ */
