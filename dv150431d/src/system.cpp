#include "system.h"
#include "SCHEDULE.h"
#include <stdlib.h>
#include <dos.h>
#include <iostream.h>
#include <stdio.h>

volatile PCB* System::running = 0;
volatile char System::dispatched = 0;
idleThread* System::idle = 0;
Thread* System::starter = 0;
InterruptRoutine System::oldRoutine = 0;
int System::lockFlag = 1;


unsigned oldTimerOFF, oldTimerSEG;


void System::prepare() {

	lock();

	#ifndef BCC_BLOCK_IGNORE

	oldRoutine = getvect(0x08);
	setvect(0x60, oldRoutine);
	setvect(0x08, timer);

	#endif

	starter = new Thread(0x10000, minTimeSlice());
	starter->myPCB->state = PCB::Ready;
	running = (volatile PCB*)starter->myPCB;
	idle = new idleThread();
	idle->start();

	unlock();

}

void System::end() {

	if ((PCB*)running != starter->myPCB) return;

	lock();
	#ifndef BCC_BLOCK_IGNORE

	setvect(0x08, oldRoutine);

	#endif
	delete starter;
	delete idle;

	unlock();
}



void interrupt System::timer(...) {

	static volatile unsigned int tsp, tss, tbp;
	static volatile PCB* newThread;

	if (!dispatched) {

		tick();
		#ifndef BCC_BLOCK_IGNORE
		asm int 60h;
		#endif
	}

	if (!dispatched && (running->pcbTimeSlice != 0))
		running->passedTime += minTimeSlice();

	if (!dispatched) {

		KernelSem::queue.sub();
	}

	if(!dispatched &&(running->passedTime < running->pcbTimeSlice || running->pcbTimeSlice == 0)) return;

	if (lockFlag) {

		dispatched = 0;

		if ((running->state == PCB::Ready) && (running != idle->myPCB)) {

			Scheduler::put((PCB*)running);

		}


		newThread = Scheduler::get();

		if (newThread == 0) newThread = idle->myPCB;
		//if (newThread->state != PCB::Ready) continue;

		#ifndef BCC_BLOCK_IGNORE
		asm {

			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
		#endif


		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;
		running = newThread;
		tsp = running->sp;
		tss = running->ss;
		tbp = running->bp;

		#ifndef BCC_BLOCK_IGNORE

		asm {

			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}

		#endif

		running->passedTime = 0;

	}
}





