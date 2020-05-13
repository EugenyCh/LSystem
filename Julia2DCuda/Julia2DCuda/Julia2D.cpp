#include "Julia2D.h"
#include "cuComplex.h"
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>

Julia2D::Julia2D(float cx, float cy)
{
	this->cx = cx;
	this->cy = cy;
}

void Julia2D::compute(size_t width, size_t height, int iters)
{
	if (points)
		delete[] points;
	points = new point[width * height];
	this->width = width;
	this->height = height;

	int halfWidth = width >> 1;
	int halfHeight = height >> 1;
	int halfSide = MAX(halfWidth, halfHeight);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
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
			float k = 1.0f * i / iters;

			points[width * y + x].color[0] = (byte)(k * 255);
			points[width * y + x].color[1] = (byte)(k * 255);
			points[width * y + x].color[2] = (byte)(k * 255);
		}
	}
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