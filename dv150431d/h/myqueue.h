#ifndef _MYQUEUE_H_
#define _MYQUEUE_H_

#include "pcb.h"

class PCB;

struct Elem {

		PCB *pcb;
		Elem *next;
		Elem(PCB* p) {

			pcb = p;
		}
	};

class Queue {

public:

	Queue();
	void put(PCB* p);
	PCB* get();
	PCB* getCurrent();
	void currentToFirst();
	void next();
	int size() const;
	int remove(PCB* p);
	void sub();
	int isEmpty();
	~Queue();

private:

	friend class KernelSem;
	Elem *first, *last, *current;
	int length;
};

#endif

