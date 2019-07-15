#ifndef _STACK_H_
#define _STACK_H_
#include "type.h"
PNODE createStack();
BOOL isEmptyStack(PNODE);
elemetType topStack(PNODE);
BOOL popStack(PNODE, elemetType*);
void pushStack(PNODE, elemetType);
void destoryStack(PNODE);
#endif // !_STACK_H_
