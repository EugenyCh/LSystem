#pragma once
#include "Quaternion.cuh"
typedef unsigned char byte;

class QFractal
{
private:
	float qR, qA, qB, qC;
	int maxIter;
	float bailout;
	float sqrBailout;
	byte* points = nullptr;
	size_t side = 0;
	byte colorSpectrum[256][3];

public:
	QFractal(float r, float a, float b, float c, int maxIter);
	bool compute(size_t width, size_t height);
	void draw(size_t width, size_t height);
	void initColorSpectrum();
};

