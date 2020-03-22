#define _USE_MATH_DEFINES
#include "LSystem.h"
#include <cmath>
#include <iostream>

int main()
{
	auto lsystem = LSystem("X");
	lsystem.set_rule('X', "X+Y+");
	lsystem.set_rule('Y', "-X-Y");
	cout << lsystem.iterate(3, true) << endl;

	return 0;
}