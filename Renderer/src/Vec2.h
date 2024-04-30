#pragma once

#include <sstream>
#include <string>

namespace Renderer
{
    class Vec2
    {
    public:
        float x, y;

        Vec2();
        Vec2(float x, float y);

        ~Vec2() = default;

        std::string ToString();

        float Dot(Vec2 const& other) const;

        Vec2 operator+(Vec2 const& other) const;
        Vec2& operator+=(Vec2 const& other);
        Vec2 operator-(Vec2 const& other) const;
        Vec2& operator-=(Vec2 const& other);
        Vec2 operator*(float scalar) const;
        Vec2& operator*=(float scalar);
        Vec2 operator/(float scalar) const;
        Vec2& operator/=(float scalar);
    };
}

