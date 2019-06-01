/*
 * KernelEv.h
 *
 *  Created on: May 23, 2017
 *      Author: OS1
 */

#ifndef _KERNELEV_H_
#define _KERNELEV_H_

#include "event.h"
#include "PCB.h"

class KernelEvent {

	IVTNo ivtNo;
	PCB *creator;
	int value;
	int isBlocked;

public:

	KernelEvent(IVTNo);
	void signal();
	void wait();
	~KernelEvent();
};

#endif /* KERNELEV_H_ */
