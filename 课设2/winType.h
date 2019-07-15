#pragma once
#ifndef _WINTYPE_MY_H_
#define _WINTYPE_MY_H_
#include <windows.h>
#define T TEXT
#define IDC_NUM_0 200
#define IDC_NUM_1 201
#define IDC_NUM_2 202
#define IDC_NUM_3 203
#define IDC_NUM_4 204
#define IDC_NUM_5 205
#define IDC_NUM_6 206
#define IDC_NUM_7 207
#define IDC_NUM_8 208
#define IDC_NUM_9 209
#define IDC_NUM_LEFT 210
#define IDC_NUM_RIGHT 211
#define IDC_NUM_MUL 212
#define IDC_NUM_DIV 213
#define IDC_NUM_ADD 214
#define IDC_NUM_SUB 215
#define IDC_NUM_EQUAL 199
#define IDC_EDIT_RESULT 216
#define IDC_EDIT_BACK 217
#define IDC_EDIT_CLS 218
#define IDC_NUM_FLAG 219
typedef struct buttonStyle {
	TCHAR szText[50];
	HMENU iMENU;
}Bstyle;
#endif