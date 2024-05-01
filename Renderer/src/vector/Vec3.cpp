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

    void Vec3::Normalize()
    {
        float s = GetScale();
        x /= s;
        y /= s;
        z /= s;
    }

    Vec3 Vec3::GetNormalized() const
    {
        float s = GetScale();
        return Vec3(x/s, y/s, z/s);
    }

    float Vec3::Dot(Vec3 const& other) const
    {
       return x * other.x +
              y * other.y +
              z * other.z;
    }

    Vec3 Vec3::Cross(Vec3 const& other) const
    {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    bool Vec3::operator==(Vec3 const &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool Vec3::operator!=(Vec3 const &other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    Vec3 Vec3::operator+(Vec3 const& other) const
    {
        return Vec3(
            x + other.x,
            y + other.y,
            z + other.z
        );
    }

    Vec3& Vec3::operator+=(Vec3 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3 Vec3::operator-(Vec3 const& other) const
    {
        return Vec3(
            x - other.x,
            y - other.y,
            z - other.z
        );
    }

    Vec3& Vec3::operator-=(Vec3 const& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 Vec3::operator*(float scalar) const
    {
        return Vec3(
            x * scalar,
            y * scalar,
            z * scalar
        );
    }

    Vec3& Vec3::operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vec3 Vec3::operator/(float scalar) const
    {
        return Vec3(
            x / scalar,
            y / scalar,
            z / scalar
        );
    }

    Vec3& Vec3::operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

}

