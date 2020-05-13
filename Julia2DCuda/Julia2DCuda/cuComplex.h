#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

class cuComplex
{
public:
	float r, i;

	__device__ cuComplex(float a, float b);
	__device__ float sqrMagnitude(void);
	__device__ cuComplex operator*(const cuComplex& a);
	__device__ cuComplex operator+(const cuComplex& a);
};