/*
 * locker.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: control15
 */


#include "locker.h"


/***********************************************************************************************/

// When a reader wants to start reading, we check if there are any active readers.
// If so, they will read first. If not, the reader can read, so it needs to catch the readers mutex and then the writers locks
void locker::read()
{
    pthread_mutex_lock(&readLockNum);

    if(readersNum < 1)
    {
		pthread_mutex_lock(&readLock);
		readersNum = 1;
    }
    else
    {
		readersNum += 1;
    }
    pthread_mutex_unlock(&readLockNum);
}

// readStop is called when a reader wants to finish.
// we keep the locks locked other reading processes.// if there aren't any (this is the last reader) we free the locks.
void locker::readStop()
{
    pthread_mutex_lock(&readLockNum);

    if(readersNum > 1)
    {
		readersNum -= 1;
    }
    else
    {
    	pthread_mutex_unlock(&readLock);
		readersNum = 0;
    }

    pthread_mutex_unlock(&readLockNum);
}

// start_writing is called when a writer wants to start.
//there can only be one writer at a time
void locker::write()
{
    pthread_mutex_lock(&writeLock);
}

// writeStop is called when a writer wants to finish.
//there can only be one writer at a time
void locker::writeStop()
{
	pthread_mutex_unlock(&writeLock);
}

