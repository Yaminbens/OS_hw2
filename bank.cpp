/*
 * bank.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: control15
 */
#include "bank.h"
#include <string>
#include <sstream>

using namespace std;

	list<Account>::iterator bank::iter(const int index)
	{
		list<Account>::iterator it = Accounts_.begin();
		for (int i = 0; i < this->getIdx(index); i++) {
			it++;
		}
		return it;
	}

	int bank::getIdx(const int ID)
	{
		bankLocker.read();
		int index = 0;
	    list<Account>::iterator it;
	    for( it = Accounts_.begin(); it != Accounts_.end(); it++)
	    	index+=1;
	   		if(ID == it->getID())
	        {
	   			bankLocker.readStop();
	            return index;
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
   			///MAYA: add here--					sleep_one_sec;
			string toPrint;
			toPrint = toString(ATM_ID) + ": New account id is"+ toString(ID) + " with password " + toString(password) + " and initial balance " + toString(amount);
			Accounts_.push_back(account);
			log.writeLog(toPrint);
   			bankLocker.writeStop();
   			return success;
		}
	}

	int bank::transation (const int src, int &balance1, const int dest,  int &balance2, const int password, const int ID, const int ampunt)
	{
		////MAYA: TODO BOM
	}

	int bank::deposit (const int ID, const int password, const int amount, int &sum, const int id)
	{
		////MAYA: TODO BOM
	}

	int bank::withdraw (const int ID, const int password, const int amount, int &balance, int id)
	{
		////MAYA: TODO BOM
	}

	int bank::getBalance (const int ID, const int password, int& outBalance, int id)
	{
		////MAYA: TODO BOM
	}

	int bank::upgrade (const int ID, const int password)
	{
		////MAYA: TODO BOM
	}

	int bank::takeCommission ()
	{
		////MAYA: TODO BOM
	}

	int bank::accountError1(const int ID)
	{
		string toPrint;
		toPrint = "Error " + toString(ID) + ": Your transaction failed - account with the same id exists";
		log.writeLog(toPrint);
		return 4;
	}

	int bank::accountError2(const int ID1, const int ID2)
	{
		string toPrint;
		toPrint = "Error " + toString(ID1) + ": Your transaction failed - account id " + toString(ID2) + " does not exist";
		log.writeLog(toPrint);
		return 5;
	}

///MAYA: I think this is not needed:
/*	int bank::accountError3(const int ID)
	{
		toPrint = "Error " + std::to_string(ID) + ": Your transaction failed - account with the same id exists";
		///MAYA: add here--			write_to_log_.writeLog(toPrint);
		return 6;
	}
*/
