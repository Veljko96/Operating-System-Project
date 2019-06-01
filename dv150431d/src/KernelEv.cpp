/*
 * KernelEv.cpp
 *
 *  Created on: May 23, 2017
 *      Author: OS1
 */
#include "IVTEntry.h"
#include "KernelEv.h"
#include "SCHEDULE.h"
#include "Thread.h"
#include "system.h"

KernelEvent::KernelEvent(IVTNo ivt) {

	ivtNo = ivt;
	creator = (PCB*)System::running;
	value = 0;
	IVTEntry::IVT[ivtNo]->setMyEvent(this);
	isBlocked = 0;
}

void KernelEvent::wait() {

	lock();

	if ((PCB*)System::running != creator) return;

	if (value == 0) {

		creator->state = PCB::Blocked;
		isBlocked = 1;
		unlock();
		dispatch();
		lock();
	}
	else {

		if (value == 1) value--;
	}

	unlock();

}

void KernelEvent::signal() {

	lock();

	if(isBlocked == 0) value = 1;
	else {

		creator->state = PCB::Ready;
		if (creator != System::idle->myPCB)
			Scheduler::put(creator);
		isBlocked = 0;
		unlock();
		dispatch();
		lock();
	}

	unlock();
}

KernelEvent::~KernelEvent() {

	lock();

	IVTEntry::IVT[ivtNo]->deleteMyEvent();

	unlock();
}



