#pragma once
#define MAX(a, b) ((a) < (b) ? (b) : (a))

typedef unsigned char byte;

class Julia2D
{
private:
	byte* points = nullptr;
	int width = 0;
	int height = 0;

public:
	float cx;
	float cy;

	Julia2D(float cx, float cy);
	bool compute(size_t width, size_t height, int iters);
	void draw();
};

