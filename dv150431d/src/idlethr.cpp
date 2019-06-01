#include "system.h"
#include "idlethr.h"
#include "PCB.h"

idleThread::idleThread(): Thread(256, minTimeSlice()) {}

void idleThread::run() {
	while (1);
}

void idleThread::start() {
	lock();

	myPCB->state = PCB::Ready;
	myPCB->createStack();
	//jedina razlika od start() f-je klase Thread je sto
	//se idle nit ne stavlja u Scheduler

	unlock();
}









