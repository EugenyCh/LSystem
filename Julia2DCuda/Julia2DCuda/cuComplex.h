#pragma once

class cuComplex
{
public:
	float r, i;

	cuComplex(float a, float b);
	float sqrMagnitude(void);
	cuComplex operator*(const cuComplex& a);
	cuComplex operator+(const cuComplex& a);
};