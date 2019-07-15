#ifndef _CALCTION_H_
#define _CALCTION_H_
#include <cstdlib>
#include <vector>
#include "type.h"
#define MAXLEN 350

std::vector<CalcNode>& castPostfix(const std::vector<CalcNode>& math, std::vector<CalcNode>& postfix);
int calc(std::vector<CalcNode>& postfix);
#endif
