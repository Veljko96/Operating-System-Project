#ifndef _IDLETHR_H_
#define _IDLETHR_H_

#include "Thread.h"

class Thread;

class idleThread : public Thread {
public:
	idleThread();
	virtual void run();
	void start();

};



#endif /* IDLETHR_H_ */
