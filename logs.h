/*
 * logs.h
 *
 *  Created on: Dec 13, 2017
 *      Author: control15
 */

#ifndef LOGS_H_
#define LOGS_H_

#include "locker.h"
#include <fstream>
#include <string>
#include "pthread.h"
#include <iostream>

using namespace std;

class logs
{
	private:
		ofstream log; //!< Member variable "log"
		locker logLocker; //!< Member variable "log_lock"

	public:
		logs() {log.open("log.txt");}
		~logs() {log.close();}

		void writeLog(string str);

};


#endif /* LOGS_H_ */
