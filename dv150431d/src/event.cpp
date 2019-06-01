#include "event.h"
#include "system.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo) {

	lock();

	myImpl = new KernelEvent(ivtNo);

	unlock();
}

void Event::wait() {

	lock();

	myImpl->wait();

	unlock();
}

void Event::signal() {

	lock();

	myImpl->signal();

	unlock();
}

Event::~Event() {

	lock();

	delete myImpl;

	unlock();
}




