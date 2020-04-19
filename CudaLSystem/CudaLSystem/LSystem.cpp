#include "LSystem.h"

LSystem::LSystem() {}

LSystem::LSystem(double theta, string axiom)
{
	this->theta = theta;
	this->axiom = axiom;
}

void LSystem::set_theta(double theta)
{
	this->theta = theta;
}

void LSystem::set_axiom(string axiom)
{
	this->axiom = axiom;
}

bool LSystem::set_rule(char rule, string defination)
{
	return this->rules.insert(pair<char, string>(rule, defination)).second;
}