#pragma once
#define MAX(a, b) ((a) < (b) ? (b) : (a))

typedef unsigned char byte;

typedef struct {
	byte color[3];
} point;

class Julia2D
{
private:
	point* points = nullptr;
	int width = 0;
	int height = 0;

public:
	float cx;
	float cy;

	Julia2D(float cx, float cy);
	bool compute(size_t width, size_t height, int iters);
	void draw();
};

