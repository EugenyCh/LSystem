#pragma once

#include "Vector3D.h"
#include "Matrix3D.h"
#include "BoundingBox.h"

#include <string>
#include <stack>
#include <map>

using namespace std;

class LSystem
{
    struct State
    {
        Vector3D pos;
        Vector3D dir;
        Vector3D angles;
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
    Vector3D step(State &state)
    {
        auto res = Matrix3D::rotateZ(state.angles.z) * Matrix3D::rotateY(state.angles.y) *
            Matrix3D::rotateX(state.angles.x) * state.dir;
        state.angles = Vector3D(0, 0, 0);
        printf("(%.1f, %.1f, %.1f) -> (%.1f, %.1f, %.1f)\n",
            state.dir.x, state.dir.y, state.dir.z,
            res.x, res.y, res.z);
        return res;
    }

    virtual void drawLine(const Vector3D &p1, const Vector3D &p2, float k) const;
    virtual void updateState(State &state, const Vector3D dir);
};