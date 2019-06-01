/*
 * BlockedQ.h
 *
 *  Created on: May 24, 2017
 *      Author: OS1
 */

#ifndef _BLOCKEDQ_H_
#define _BLOCKEDQ_H_


class KernelSem;

class BlockedQ{

	struct Str{
	KernelSem* sem;
	Str* next;
	Str(KernelSem* p, Str* sled = 0){

		sem = p;
		next = sled;
	}
};
	Str* head,*last;
	friend class KernelSem;
	friend class Queue;
public:
	BlockedQ();
	void put(KernelSem* p);
	void remove(KernelSem* p);
	int isEmpty();
	~BlockedQ();
};
#endif

