/*
 * Account.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: control15
 */
#include "Account.h"

	int Account::getID () const {
		return ID_;
	}
	int Account::getBalance() const {
		return balance_;
	}
	int Account::getPassword() const {
		return password_;
	}
	bool Account::isVIP() const {
		return VIP_;
	}

	bool Account::depodit (const int amount, const int password) ///MAYA: if we also need to check if amount>=0 then we can return int instead of bool
	{
		if (password!=password_)
			return false;
		balance_ += amount;
		return true;
	}

	int Account::withdraw (const int amount, const int password) ///MAYA: if we also need to check if amount>=0 then we can return int instead of bool
	{
		if (password!=password_)
			return -1;
		if (balance_<amount)
			return 0;
		balance_ -= amount;
		return 1;
	}

	bool Account::checkBalance (const int password, int& balance)
	{
		if (password!=password_)
			return false;
		balance = balance_;
		return true;
	}

	bool Account::setVIP(const int password)
	{
		if (password!=password_)
			return false;
		VIP_ = true;
		return true;
	}

	bool Account::setBalance (const int balance)
	{
		if (balance<0)
			return false;
		balance_ = balance;
		return true;
	}



