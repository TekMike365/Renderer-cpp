#pragma once

namespace Renderer
{
    class Vec3
    {
    public:
        float x, y, z;

        Vec3();
        Vec3(float x, float y, float z);

        ~Vec3() = default;
    };

}

