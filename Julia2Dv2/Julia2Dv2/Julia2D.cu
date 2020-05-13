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
	this->width = width;
	this->height = height;
	int side = MAX(width, height);

	const size_t sz = width * height;
	points = new byte[sz * 3];
	byte* dev_buffer;

	if (cudaMalloc((void**)&dev_buffer, sz * 3) != cudaSuccess)
	{
		printf("Error on creating buffer of pixels in GPU\n");
		return false;
	}

	printf("Rendering %dx%d\n", width, height);
	int threads = 1024;
	int blocks = (sz + threads - 1) / threads;
	clock_t tStart = clock();
	kernel<<<blocks, threads>>>(dev_buffer, width, height, cx, cy, 200);
	cudaThreadSynchronize();
	clock_t tFinish = clock();
	double tDelta = (double)(tFinish - tStart) / CLOCKS_PER_SEC;
	printf("It tooks %.3f seconds\n", tDelta);

	printf("Moving\n");
	if (cudaMemcpy((void*)points, dev_buffer, sz * 3, cudaMemcpyDeviceToHost) != cudaSuccess)
	{
		printf("Error on getting buffer of pixels from GPU\n");
		return false;
	}

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
			int i = (width * y + x) * 3;
			glColor3ub(
				points[i],
				points[i + 1],
				points[i + 2]
			);
			glVertex2i(x, y);
		}
	}
	glEnd();
}