#include "calculation.h"
#include "stack.h"
#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>

std::vector<CalcNode>& castPostfix(const std::vector<CalcNode>& math, std::vector<CalcNode>& postfix)
{
	int nLenMath = math.size();
	int i = 0;
	PNODE operatorStack = createStack();
	CalcNode temp, o;

	if (!operatorStack) 
	{
		printf("ÄÚ´æ²»×ã\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < nLenMath; ++i)
	{ 
		temp = math[i];
		if (temp.type == TRUE)
		{
			postfix.push_back(temp);
		}
		else if (temp.data == ')')
		{
			while(!isEmptyStack(operatorStack) && topStack(operatorStack).data != '(')
			{
				popStack(operatorStack, &o);
				postfix.push_back(o);
			}
			popStack(operatorStack, &o);
		}
		else if (temp.data == '*' || temp.data == '/')
		{
			if (!isEmptyStack(operatorStack))
			{
				if (topStack(operatorStack).data == '*' || topStack(operatorStack).data == '/')
				{
					popStack(operatorStack, &o);
					postfix.push_back(o);
				}
			}
			pushStack(operatorStack, temp);
		}
		else if (temp.data == '+' || temp.data == '-')
		{
			if (!isEmptyStack(operatorStack))
			{
				if (topStack(operatorStack).data == '*' || topStack(operatorStack).data == '/' || topStack(operatorStack).data == '+' || topStack(operatorStack).data == '-')
				{
					popStack(operatorStack, &o);
					postfix.push_back(o);
				}
			}
			pushStack(operatorStack, temp);
		}
		else
		{
			pushStack(operatorStack, temp);
		}
	}
	while (!isEmptyStack(operatorStack))
	{
		popStack(operatorStack, &o);
		if (o.data == ')' || o.data == '(')
		{
			postfix = std::vector<CalcNode>();
			return std::vector<CalcNode>();
		}
		postfix.push_back(o);
	}
	destoryStack(operatorStack);
	return postfix;
}

int calc(std::vector<CalcNode>& postfix)
{
	int r = 0;
	CalcNode opt1, opt2;
	PNODE calcStack = createStack();
	int nLenPostfix = postfix.size(), i;

	if (!calcStack)
	{
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < nLenPostfix; ++i)
	{
		CalcNode temp = postfix[i];
		if (temp.type == 1)
		{
			pushStack(calcStack, temp);
		}
		else if (temp.data == '+')
		{
			popStack(calcStack, &opt1);
			popStack(calcStack, &opt2);
			r = opt1.data + opt2.data;
			pushStack(calcStack, CalcNode(r, 1));
		}
		else if (temp.data == '-')
		{
			popStack(calcStack, &opt1);
			popStack(calcStack, &opt2);
			r = opt2.data - opt1.data;
			pushStack(calcStack, CalcNode(r, 1));
		}
		else if (temp.data == '/')
		{
			popStack(calcStack, &opt1);
			popStack(calcStack, &opt2);
			r = opt2.data / opt1.data;
			pushStack(calcStack, CalcNode(r, 1));
		}
		else if (temp.data == '*')
		{
			popStack(calcStack, &opt1);
			popStack(calcStack, &opt2);
			r = opt2.data * opt1.data;
			pushStack(calcStack, CalcNode(r, 1));
		}
	}
	r = topStack(calcStack).data;
	destoryStack(calcStack);
	return r;
}
