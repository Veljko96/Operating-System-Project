/*
 * KernelS.h
 *
 *  Created on: May 24, 2017
 *      Author: OS1
 */

#ifndef _KERNELS_H_
#define _KERNELS_H_

typedef unsigned int Time;

#include "BlockedQ.h"

class KernelSem{
public:

	KernelSem(int init);
	~KernelSem();
	int wait (Time maxTimeToWait);
	void signal();
	int getValue () const;
	static BlockedQ sList;
	static Queue queue;
	friend class Queue;

private:

	Queue* myQueue;
	int value;

};




#endif /* KERNELS_H_ */
