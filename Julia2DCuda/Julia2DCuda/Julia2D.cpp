#include "Julia2D.h"
#include "cuComplex.h"

Julia2D::Julia2D(float _cx, float _cy) : cx(_cx), cy(_cy) {}

void Julia2D::compute(size_t width, size_t height, int iters)
{
	if (points)
		delete[] points;
	points = new point[width * height];

	int halfSide = MIN(width, height) / 2;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float jx = 1.5f * (float)(halfSide - x) / halfSide;
			float jy = 1.5f * (float)(halfSide - y) / halfSide;
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

			if (k > 0)
			{
				points[width * y + x].exist = true;
				points[width * y + x].color[0] = (byte)(k * 255);
				points[width * y + x].color[1] = (byte)(k * 255);
				points[width * y + x].color[2] = (byte)(k * 255);
			}
		}
	}
}