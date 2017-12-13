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

using namespace std;

#ifndef BANK_H_
#define BANK_H_

#define success 0
#define passwordError 1
#define balanceError 2
#define withdraw_or_deposit_error 3


class bank {
private:
	list<Account> Accounts_;
	locker bankLocker;

	logs log;
	bool finished;

public:
	bank()
	{
		Account bankAccount(0, 0, 0, true); // saves money for the bank ///MAYA: right values?
	}
	~bank(){}

	int takeCommission ();

	list<Account>::iterator iter(const int index);
	int getIdx(const int ID);
	int newAccount(const int ATM_ID, const int ID, const int password, const int amount, const bool VIP);
	int transation (const int src, int &balance1, const int dest,  int &balance2, const int password, const int ID, const int ampunt);


	int deposit (const int ID, const int password, const int amount, int &sum, const int id);
	int withdraw (const int ID, const int password, const int amount, int &balance, int id);
	int getBalance (const int ID, const int password, int& outBalance, int id);
	int upgrade (const int ID, const int password);

	int accountError1(const int ID);
	int accountError2(const int ID1, const int ID2);

};


template <typename T>
std::string toString(const T& temp)
{
	std::stringstream string_stream;
	string_stream << temp;

	return string_stream.str();
}

#endif /* BANK_H_ */
