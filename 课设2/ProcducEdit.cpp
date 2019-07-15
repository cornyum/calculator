#include "ProcducEdit.h"
#include <cctype>

BOOL CheckEditLength(PTCHAR szEdit, UINT nBufferNum)
{
	UINT nowLen = lstrlen(szEdit);
	if (nowLen <= nBufferNum && nowLen >= 0)
	{
		return TRUE;
	}
	return FALSE;
}

std::vector<CalcNode>& ProcdeMath(std::vector<CalcNode>& v, const char * szEditA)
{
	int nEditlen = lstrlenA(szEditA);
	int temp = 0, flag = 1, flag2 = 0;
	for (int i = 0; i < nEditlen; ++i)
	{
		char ch = szEditA[i];
		if (ch == '+' || ch == '(' || ch == ')' || ch == '*' || ch == '/'){
			if (flag2)
			{
				v.push_back(CalcNode(temp * flag, 1));
				temp = 0;
				flag = 1;
				flag2 = 0;
			}
			v.push_back(CalcNode(ch, 0));
		} else {
			if (ch == '-' && i != 0 && (isdigit(szEditA[i - 1]) || szEditA[i - 1] == ')'))
			{
				if (flag2)
				{
					v.push_back(CalcNode(temp * flag, 1));
					temp = 0;
					flag = 1;
					flag2 = 0;
				}
				v.push_back(CalcNode(ch, 0));
			}
			else if (ch == '-')
			{
				flag = -1;
				flag2 = 1;
			}
			else {
				temp = temp * 10 + (ch - '0');
				flag2 = 1;
			}
		}
	}
	if (flag2)
		v.push_back(CalcNode(temp * flag, 1));
	return v;
}
