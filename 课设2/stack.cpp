#include "stack.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

PNODE createStack()
{
	PNODE phead = (PNODE)malloc(sizeof(NODE));
	if (!phead)
		return NULL;
	phead->x = 0;
	phead->next = NULL;
	return phead;
}

BOOL isEmptyStack(PNODE p)
{
	if (!p->next)
		return TRUE;
	return FALSE;
}

elemetType topStack(PNODE phead)
{
	return phead->next->x;
}

BOOL popStack(PNODE phead, elemetType *data)
{
	if (isEmptyStack(phead))
	{
		return FALSE;
	}
	PNODE tempNode = phead->next;
	*data = tempNode->x;
	phead->next = tempNode->next;
	free(tempNode);
	return TRUE;
}

void pushStack(PNODE phead, elemetType data)
{
	PNODE newNode = (PNODE)malloc(sizeof(NODE));
	newNode->next = phead->next;
	newNode->x = data;
	phead->next = newNode;
}

void destoryStack(PNODE phead)
{
	elemetType temp;
	while (!isEmptyStack(phead)) {
		popStack(phead, &temp);
	}
	free(phead);
}