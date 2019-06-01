#include "KernelS.h"
#include "system.h"
#include "PCB.h"
#include "myqueue.h"
#include "SCHEDULE.h"

BlockedQ KernelSem::sList = BlockedQ();

Queue KernelSem::queue =  Queue();

KernelSem::KernelSem(int init) {



	value = init;
	myQueue = new Queue();
	sList.put(this);


}

int KernelSem::wait(Time maxTimeToWait) {

	lock();

	if(--value<0) {



		if(maxTimeToWait>0)
		{
			System::running->waitTime = maxTimeToWait;
			queue.put((PCB*)System::running);

		}

		System::running->state=PCB::Blocked;
		if(myQueue != 0)
			myQueue->put((PCB*)System::running);

		unlock();

		dispatch();

		lock();

		if (System::running->flag == 1) {

			System::running->flag = 0;
			unlock();
			return 1;
		}

		unlock();
		return 0;

	}

	unlock();
	return 1;
}

void KernelSem::signal() {

	lock();

	if(value++<0) {

		PCB* pcb=myQueue->get();
		pcb->state=PCB::Ready;
		pcb->flag=1;

		if(pcb->waitTime>0)
		{
			queue.remove(pcb);

		}

		if(pcb != System::idle->myPCB) {

			Scheduler::put(pcb);
		}
		unlock();
		}
	else {

		unlock();
	}
}

int KernelSem::getValue() const {

	return value;
}

KernelSem::~KernelSem() {



	if(myQueue != 0){

		Elem* curr = myQueue->first;

		while(curr!= 0)
		{
			PCB* pcb = myQueue->get();
			pcb->state=PCB::Ready;

			if(pcb != System::idle->myPCB && pcb != System::starter->myPCB)	{

				Scheduler::put(pcb);
			}

			curr=myQueue->first;
		}

		delete myQueue;
		if(!sList.isEmpty())
			sList.remove(this);

	}

}
