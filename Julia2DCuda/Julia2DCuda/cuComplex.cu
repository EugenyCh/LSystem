#include "cuComplex.h"

__device__ cuComplex::cuComplex(float a, float b) : r(a), i(b) {}

__device__ float cuComplex::sqrMagnitude(void)
{
	return r * r + i * i;
}

__device__ cuComplex cuComplex::operator*(const cuComplex& a)
{
	return cuComplex{ r * a.r - i * a.i, i * a.r + r * a.i };
}

__device__ cuComplex cuComplex::operator+(const cuComplex& a)
{
	return cuComplex{ r + a.r, i + a.i };
}