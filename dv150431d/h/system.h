#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "Thread.h"
#include "PCB.h"
#include "idlethr.h"
#include "KernelS.h"
#include "BlockedQ.h"

// imace ovde jos da se radi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

typedef void interrupt(*InterruptRoutine)(...);

#define lock() { asm {pushf}; asm {cli}; }
#define unlock() { asm{popf;} }




class System {

public:

	static void prepare();
	static void end();
	static volatile char dispatched;
	static void interrupt timer(...);
	static int lockFlag;


private:

	friend class Thread;
	friend class PCB;
	friend class KernelEvent;
	friend class KernelSem;
	friend class Queue;
	//ovde ima jos da se radi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	static Thread* starter;

	static InterruptRoutine oldRoutine;


	static volatile PCB* running;
	static idleThread* idle;




};




#endif

