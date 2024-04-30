#include "Vec2.h"

namespace Renderer {

    Vec2::Vec2()
        : x(0.0f), y(0.0f)
    {
    }

    Vec2::Vec2(float x, float y)
        : x(x), y(y)
    {
    }

    std::string Vec2::ToString()
    {
        std::stringstream ss;
        ss << "[" << x << ", " << y << "]";
        return ss.str();
    }

    float Vec2::Dot(Vec2 const& other) const
    {
       return x * other.x +
              y * other.y;
    }


    Vec2 Vec2::operator+(Vec2 const& other) const
    {
        return Vec2(
            x + other.x,
            y + other.y
        );
    }

    Vec2& Vec2::operator+=(Vec2 const& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 Vec2::operator-(Vec2 const& other) const
    {
        return Vec2(
            x - other.x,
            y - other.y
        );
    }

    Vec2& Vec2::operator-=(Vec2 const& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
}

