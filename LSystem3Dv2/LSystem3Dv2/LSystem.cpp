#include <stdio.h>
#include <GL/glut.h>
#include "LSystem.h"

LSystem::LSystem()
{
	initialString = "F";
	angle = 30 * M_PI / 180;
	distScale = 1;
	angleScale = 1;
}

void LSystem::interpretString(const string& str)
{
	State state;
	stack<State> st;
	Vector3D d;

	state.pos = Vector3D(0, 0, 0);
	state.dir = Vector3D(1, 0, 0);
	state.angles = Vector3D(0, 0, 0);
	state.angle = angle;
	state.invert = 1;

	int maxLevel = 0;
	int level = 0;
	for (int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '[':
			++level;
			break;

		case ']':
			--level;
			break;
		}
		if (level > maxLevel)
			maxLevel = level;
	}

	for (int i = 0; i < str.length(); i++)
	{
		float k;
		if (maxLevel > 0)
			k = 1.0f * st.size() / maxLevel;
		else
			k = 1.0f;
		switch (str[i])
		{
		case '[': // push state
			st.push(state);
			break;

		case ']': // pop state
			state = st.top();
			st.pop();
			break;

		case 'F':
			d = step(state);
			bounds.addVertex(state.pos);
			bounds.addVertex(state.pos + d);
			drawLine(state.pos, state.pos + d, k);
			updateState(state, d, k);
			break;

		case 'f':
			bounds.addVertex(state.pos);
			bounds.addVertex(state.pos + d);
			updateState(state, step(state), k);
			break;

		case '!': // inverse + and - meaing (just as for & and ^ and < and >)
			state.invert *= -1;
			break;

		case '+':
			state.angles.z += state.invert * state.angle;
			break;

		case '-':
			state.angles.z -= state.invert * state.angle;
			break;

		case '|':
			state.angles.z += M_PI;
			break;

		case '<':
		case '\\':
			state.angles.y += state.invert * state.angle;
			break;

		case '>':
		case '/':
			state.angles.y -= state.invert * state.angle;
			break;

		case '&':
			state.angles.x += state.invert * state.angle;
			break;

		case '^':
			state.angles.x -= state.invert * state.angle;
			break;
		}
	}
}

void LSystem::buildSystem(int numIterations)
{
	bounds.reset();

	currentString = initialString;

	for (int i = 0; i < numIterations; i++)
	{
		currentString = oneStep(currentString);

		printf("%s\n", currentString.c_str());
	}
}

string LSystem::oneStep(const string& in) const
{
	string out;
	map<char, string>::const_iterator it;

	for (int i = 0; i < in.length(); i++)
	{
		it = rules.find(in[i]);

		if (it != rules.end())
			out += it->second;
		else
			out += in[i];
	}

	return out;
}

void LSystem::drawLine(const Vector3D& p1, const Vector3D& p2, float k) const
{
	static bool first = true;
	// k in [0; 1]
	glLineWidth(4.f - 3.f * k);
	glBegin(GL_LINES);
	if (first)
		glColor3f(1.f, 0.f, 0.f);
	else
		glColor3f(1.f - k, k, 0.f);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glEnd();
	first = false;
}

void LSystem::updateState(State& state, const Vector3D& dir, float k)
{
	state.pos += dir;
	state.dir = dir * distScale;
	state.angle *= angleScale;
}
