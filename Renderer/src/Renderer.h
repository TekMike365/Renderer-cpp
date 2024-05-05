#pragma once

#include <cstdint>

#include "vector/Vec2.h"
#include "vector/Vec3.h"
#include "vector/Vec4.h"
#include "vector/Mat4.h"

namespace Renderer {

    struct Pixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        int d;
    };

    int Init(int width, int height);
    int Cleanup();
    int SaveBMP(const char* filepath);

}

