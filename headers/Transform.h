#pragma once

#include <string>
#include <sstream>

class Transform{
public:
    Transform() : Transform(0, 0, 0, 1, 1) {}
    Transform(double x, double y, double rot, double scaleX, double scaleY);

    double* position;
    double rotation;
    double* scale;

    std::string toString() const;
};