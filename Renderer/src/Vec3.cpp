#include "Vec3.h"

namespace Renderer {

    Vec3::Vec3()
        : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    Vec3::Vec3(float x, float y, float z)
        : x(x), y(y), z(z)
    {
    }

    std::string Vec3::ToString()
    {
        std::stringstream ss;
        ss << "[" << x << ", " << y << ", " << z << "]";
        return ss.str();
    }

}

