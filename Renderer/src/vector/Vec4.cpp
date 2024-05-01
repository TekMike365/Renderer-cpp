#include "Vec4.h"

namespace Renderer {

    Vec4::Vec4()
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {
    }

    Vec4::Vec4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    {
    }

    std::string Vec4::ToString()
    {
        std::stringstream ss;
        ss << "[" << x << ", " << y << ", " << z << ", " << w << "]";
        return ss.str();
    }

    void Vec4::Normalize()
    {
        float s = GetScale();
        x /= s;
        y /= s;
        z /= s;
        w /= s;
    }

    Vec4 Vec4::GetNormalized() const
    {
        float s = GetScale();
        return Vec4(x/s, y/s, z/s, w/s);
    }

    float Vec4::Dot(Vec4 const& other) const
    {
       return x * other.x +
              y * other.y +
              z * other.z +
              w * other.w;
    }

    Vec4 Vec4::operator+(Vec4 const& other) const
    {
        return Vec4(
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w
        );
    }

    Vec4& Vec4::operator+=(Vec4 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Vec4 Vec4::operator-(Vec4 const& other) const
    {
        return Vec4(
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w
        );
    }

    Vec4& Vec4::operator-=(Vec4 const& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Vec4 Vec4::operator*(float scalar) const
    {
        return Vec4(
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        );
    }

    Vec4& Vec4::operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    Vec4 Vec4::operator/(float scalar) const
    {
        return Vec4(
            x / scalar,
            y / scalar,
            z / scalar,
            w / scalar
        );
    }

    Vec4& Vec4::operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

}

