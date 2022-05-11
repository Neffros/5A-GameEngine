#include "../headers/Transform.h"

Transform::Transform(double x, double y, double rot, double scaleX, double scaleY) {
    position = new double[2]{x, y};
    rotation = rot;
    scale = new double[2]{scaleX, scaleY};
}

std::string Transform::toString() const {
    std::stringstream sstream;
    sstream << "position: (" << position[0] << ", " << position[1]
            << ") ; rotation: " << rotation << " ; scale: (" << scale[0]
            << ", " << scale[1] << ")";
    return sstream.str();
}
