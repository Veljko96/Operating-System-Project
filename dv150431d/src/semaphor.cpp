#include "semaphor.h"
#include "KernelS.h"

Semaphore::Semaphore(int init) {

	myImpl=new KernelSem(init);
}

int Semaphore::wait(Time maxTimeToWait) {

	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal() {

	myImpl->signal();
}

int Semaphore::val() const {

	return myImpl->getValue();
}

Semaphore::~Semaphore() {

	delete myImpl;
}



