#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Julia2D.cuh"
#include "cuComplex.cuh"
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <time.h>

__global__ void kernel(byte* buffer, const int width, const int height, const float cx, const float cy, const int iters)
{
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	if (x >= width)
		return;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	if (y >= height)
		return;
	int offset = x + y * width;

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
}

Julia2D::Julia2D(float cx, float cy)
{
	this->cx = cx;
	this->cy = cy;
}

bool Julia2D::compute(size_t width, size_t height, int iters)
{
	if (points)
		delete[] points;
	points = new point[width * height];
	this->width = width;
	this->height = height;
	int side = MAX(width, height);

	const size_t sz = width * height;
	byte* buffer = new byte[sz * 3];
	byte* dev_buffer;

	if (cudaMalloc((void**)&dev_buffer, sz * 3) != cudaSuccess)
	{
		printf("Error on creating buffer of pixels in GPU\n");
		return false;
	}

	dim3 blocks((side + 31) / 32, (side + 31) / 32);
	dim3 threads(32, 32);
	printf("Rendering\n");
	clock_t tStart = clock();
	kernel<<<blocks, threads>>>(dev_buffer, width, height, cx, cy, 50);
	cudaThreadSynchronize();
	clock_t tFinish = clock();
	double tDelta = (double)(tFinish - tStart) / CLOCKS_PER_SEC;
	printf("It tooks %.3f seconds\n", tDelta);

	cudaFree(dev_buffer);
	return true;
}

void Julia2D::draw()
{
	glBegin(GL_POINTS);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int i = width * y + x;
			glColor3ub(
				points[i].color[0],
				points[i].color[1],
				points[i].color[2]
			);
			glVertex2i(x, y);
		}
	}
	glEnd();
}