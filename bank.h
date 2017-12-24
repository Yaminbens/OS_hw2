/*
 * bank.h
 *
 *  Created on: Dec 2, 2017
 *      Author: control15
 */
#include "Account.h"
#include "locker.h"
#include "logs.h"
#include <list>
#include <string>
#include <sstream>
#include <pthread.h>
//#include <chrono>
#include "unistd.h"
#include <math.h>

#include <iomanip>
#include <cstdlib>

using namespace std;

#ifndef BANK_H_
#define BANK_H_

#define success 0
#define passwordError 1
#define balanceError 2
#define withdrawDepositError 3


class bank {
public:
	list<Account> Accounts_;
	locker bankLocker;

	logs log;

public:
	bank()
	{
		Account bankAccount(0, 0, 0, true );
		Accounts_.push_back(bankAccount);
		finishedFlag = false;// money for the bank ///MAYA: right values??
	}
	~bank(){}

	list<Account>::iterator iter(const int index);
	int getIdx(const int ID);
	int newAccount(const int ATM_ID, const int ID, const int password, const int amount, const bool VIP);
	int transaction (const int src, int &srcBalance, const int dest,  int &dstBalance, const int password, const int ATM_ID, const int amount);

	int deposit (const int ATM_ID, const int password, const int amount, int &sum, const int ID);
	int withdraw (const int ATM_ID, const int password, const int amount, int &balance, int ID);
	int getBalance (const int ATM_ID, const int password, int& outBalance, int ID);
	int upgrade (const int ATM_ID, const int ID, const int password);

	int accountError1(const int ID);
	int accountError2(const int ID1, const int ID2);
	int accountError3(const int ATM_ID, const int ID);

	void takeCommission ();
	void bExec(int ATM_ID, string cmd);

	void printStatus();
	static void* commForThread(void* input);
	static void* statusForThread(void* input);

	bool finishedFlag;
};


template <typename T>
std::string toString(const T& temp)
{
	std::stringstream string_stream;
	string_stream << temp;

	return string_stream.str();
}

#endif /* BANK_H_ */
