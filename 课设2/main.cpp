#include <windows.h>
#include <windowsx.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "resource.h"
#include "winType.h"
#include "ProcducEdit.h"
#include "calculation.h"
#include "type.h"

static TCHAR scrClassName[] = TEXT("Calculator");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
ATOM MyRegisterClass(HINSTANCE hInstance);


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR lpCmdLine,int nCmdShow) {
	MSG msg;
	
	if (!MyRegisterClass(hInstance))
	{
		MessageBox(NULL, TEXT("This program requires Windows!"), T("计算器"), MB_ICONERROR | MB_OK);
		return 0;
	}

	if (!InitInstance(hInstance, nCmdShow))
		return 0;
	
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int i;
	int wmId, wmEvent;
	static int nNumFlag = 1;
	static int nTempSum = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	static HFONT hFont;
	static HWND hBtn[20];
	static HWND hEdit;
	static HFONT hFont2;
	static TCHAR szEditText[256] = { T("") };
	static INT cEditLength = 0;
	static std::vector<CalcNode> math;
	static std::vector<CalcNode> calcResult;
	char szMath[256];

	static Bstyle styleButton[] = {
		{ T("CE"), (HMENU)IDC_EDIT_CLS },
		{ T("("), (HMENU)IDC_NUM_LEFT },
		{ T(")"), (HMENU)IDC_NUM_RIGHT },
		{ T("Back"), (HMENU)IDC_EDIT_BACK },

		{ T("7"), (HMENU)IDC_NUM_7 },
		{ T("8"), (HMENU)IDC_NUM_8 },
		{ T("9"), (HMENU)IDC_NUM_9 },
		{ T("/"), (HMENU)IDC_NUM_DIV },

		{ T("4"), (HMENU)IDC_NUM_4 },
		{ T("5"), (HMENU)IDC_NUM_5 },
		{ T("6"), (HMENU)IDC_NUM_6 },
		{ T("x"), (HMENU)IDC_NUM_MUL },

		{ T("1"), (HMENU)IDC_NUM_1 },
		{ T("2"), (HMENU)IDC_NUM_2 },
		{ T("3"), (HMENU)IDC_NUM_3 },
		{ T("-"), (HMENU)IDC_NUM_SUB },

		{ T("±"), (HMENU)IDC_NUM_FLAG },
		{ T("0"), (HMENU)IDC_NUM_0 },
		{ T("+"), (HMENU)IDC_NUM_ADD },
		{ T("="), (HMENU)IDC_NUM_EQUAL }
	};
	
	switch (message)
	{
	case WM_CREATE:
		hFont = CreateFont(-15, -7, 0, 0, 400,
			FALSE, FALSE, FALSE,
			DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY,
			FF_DONTCARE,
			TEXT("微软雅黑")
		);
		hFont2 = CreateFont(
			30, 15, 0, 0, 400,
			FALSE, FALSE, FALSE,
			DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY,
			FF_DONTCARE,
			TEXT("微软雅黑")
		);

		for (i = 0; i<20; i++)
		{
			hBtn[i] = CreateWindow(
				TEXT("button"),
				styleButton[i].szText,
				WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
				(20 + 60 * (i % 4)), (110 + (i / 4) * 60), 50, 50,
				hwnd, (HMENU)styleButton[i].iMENU, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

			SendMessage(hBtn[i], WM_SETFONT, (WPARAM)hFont, NULL);
		}
		hEdit = CreateWindow(
			TEXT("edit"),
			TEXT("0"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL |  ES_AUTOVSCROLL | ES_WANTRETURN | ES_RIGHT | ES_AUTOHSCROLL | ES_READONLY | ES_MULTILINE,
			35, 15, 200, 80,
			hwnd, (HMENU)20, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont2, NULL);
		return 0;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDC_EDIT_BACK:
		{
			if (--cEditLength <= 0)
			{
				cEditLength = 0;
				Edit_SetText(hEdit, L"0");
			}
			else
			{
				szEditText[cEditLength] = T('\0');
				Edit_SetText(hEdit, szEditText);
			}
			break;
		}
		case IDC_EDIT_CLS:
		{
			memset(szEditText, 0, sizeof(szEditText));
			cEditLength = 0;
			Edit_SetText(hEdit, T("0"));
			math.clear();
			calcResult.clear();
			break;
		}
		case IDC_NUM_0:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('0');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_1:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('1');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}

			break;
		}
		case IDC_NUM_2:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('2');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_3:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('3');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_4:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('4');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_5:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('5');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_6:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('6');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_7:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('7');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_8:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('8');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_9:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('9');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_LEFT:
		{

			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('(');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_RIGHT:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T(')');
				Edit_SetText(hEdit, szEditText);
				
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_SUB:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('-');
				Edit_SetText(hEdit, szEditText);

			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_ADD:
		{

			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('+');
				Edit_SetText(hEdit, szEditText);

			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_DIV:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('/');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_MUL:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('*');
				Edit_SetText(hEdit, szEditText);

			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case  IDC_NUM_FLAG:
		{
			if (CheckEditLength(szEditText, 256))
			{
				szEditText[cEditLength++] = T('-');
				Edit_SetText(hEdit, szEditText);
			}
			else
			{
				MessageBox(hwnd, T("无法输出！"), T("缓冲区已满"), MB_ICONERROR | MB_OK);
			}
			break;
		}
		case IDC_NUM_EQUAL:
		{
			Edit_GetText(hEdit, szEditText, 256);
			if (WideCharToMultiByte(CP_OEMCP, 0, szEditText, -1, szMath, 256, NULL, FALSE) <= 0)
			{
				MessageBox(hwnd, T("cast failed!"), T("Error"), NULL);
				return 0;
			}
			memset(szEditText, 0, sizeof(szEditText));
			cEditLength = 0;
			ProcdeMath(math, szMath);
			castPostfix(math, calcResult);

			if (calcResult.size() == 0)
			{
				int reMes = MessageBox(hwnd, T("表达式错误!\n\"确定\"继续计算\n\"取消\"退出程序"), T("Error"), MB_OKCANCEL | MB_ICONERROR);
				if (IDCANCEL == reMes)
				{
					DeleteObject(hFont);
					DeleteObject(hFont2);
					PostQuitMessage(0);
					return 0;
				}
				math.clear();
				calcResult.clear();
				memset(szEditText, 0, sizeof(szEditText));
				cEditLength = 0;
				Edit_SetText(hEdit, T("0"));
				break;
			}

			int r = calc(calcResult);
			wsprintf(szEditText, T("%d"), r);
			Edit_SetText(hEdit, szEditText);
			cEditLength = lstrlen(szEditText);
			math.clear();
			calcResult.clear();
			break;
		}
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//
		EndPaint(hwnd, &ps);
		return 0;
		break;
	case WM_DESTROY:
		DeleteObject(hFont);
		DeleteObject(hFont2);
		PostQuitMessage(0);
		return 0;
		break;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND Windo = CreateWindow(
		scrClassName,
		TEXT("计算器"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		285,
		450,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!Windo)
		return FALSE;
	//显示窗口
	ShowWindow(Windo, nCmdShow);
	//绘制窗口
	UpdateWindow(Windo);
	HICON hIcon = LoadIcon(NULL, TEXT("IDC_MARVEL"));
	Static_SetIcon(Windo, hIcon);
	SendMessage(Windo, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, TEXT("IDC_MARVEL")));

	return TRUE;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS winclass; //窗口类
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WndProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hInstance;
	winclass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = scrClassName;
	//注册窗口
	return RegisterClass(&winclass);
}
