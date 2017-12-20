/*
 * ATM.h
 *
 *  Created on: Dec 18, 2017
 *      Author: control15
 */

#ifndef ATM_H_
#define ATM_H_

#include "Account.h"
#include "bank.h"
#include "logs.h"
#include "locker.h"

using namespace std;

struct Thread
{
	bank* myBank;
	int id;
	string src;
};


void atm(bank* myBank, string src, int id)
{
	ifstream commands (src.c_str());
	string toDo;
	while (getline(commands, toDo))
	{
		myBank->bExec(id, toDo);
		sleep(100);
	}
	return;
}


// For c pthread
void* atmForThread(void* arguments)
{
	Thread* args = (Thread*)arguments;
	atm(args->myBank, args->src, args->id);
	return NULL;
}


#endif /* ATM_H_ */
