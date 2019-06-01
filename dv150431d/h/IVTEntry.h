/*
 * IVTEntry.h
 *
 *  Created on: May 23, 2017
 *      Author: OS1
 */

#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

class KernelEvent;
typedef void interrupt (*InterruptFunc)(...);
typedef unsigned char IVTNo;

class IVTEntry {


	IVTNo myIvtN;
	KernelEvent* myEvent;
	InterruptFunc oldFunc, newFunc; //newFunc

public:

	static IVTEntry* IVT[256];

	IVTEntry(IVTNo, InterruptFunc);

	void setMyEvent(KernelEvent*);

	void deleteMyEvent();

	void signalMyEvent();

	void callOldRoutine();

	~IVTEntry();

};



#endif /* IVTENTRY_H_ */
