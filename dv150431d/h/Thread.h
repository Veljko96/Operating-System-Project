/*
 * Thread
 *
 *  Created on: May 12, 2017
 *      Author: OS1
 */

#ifndef _THREAD_H_
#define _THREAD_H_

typedef unsigned long StackSize;
typedef unsigned int Time;
typedef int ID;

class PCB;


const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2;

class Thread {

public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);

protected:

	friend class PCB;
	friend class idleThread;
	friend class System;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

public:

	PCB* myPCB;


};

void dispatch();
extern void tick();
Time minTimeSlice();



#endif
