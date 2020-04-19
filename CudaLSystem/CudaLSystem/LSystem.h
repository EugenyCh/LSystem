#pragma once
#include <string>
#include <map>

using namespace std;

class LSystem
{
	double theta;
	string axiom;
	map<char, string> rules;

public:
	LSystem();
	LSystem(double, string);
	void set_theta(double);
	void set_axiom(string);
	bool set_rule(char, string);
};

