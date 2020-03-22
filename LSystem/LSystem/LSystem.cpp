#include "LSystem.h"

LSystem::LSystem() {}

LSystem::LSystem(string axiom)
{
	this->axiom = axiom;
}

void LSystem::set_axiom(string axiom)
{
	this->axiom = axiom;
}

bool LSystem::set_rule(char rule, string defination)
{
	return this->rules.insert(pair<char, string>(rule, defination)).second;
}

string LSystem::iterate(int n, bool debug)
{
	string s0;
	string s1 = this->axiom;
	for (int k = n; k > 0; --k)
	{
		s0 = s1;
		s1 = "";
		for (int i = 0; i < s0.length(); ++i)
		{
			map<char, string>::iterator it = this->rules.find(s0[i]);
			if (it == this->rules.end())
				s1 += s0[i];
			else
			{
				if (k == 1 && debug)
					s1 += "(" +  it->second + ")";
				else
					s1 += it->second;
			}
		}
	}
	return s1;
}