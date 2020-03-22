#define _USE_MATH_DEFINES
#include "LSystem.h"
#include <cmath>
#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#define WIDTH 640
#define HEIGHT 480

vector<sf::Vertex> renderLSystem(string lsystem, double angle, double theta, string undrawables = "")
{
	vector<sf::Vertex> lines;
	double h = 1.0;
	double x, y;
	x = y = 0;
	double xmin, xmax, ymin, ymax;
	xmin = xmax = 0;
	ymin = ymax = 0;
	stack<double> stack_x, stack_y, stack_a;
	int stack_depth = 0;

	for (int i = 0; i < lsystem.length(); ++i)
	{
		char c = lsystem[i];
		switch (c)
		{
		case '+':
			angle += theta;
			break;
		case '-':
			angle -= theta;
			break;
		case '[':
			stack_a.push(angle);
			stack_x.push(x);
			stack_y.push(y);
			++stack_depth;
			break;
		case ']':
			if (stack_depth < 1)
				break;
			angle = stack_a.top();
			x = stack_x.top();
			y = stack_y.top();
			stack_a.pop();
			stack_x.pop();
			stack_y.pop();
			--stack_depth;
			break;
		default:
			if (undrawables.empty() || undrawables.find(c) == string::npos)
			{
				lines.push_back(sf::Vertex(sf::Vector2f(x, y), sf::Color(64, 64, 64)));
				x += h * cos(angle);
				y += h * sin(angle);
				lines.push_back(sf::Vertex(sf::Vector2f(x, y), sf::Color(255, 255, 255)));
				if (x < xmin)
					xmin = x;
				if (x > xmax)
					xmax = x;
				if (y < ymin)
					ymin = y;
				if (y > ymax)
					ymax = y;
			}
			else
			{
				x += h * cos(angle);
				y += h * sin(angle);
			}
		}
	}

	double scale = min(HEIGHT, WIDTH) / max(ymax - ymin, xmax - xmin);

	for (int i = 0; i < lines.size(); ++i)
	{
		lines[i].position.x -= (xmax + xmin) / 2;
		lines[i].position.x *= scale;
		lines[i].position.x += WIDTH / 2;
		lines[i].position.y -= (ymax + ymin) / 2;
		lines[i].position.y *= scale;
		lines[i].position.y += HEIGHT / 2;
	}

	return lines;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "LSystem Window");
	window.setFramerateLimit(2);

	LSystem lsystem("f+f+f+f");
	lsystem.set_rule('f', "ff+f+f+f+ff");

	vector<sf::Vertex> lines = renderLSystem(lsystem.iterate(5), 0, 90 * M_PI / 180);
	sf::Vertex* vertices = lines.data();
	size_t vlen = lines.size();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(vertices, vlen, sf::Lines);
		window.display();
	}

	return 0;
}