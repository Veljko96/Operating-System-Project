#ifndef _MAKRO_H_
#define _MAKRO_H_

#include "IVTEntry.h"
#include "system.h"
#include "Thread.h"
#include "PCB.h"
#include <dos.h>

#define PREPAREENTRY(numEntry, callOld)\
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) {\
	newEntry##numEntry.signalMyEvent();\
	if (callOld == 1)\
		newEntry##numEntry.callOldRoutine();\
}



#endif /* MAKRO_H_ */
