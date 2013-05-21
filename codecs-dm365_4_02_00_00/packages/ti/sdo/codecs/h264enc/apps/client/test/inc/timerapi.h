#ifndef __timerAPI_h_
#define __timerAPI_h_
#include "tistdtypes.h"
#define Uint64 unsigned long long

typedef struct{
     Uint64 Count;     
     Uint64 TotalCycles;     
     Uint64 CurrentCycleCount;
     Uint64 AverageCycleCount;
     Uint64 PeakCycleCount;
}TimerState;

#endif
