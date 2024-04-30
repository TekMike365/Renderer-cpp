#pragma once

#include <sstream>
#include <string>

namespace Renderer
{
    class Vec3
    {
    public:
        float x, y, z;

        Vec3();
        Vec3(float x, float y, float z);

        ~Vec3() = default;

        std::string ToString();

        float Dot(Vec3 const& other) const;
        Vec3 Cross(Vec3 const& other) const;

        Vec3 operator+(Vec3 const& other) const;
        Vec3& operator+=(Vec3 const& other);
        Vec3 operator-(Vec3 const& other) const;
        Vec3& operator-=(Vec3 const& other);
        Vec3 operator*(float scalar) const;
        Vec3& operator*=(float scalar);
        Vec3 operator/(float scalar) const;
        Vec3& operator/=(float scalar);
    };
}

