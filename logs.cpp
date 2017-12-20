/*
 * logs.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: control15
 */

#include "logs.h"

void logs::writeLog(string str)
{
	logLocker.write();

	log << str << endl;

	logLocker.writeStop();
}
