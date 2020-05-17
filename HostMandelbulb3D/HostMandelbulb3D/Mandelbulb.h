#pragma once
typedef unsigned char byte;

class Mandelbulb
{
private:
	int n;
	int maxIter;
	float bailout;
	float sqrBailout;
	byte* points = nullptr;
	int width = 0;
	int height = 0;
	int depth = 0;

public:
	Mandelbulb(int power, int maxIter);
	void compute(size_t width, size_t height);
	void draw();
};

