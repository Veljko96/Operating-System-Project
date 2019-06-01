#include "system.h"
#include "SCHEDULE.h"
#include "Thread.h"
#include "PCB.h"
#include <stdlib.h>
#include <dos.h>
#include <iostream.h>
#include "myqueue.h"

class Scheduler;
class System;

Thread::Thread(StackSize stackSize, Time timeSlice) {

	lock();

	myPCB = new PCB(stackSize, timeSlice, this);

	unlock();




}

void Thread::start() {

	lock();

	myPCB->state = PCB::Ready;
	myPCB->createStack();
	Scheduler::put(myPCB);



	unlock();
}

void Thread::waitToComplete() {

	lock();


	if (myPCB->state == PCB::Over) {

		unlock();
		return;
	}

	if (myPCB->state == PCB::New) {

			unlock();
			return;
		}

	if (myPCB == (PCB*)System::running) {

		unlock();
		return;
	}

	if (this == System::idle) {

			unlock();
			return;
		}

	if (this == System::starter) {

		unlock();
		return;
	}

	System::running->state = PCB::Blocked;
	myPCB->pcbQueue->put((PCB*)System::running);

	unlock();

	dispatch();


}


ID Thread::getId() { return myPCB->id; }

ID Thread::getRunningId() { return System::running->id; }

Thread* Thread::getThreadById(ID id) {

	PCB::allPCB.currentToFirst();
	PCB *pom = 0;
	pom = PCB::allPCB.getCurrent();

	while(pom->id != id && pom != 0) {

		PCB::allPCB.next();
		pom = PCB::allPCB.getCurrent();
	}

	PCB::allPCB.currentToFirst();

	if (pom->id == id) return pom->myThread;

	return 0;
}

void dispatch() {

	lock();

	System::dispatched = 1;

	System::timer();

	System::dispatched = 0;

	unlock();

}

//void tick() {};

Time minTimeSlice() { return 1; }

Thread::~Thread() {

	lock();


	delete myPCB;

	unlock();
}




