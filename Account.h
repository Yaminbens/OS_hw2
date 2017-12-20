/*
 * Account.h
 *
 *  Created on: Dec 2, 2017
 *      Author: control15
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "locker.h"

class Account {
private:
	int ID_;
	int balance_;
	int password_;
	bool VIP_;

public:
	Account ( const int ID, const int password, const int balance, bool VIP)
	{
		ID_ = ID;
		balance_ = balance;
		password_ = password;
		VIP_ = VIP;
	}

	~Account() {}

	int getID () const;
	int getBalance() const;
	int getPassword() const;
	bool isVIP() const;

	bool depodit (const int amount, const int password);
	int withdraw (const int amount, const int password);
	bool checkBalance (const int password, int& balance);
	bool setVIP (const int password);
	bool setBalance (const int balance);

/*
	void deposit_for_bank(const int money_to_deposit);
*/
	locker accLocker;



};




#endif /* ACCOUNT_H_ */
