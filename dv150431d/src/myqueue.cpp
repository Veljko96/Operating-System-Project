#include "myqueue.h"
#include "system.h"
#include <stdlib.h>
#include<iostream.h>
#include "BlockedQ.h"
#include "SCHEDULE.H"
#include "KernelS.h"

Queue::Queue() {

	lock();

	first = 0;
	last = 0;
	current = 0;
	length = 0;

	unlock();
}

int Queue::size() const { return length; }

void Queue::put(PCB* p) {

	lock();
	Elem *temp = new Elem(p);

	/*for (temp = first; temp != 0; temp = temp->next) {

		if (temp->pcb == p) { unlock(); return; }

	}*/

	temp->next = 0;
	if (first == 0) first = temp;
	else last->next = temp;
	last = temp;
	length++;

	unlock();
}

PCB* Queue::get() {

	if (first == 0) {

		last = 0;
		return 0;
	}

	lock();

	Elem *temp = 0;
	temp = first;
	first = first->next;
	length--;

	unlock();

	return temp->pcb;
}

PCB* Queue::getCurrent() {

	return current->pcb;

}

void Queue::currentToFirst() {

	current = first;
}

void Queue::next() {

	current = current->next;
}

int Queue::remove(PCB* p)
{

	lock()
	Elem* prev = first;

	if(first == 0) {

		unlock()
		return 0;
	}

	Elem* curr = first;
	while(curr!=0 && curr->pcb!=p) {

		prev=curr;
		curr=curr->next;
	}

	if(curr==0) {

		unlock();
		return 0;
	}
	if(first->pcb==p) {

		first=first->next;
		if(first == 0)
			last = 0;
	}
	else {
		if(last != 0 && last->pcb==p) {
			last = prev;
			last->next = 0;
		}
		else {
			prev->next=curr->next;
			curr->next = 0;
		}
	}
	delete curr;
	unlock();
	return 1;
}

void Queue::sub() {

	lock();
	Elem* curr = first;
	while(curr != 0)
	{
		curr->pcb->waitTime--;
		if(curr->pcb->waitTime == 0)
		{
			PCB* temp=curr->pcb;
			curr=curr->next;
			remove(temp);
			BlockedQ::Str* s = KernelSem::sList.head;
			while(s != 0) {

				int ret=s->sem->myQueue->remove(temp);
				if(ret == 1)
					s->sem->value++;
				s=s->next;
			}
			temp->state=PCB::Ready;

			if(temp != System::idle->myPCB) {

				Scheduler::put(temp);
			}
		}
		else
		curr=curr->next;
	}

	unlock();

}

int Queue::isEmpty() {

	lock();

	if (first == 0) {

		unlock();
		return 1;
	}

	unlock();
	return 0;
}

Queue::~Queue() {

	lock();

	Elem *temp = 0;

	while(first != 0) {

		temp = first;
		first = first->next;
		delete temp;
	}

	length = 0;
	last = 0;
	current = 0;

	unlock();
}




