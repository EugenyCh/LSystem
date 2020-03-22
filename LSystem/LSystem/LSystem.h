#pragma once
#include <string>
#include <map>

using namespace std;

class LSystem
{
	string axiom;
	map<char, string> rules;

public:
	LSystem();
	LSystem(string);
	void set_axiom(string);
	bool set_rule(char, string);
	string iterate(int, bool=false);
};

