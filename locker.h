/*
 * locker.h
 *
 *  Created on: Dec 13, 2017
 *      Author: control15
 */

#ifndef LOCKER_H_
#define LOCKER_H_
#include <string>
#include <pthread.h>
#include <iostream>
//#include <fstream>

using namespace std;

class locker
{
	private:
		int readersNum;
		pthread_mutex_t readLock;
		pthread_mutex_t readLockNum;
		pthread_mutex_t writeLock;

	public:
	locker()
		{
			readersNum = 0;
			if ( pthread_mutex_init(&readLock, NULL)|| pthread_mutex_init(&readLockNum, NULL) || pthread_mutex_init(&writeLock, NULL) )
			{
				cout << "ERROR: failed when initializing the mutex" << endl;
//erase?				exit(1);
			}
		}

//	~locker();
	// We will first try to catch the read lock
	void read();
	void readStop();
	// then the write lock
	void write();
	void writeStop();

};

#endif
