#include "Mandelbulb.h"
#include "Hypercomplex.h"
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include <cstdio>
#include <ctime>
#define MAX(a, b) ((a) < (b) ? (b) : (a))

Mandelbulb::Mandelbulb(int power, int maxIter)
{
	this->n = power;
	this->maxIter = maxIter;
	this->bailout = powf(2.0f, 1.0f / (power - 1));
	this->sqrBailout = powf(4.0f, 1.0f / (power - 1));
}

void Mandelbulb::compute(size_t width, size_t height)
{
	if (points)
		delete[] points;
	this->width = width;
	this->height = height;
	this->depth = MAX(width, height);

	const size_t sz = width * height * depth;
	points = new byte[sz * 4];

	printf("Rendering %dx%d%d\n", width, height, depth);
	clock_t tStart = clock();
	int halfWidth = width >> 1;
	int halfHeight = height >> 1;
	int halfSide = depth >> 1;
	// Processing
	for (int z = 0; z < depth; ++z)
	{
		printf("\r%5.1f %%", 100.0f * z / (depth - 1));
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				int offset = (z * width * height + y * width + x) * 4;
				// Compute point at this position
				float fx = bailout * (float)(x - halfWidth) / halfSide;
				float fy = bailout * (float)(y - halfHeight) / halfSide;
				float fz = bailout * (float)(z - halfSide) / halfSide;
				Hypercomplex hc(fx, fy, fz);
				Hypercomplex hz(fx, fy, fz);

				// Iterating
				bool belongs;
				if (hc.sqrRadius() > sqrBailout)
					belongs = false;
				else
				{
					for (int i = 0; i < maxIter; ++i)
						hz = (hz ^ n) + hc;
					belongs = hz.sqrRadius() <= sqrBailout;
				}

				if (belongs)
				{
					//float k = hz.sqrRadius() / sqrBailout;
					float k = 1.0f;
					// Setting point color
					points[offset] = (byte)(k * 255);
					points[offset + 1] = (byte)(k * 255);
					points[offset + 2] = (byte)(k * 255);
					points[offset + 3] = 255;
				}
				else
				{
					points[offset] = 0;
					points[offset + 1] = 0;
					points[offset + 2] = 0;
					points[offset + 3] = 0;
				}
			}
		}
	}
	// End
	clock_t tFinish = clock();
	double tDelta = (double)(tFinish - tStart) / CLOCKS_PER_SEC;
	printf("\nIt tooks %.3f seconds\n", tDelta);
}

void Mandelbulb::draw()
{
	glBegin(GL_POINTS);
	for (int z = 0; z < depth; ++z)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				int i = (z * width * height + y * width + x) * 4;
				if (points[i + 3] > 0)
				{
					glColor4ub(
						points[i],
						points[i + 1],
						points[i + 2],
						points[i + 3]
					);
					glVertex3f(x, y, z);
				}
			}
		}
	}
	glEnd();
}
