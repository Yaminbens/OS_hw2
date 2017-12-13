/*
 * Account.h
 *
 *  Created on: Dec 2, 2017
 *      Author: control15
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_


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

/*
	void deposit_for_bank(const int money_to_deposit);
	void change_bank_balance(int balance);
	Locks account_lock_; //!< Member variable "account_lock"
*/


};




#endif /* ACCOUNT_H_ */
