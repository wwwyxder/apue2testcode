#ifndef __TELL_WAIT_SIGNAL_H__
#define __TELL_WAIT_SIGNAL_H__
#include <signal.h>
void TELL_WAIT();
void TELL_PARENT(pid_t pid);
void WAIT_PARENT();
void TELL_CHILD(pid_t pid);
void WAIT_CHILD();
#endif
