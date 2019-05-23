
#ifndef _SCHEDULLER_
#define _SCHEDULLER_

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STATUS_REQUEST
#define _TASK_STD_FUNCTION
#define _TASK_PRIORITY // Support for layered scheduling priority

#include <TaskSchedulerDeclarations.h>

// Let the runner object be a global, single instance shared between object
// files.
extern Scheduler scheduller;

extern uint8_t configFlag ;

#endif