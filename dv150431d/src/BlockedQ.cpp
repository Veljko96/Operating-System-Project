#include "BlockedQ.h"
#include "system.h"

BlockedQ::BlockedQ(){

	lock();
	head = 0;
	last = 0;
	unlock();
}

void BlockedQ::put(KernelSem* ksem) {

	lock();

	Str* new1 = new Str(ksem);
	if(head == 0) head=new1;
	else last->next = new1;
	last = new1;

	unlock();
}

void BlockedQ::remove(KernelSem* ksem)
{

	lock();

	Str* prev = head;
	if(head==0) {

		unlock();
		return;
	}

	Str* curr = head;
	while(curr!=0 && curr->sem!=ksem) {

		prev=curr;
		curr=curr->next;
	}

	if(curr==0) {

		unlock();
		return;
	}

	if(head->sem==ksem) {

		head=head->next;
		if(head==0)
			last=0;
	}

	if(last != 0 && last->sem==ksem)
		last=prev;

	prev->next=curr->next;
	curr->next=0;

	delete curr;

	unlock();
	return;
}

int BlockedQ::isEmpty() {

	lock();
	if (head == 0) {

		unlock();
		return 1;
	}

	unlock();
	return 0;
}

BlockedQ::~BlockedQ() {

	lock();

	while(head != 0)
	{
		Str* old = head;
		head=head->next;
		old->next=0;
		delete old;
	}

	unlock();
}


