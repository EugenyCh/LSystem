#pragma once
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef unsigned char byte;

typedef struct {
	bool exist = false;
	byte color[3];
} point;

class Julia2D
{
private:
	point* points = nullptr;

public:
	float cx;
	float cy;

	Julia2D(float cx, float cy);
	void compute(size_t width, size_t height, int iters);
};

