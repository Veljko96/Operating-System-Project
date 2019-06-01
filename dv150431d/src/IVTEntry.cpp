/*
 * IVTEntry.cpp
 *
 *  Created on: May 23, 2017
 *      Author: OS1
 */
#include "IVTEntry.h"
#include "event.h"
#include "KernelEv.h"
#include "system.h"
#include <dos.h>

IVTEntry* IVTEntry::IVT[256];

IVTEntry::IVTEntry(IVTNo i, InterruptFunc newF) {

	lock();

	myIvtN = i;
	newFunc = newF;
	oldFunc = 0;
	myEvent = 0;


	#ifndef BCC_BLOCK_IGNORE
	oldFunc=getvect(myIvtN);
	setvect(myIvtN,newFunc);
	#endif

	IVT[myIvtN] = this;

	unlock();
}

void IVTEntry::setMyEvent(KernelEvent* event) {

	lock();

	myEvent = event;

	unlock();
}

void IVTEntry::deleteMyEvent() {

	lock();

	myEvent = 0;

	unlock();
}

void IVTEntry::signalMyEvent() {

	lock();

	if(myEvent == 0) return;
	myEvent->signal();

	unlock();
}

void IVTEntry::callOldRoutine() {

	(*oldFunc)();

}

IVTEntry::~IVTEntry() {

	IVT[myIvtN] = 0;
	//(*oldFunc)();
	lock();

	#ifndef BCC_BLOCK_IGNORE
	setvect(myIvtN, oldFunc);
	#endif

	unlock();
}

