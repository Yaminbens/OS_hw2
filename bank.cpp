/*
 * bank.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: control15
 */

#include "bank.h"

//#include <boost/math/special_functions/round.hpp>

using namespace std;

	list<Account>::iterator bank::iter(const int index)
	{
		list<Account>::iterator it = Accounts_.begin();
		for( it = this->Accounts_.begin(); it != this->Accounts_.end(); it++) {
			if(it->getID() == index){
				return it;
			}
		}
		return it;
	}

	int bank::getIdx(const int ID)
	{
		bankLocker.read();
		int index = 0;
	    list<Account>::iterator it;
	    for( it = this->Accounts_.begin(); it != this->Accounts_.end(); it++) {
	    	index+=1;
	   		if(ID == it->getID())
	        {
	   			bankLocker.readStop();
	            return index;
	        }
	    }
		bankLocker.readStop();
		return -1; // wasn't found
	}

	int bank::newAccount(const int ATM_ID, const int ID, const int password, const int amount, const bool VIP)
	{
		if(amount < 0 )
	    {
	        return balanceError;
	    }
		else if (this->getIdx(ID) > -1 ) //found the same ID
		{
	        return accountError1(ID);
	    }
		else // valid parameters
		{
			Account account(ID, password, amount,VIP);
   			bankLocker.write();
   			sleep(1);
			string toPrint;
			toPrint = toString(ATM_ID) + ": New account id is"+ toString(ID) + " with password " + toString(password) + " and initial balance " + toString(amount);
			Accounts_.push_back(account);
			log.writeLog(toPrint);
   			bankLocker.writeStop();
   			return success;
		}
	}

	int bank::transaction (const int src, int &srcBalance, const int dest,  int &dstBalance, const int password, const int ATM_ID, const int amount)
	{
		int srcIdx = this->getIdx(src);
		int dstIdx = this->getIdx(dest);

		string toPrint;
		if(dstIdx == -1)
		{
/*	    	toPrint ="Error " + toString(ID) + ": Your transaction failed - account id " + toString(dst) +" does not exist";
			log.writeLog(toPrint);
*/
			return accountError2(ATM_ID, dest);
		}

		else if (srcIdx == -1)
	    {
/*			toPrint = "Error " + toString(ID) + ": Your transaction failed - account id " + toString(src) +" does not exist";
			log.writeLog(toPrint);
*/
			return accountError2(ATM_ID, src);
	    }

		else
		{
			// to prevent deadlocks: first try to catch the account with the lower index, and then the account with the higher index.
			int maxIdx = max(srcIdx, dstIdx);
			int minIdx = min(srcIdx, dstIdx);

			list<Account>::iterator maxListItr = Accounts_.begin();
			for (int i = 0; i < maxIdx; i++, maxListItr++);
			list<Account>::iterator minListItr = Accounts_.begin();
			for (int i = 0; i < minIdx; i++, minListItr++);

			minListItr->accLocker.write();
			if (minIdx < maxIdx)
			{
				maxListItr->accLocker.write();
			}

			list<Account>::iterator srcItr = iter(src);
			list<Account>::iterator destItr = iter(dest);

			int res = srcItr->withdraw(amount, password);
			sleep(1);
			switch (res)
			{
			case -1:
				return accountError3(ATM_ID, src);
				break;
			case 0:
				toPrint = "Error " + toString(ATM_ID) + ": Your transaction failed - account id " + toString(src) + " balance is lower than " + toString(amount);
				break;
			case 1:
				int srcBalance = srcItr->getBalance();
				int destBalance = destItr->getBalance();
				toPrint = toString(ATM_ID) + ": Transfer " + toString(amount) + " from account " + toString(src) + " to account " + toString(dest) + " new account balance is " + toString(srcBalance) + " new target account balance is " + toString(destBalance);
				break;
			}
			log.writeLog(toPrint);
			minListItr->accLocker.writeStop();
			if (minIdx < maxIdx)
			{
				maxListItr->accLocker.writeStop();
			}
			return res;
		}
	}

	int bank::deposit (const int ATM_ID, const int password, const int amount, int &sum, const int ID)
	{
		int idx = this->getIdx(ID);
		string toPrint;
		if(idx == -1)
		{
/*	    	toPrint ="Error " + toString(ID) + ": Your transaction failed - account id " + toString(dst) +" does not exist";
			log.writeLog(toPrint);
*/
			return accountError2(ATM_ID, ID);
		}
		else
		{
			list<Account>::iterator it = iter(ID);
			it->accLocker.write();
			int res = it->depodit(amount, password);
			sleep(1);
			if (res == -1)
			{
				return accountError3(ATM_ID, ID);
			}
			else
			{
				int newBalance = it->getBalance();
				toPrint = toString(ATM_ID) + ": Account " + toString(ID) + " new balance is " + toString(newBalance) + " after " + toString(amount) + " $ was deposited";
			}
			log.writeLog(toPrint);
			it->accLocker.writeStop();
			return res;
		}
	}

	int bank::withdraw (const int ATM_ID, const int password, const int amount, int &balance, int ID)
	{
		int idx = this->getIdx(ID);
		string toPrint;
		if(idx == -1)
		{
/*	    	toPrint ="Error " + toString(ID) + ": Your transaction failed - account id " + toString(dst) +" does not exist";
			log.writeLog(toPrint);
*/
			return accountError2(ATM_ID, ID);
		}
		else
		{
			list<Account>::iterator it = iter(ID);
			it->accLocker.write();
			int res = it->withdraw(amount, password);
			sleep(1);
			switch (res)
			{
			case -1:
				return accountError3(ATM_ID, ID);
				break;
			case 0:
				toPrint = "Error " + toString(ATM_ID) + ": Your transaction failed - account id " + toString(ID) + " balance is lower than " + toString(amount);
				break;
			case 1:
				int newBalance = it->getBalance();
				toPrint = ": Account " + toString(ATM_ID) + " new balance is " + toString(newBalance) + " after " + toString(amount) + " $ was deposited";
				break;
			}
			log.writeLog(toPrint);
			it->accLocker.writeStop();
			return res;
		}
	}

	int bank::getBalance (const int ATM_ID, const int password, int& outBalance, int ID)
	{
		int idx = this->getIdx(ID);
		string toPrint;
		if(idx == -1)
		{
/*	    	toPrint ="Error " + toString(ID) + ": Your transaction failed - account id " + toString(dst) +" does not exist";
			log.writeLog(toPrint);
*/
			return accountError2(ATM_ID, ID);
		}
		else
		{
			list<Account>::iterator it = iter(ID);
			it->accLocker.read();
			int res = it->checkBalance(password, outBalance);
			sleep(1);
			if (res == false)
			{
				return accountError3(ATM_ID, ID);
			}
			else
			{
				toPrint =  toString(ATM_ID) + ": Account " + toString(ID) + " balance is " + toString(it->getBalance());
			}
		log.writeLog(toPrint);
		it->accLocker.readStop();
		return res;
		}
	}

	int bank::upgrade (const int ATM_ID, const int ID, const int password)
	{
		int idx = this->getIdx(ID);
		string toPrint;
		if(idx == -1)
		{
			return accountError2(ATM_ID, ID);
		}
		else
		{
			list<Account>::iterator it = iter(ID);
			it->accLocker.write();
			int res = it->setVIP(password);
			sleep(1);
			if (res == false)
			{
				return accountError3(ATM_ID, ID);
			}
			log.writeLog(toPrint);
			it->accLocker.writeStop();
			return res;
		}
	}

	int bank::accountError1(const int ATM_ID)
	{
		string toPrint;
		toPrint = "Error " + toString(ATM_ID) + ": Your transaction failed - account with the same id exists";
		log.writeLog(toPrint);
		return 4;
	}

	int bank::accountError2(const int ATM_ID, const int ID)
	{
		string toPrint;
		toPrint = "Error " + toString(ATM_ID) + ": Your transaction failed - account id " + toString(ID) + " does not exist";
		log.writeLog(toPrint);
		return 5;
	}

	int bank::accountError3(const int ATM_ID, const int ID)
	{
		string toPrint;
		toPrint = "Error " + toString(ATM_ID) + ": Your transaction failed - password for account id " + toString(ID) + " is incorrect";
		log.writeLog(toPrint);
		return 6;
	}


	void bank::takeCommission ()
	{
		double Rand;
		int comm;
		while(finishedFlag == false)
		{
			Rand = (rand()%200 + 200)/100;
			//Accounts_.begin()->accLocker.write();
			for(list<Account>::iterator it = Accounts_.begin(); it!=Accounts_.end(); ++it)
			{
				if (it->getID() == -1) continue;
				if (it->isVIP()) continue;

				it->accLocker.write();
				string toPrint;
				comm = roundf((it->getBalance()*Rand)/100);
				int newBalance = it->getBalance()-comm;
//				cout << "new balance" << newBalance << endl;
				it->setBalance(newBalance);

				Accounts_.begin()->setBalance(Accounts_.begin()->getBalance()+comm);

				stringstream str;
				str << fixed << setprecision(2) << Rand;
				toPrint ="Bank: commissions of " + str.str() + " % were charged, the bank gained " + toString(comm) + " $ from account " + toString(it->getID());
				log.writeLog(toPrint);
				it->accLocker.writeStop();
			}
			Accounts_.begin()->accLocker.writeStop();
			sleep(3);
		}
	}

	void bank::bExec(int ATM_ID, string command)
	{
		int arg1, arg2, arg3, arg4;
		int balance1, balance2;
	    string cmd;
	    stringstream str_stream(command);
	    str_stream >> cmd;

	    getline(str_stream,command);

	    istringstream stream(command);
	    stream >> arg1;
	    stream >> arg2;
	    stream >> arg3;
	    stream >> arg4;

	    if (cmd == "O") {
	        newAccount(ATM_ID,arg1,arg2,arg3,false);
	        // newAccount(const int ATM_ID, const int ID, const int password, const int amount, const bool VIP)
	        // O <account> <password> <initial_amount>
	    } else if (cmd == "L") {
	    	upgrade(ATM_ID, arg1, arg2);
	    	// upgrade (const int ATM_ID, const int ID, const int password)
	    	// L <account> <password>
	    } else if (cmd == "D") {
	        deposit(ATM_ID,arg2, arg3, balance1,arg1);
	        // deposit (const int ATM_ID, const int password, const int amount, int &sum, const int ID)
	        // D <account> <password> <amount>
	    } else if (cmd == "W") {
	    	withdraw(ATM_ID, arg2, arg3, balance1, arg1);
	    	// withdraw (const int ATM_ID, const int password, const int amount, int &balance, int ID)
	    	// W <account> <password> <amount>
	    } else if (cmd == "B") {
	    	getBalance(ATM_ID, arg2, balance1, arg1);
	    	// getBalance (const int ATM_ID, const int password, int& outBalance, int ID)
	    	// B <account> <password>
	    } else if (cmd == "T") {
			transaction(arg1, balance1, arg3, balance2, arg2, ATM_ID, arg4);
			// transaction (const int src, int &srcBalance, const int dest,  int &dstBalance, const int password, const int ATM_ID, const int amount)
			// T <account> <password> <target_account> <amount>
	    }
	}

	void bank::printStatus()
	{
	    while (this->finishedFlag == 0)
	    {
	    	sleep(0.5);  //MAYA: delete this??
	        for(list<Account>::iterator it=Accounts_.begin(); it!=Accounts_.end(); ++it)
	            it->accLocker.read();
	        	cout << "\033[2J\033[1;1H";
	        	cout << "Current Bank Status" << endl;

	        for(list<Account>::iterator it=Accounts_.begin(); it!=Accounts_.end(); ++it)
	        {
	        	int accID = it->getID();
	            if(accID == -1)
	                continue;

	            cout << "Account " << accID << ": Balance - " << it->getBalance() << " , Account Password - " << it->getPassword() << endl;
	        }
	        cout << "The Bank has " << Accounts_.begin()->getBalance() << " $" << endl;

	        for(list<Account>::iterator it = Accounts_.begin(); it!=Accounts_.end(); ++it)
	            it->accLocker.readStop();
	    }
	}

	void* bank::commForThread(void* input)
	{
		bank* myBank = (bank*)input;
		myBank->takeCommission();
		return NULL;
	}

	void* bank::statusForThread(void* input)
	{
		bank* myBank = (bank*)input;
		myBank->printStatus();
		return NULL;
	};
