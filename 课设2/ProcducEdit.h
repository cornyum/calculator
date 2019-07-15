#pragma once
#ifndef _PROC_EDIT_H_
#define _PROC_EDIT_H_
#include <windows.h>
#include <windowsx.h>
#include "type.h"
#include <vector>
BOOL CheckEditLength(PTCHAR szEdit, UINT nBufferNum);
std::vector<CalcNode>& ProcdeMath(std::vector<CalcNode>& v, const char * szEditA);
#endif