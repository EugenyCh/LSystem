#pragma once

#include "Vector3D.h"
#include "Matrix3D.h"
#include "BoundingBox.h"

#include <string>
#include <stack>
#include <map>

using namespace std;

static int nstep = 0;

class LSystem
{
    struct State
    {
		Vector3D pos;
        Vector3D angles;
        Vector3D dir;
        float angle;
        float invert;
    };

    map<char, string> rules;
    string initialString;
    float angle;
    float distScale;
    float angleScale;
	string currentString;
    BoundingBox bounds;

public:
    LSystem();

    void setInitialString(const char *str)
    {
        initialString = str;
    }

    void addRule(char symbol, const char *rule)
    {
        rules[symbol] = rule;
    }

    void setAngle(float newAngle)
    {
        angle = newAngle;
    }

    const string &getCurrentString() const
    {
        return currentString;
    }

    void setDistScale(float newScale)
    {
        distScale = newScale;
    }

    void setAngleScale(float scale)
    {
        angleScale = scale;
    }

    void interpretString(const string &str);
    void buildSystem(int numIterations);

    void draw()
    {
        interpretString(currentString);
    }

    const BoundingBox &getBounds() const
    {
        return bounds;
    }

protected:
    string oneStep(const string &in) const;
    Vector3D step(State &state) const
    {
        ++nstep;
        return Matrix3D::rotate(state.angles.x, state.angles.y, state.angles.z) * state.dir;
    }

    virtual void drawLine(const Vector3D &p1, const Vector3D &p2, float k) const;
    virtual void updateState(State &state, const Vector3D dir) const;
};