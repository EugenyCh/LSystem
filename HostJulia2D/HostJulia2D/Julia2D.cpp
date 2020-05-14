#include "Julia2D.h"
#include "Complex.h"
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <time.h>

/*__global__ void kernel(byte* buffer, const int width, const int height, const float cx, const float cy, const int iters)
{
	int offset = threadIdx.x + blockDim.x * blockIdx.x;
	int x = offset % width;
	int y = offset / width;
	if (y >= height)
		return;

	// Compute point at this position
	int halfWidth = width >> 1;
	int halfHeight = height >> 1;
	int halfSide = MAX(halfWidth, halfHeight);
	float jx = 2.0f * (float)(x - halfWidth) / halfSide;
	float jy = 2.0f * (float)(y - halfHeight) / halfSide;
	cuComplex c(cx, cy);
	cuComplex z(jx, jy);

	// Iterating
	int i;
	for (i = 0; i < iters; ++i)
	{
		z = z * z + c;
		if (z.sqrMagnitude() > 4.0f)
			break;
	}
	float k = (float)i / iters;

	// Setting point color
	buffer[offset * 3] = (byte)(k * 255);
	buffer[offset * 3 + 1] = (byte)(k * 255);
	buffer[offset * 3 + 2] = (byte)(k * 255);
}*/

Julia2D::Julia2D(float cx, float cy)
{
	this->cx = cx;
	this->cy = cy;
}

bool Julia2D::compute(size_t width, size_t height, int iters)
{
	width *= 2;
	height *= 2;
	if (points)
		delete[] points;
	this->width = width;
	this->height = height;
	int side = MAX(width, height);

	const size_t sz = width * height;
	points = new byte[sz * 3];

	printf("Rendering %dx%d\n", width, height);
	clock_t tStart = clock();
	int halfWidth = width >> 1;
	int halfHeight = height >> 1;
	int halfSide = MAX(halfWidth, halfHeight);
	// Processing
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int offset = (y * width + x) * 3;
			// Compute point at this position
			float jx = 2.0f * (float)(x - halfWidth) / halfSide;
			float jy = 2.0f * (float)(y - halfHeight) / halfSide;
			Complex c(cx, cy);
			Complex z(jx, jy);

			// Iterating
			int i;
			for (i = 0; i < iters; ++i)
			{
				z = z * z + c;
				if (z.sqrMagnitude() > 4.0f)
					break;
			}
			float k = (float)i / iters;

			// Setting point color
			points[offset] = (byte)(k * 255);
			points[offset + 1] = (byte)(k * 255);
			points[offset + 2] = (byte)(k * 255);
		}
	}
	// End
	clock_t tFinish = clock();
	double tDelta = (double)(tFinish - tStart) / CLOCKS_PER_SEC;
	printf("It tooks %.3f seconds\n", tDelta);

	return true;
}

void Julia2D::draw()
{
	glBegin(GL_POINTS);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int i = (width * y + x) * 3;
			glColor3ub(
				points[i],
				points[i + 1],
				points[i + 2]
			);
			glVertex2f(x * 0.5, y * 0.5);
		}
	}
	glEnd();
}