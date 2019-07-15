#pragma once
#ifndef _TYPE_H_
#define _TYPE_H_
typedef int BOOL;
typedef struct stacknode {
	int data;
	BOOL type;	//FALSE operator  True number
	stacknode(const int &d = 0, const BOOL &f = 0) : data(d), type(f) {}
}CalcNode;

typedef CalcNode elemetType;
typedef struct node {
	elemetType x;
	struct node* next;
}NODE, *PNODE;
#define FALSE 0
#define TRUE 1
#endif