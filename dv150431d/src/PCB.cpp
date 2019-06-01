#include "system.h"
#include "PCB.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>
#include <SCHEDULE.h>

const int PCB::New = 0;
const int PCB::Ready = 1;
const int PCB::Over = 2;
const int PCB::Blocked = 3;

ID PCB::sid = -2;

Queue PCB::allPCB = Queue();

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* t) {

	lock();

	id = ++PCB::sid;
	pcbStackSize = stackSize;
	pcbTimeSlice = timeSlice;
	state = New;
	myThread = t;
	pcbSP = 0;
	passedTime = 0;
	pcbQueue = new Queue();
	waitTime = 0;
	flag = 0;
	allPCB.put(this);

	unlock();


}

void PCB::createStack() {



	int n = 0;
	n = this->pcbStackSize;
	n = n / sizeof(unsigned);
	unsigned* st = new unsigned[n];

	this->pcbSP = st;

	#ifndef BCC_BLOCK_IGNORE
	st[n-1] = 0x200;
	st[n-2] = FP_SEG(&(wrapper));
	st[n-3] = FP_OFF(&(wrapper));

	this->ss = FP_SEG(st+n-12);
	this->sp = FP_OFF(st+n-12);
	this->bp = FP_OFF(st+n-12);
	#endif


}

void PCB::wrapper() {

	System::running->myThread->run();

	lock();

	System::running->state = PCB::Over;
	PCB *temp = 0;


	while (System::running->pcbQueue->size() > 0) {

		temp = System::running->pcbQueue->get();
		temp->state = PCB::Ready;
		Scheduler::put(temp);

	}

	unlock();

	dispatch();


}

PCB::~PCB() {

	lock();


	delete pcbSP;
	delete pcbQueue;

	unlock();
}




