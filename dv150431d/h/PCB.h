#ifndef _PCB_H_
#define _PCB_H_

#include "Thread.h"
#include "myqueue.h"

class Queue;
class Thread;
class KernelSem;

class PCB {

public:

	static ID sid;
	ID id;

	Thread* myThread;

	static const int New, Ready, Over, Blocked;
	volatile unsigned int state;

	Queue* pcbQueue;
	static Queue allPCB;

	unsigned int ss, sp, bp;

	Time pcbTimeSlice;
	volatile Time passedTime;
	Time waitTime;

	StackSize pcbStackSize;
	unsigned* pcbSP;

	int flag;

	PCB(StackSize stackSize, Time timeSlice, Thread* t);
	~PCB();

	void createStack();
	static void wrapper();

};

#endif
