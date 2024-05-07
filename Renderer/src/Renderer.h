#pragma once

#include "vector/Vec2.h"
#include "vector/Vec3.h"
#include "vector/Vec4.h"
#include "vector/Mat4.h"

#define NONE 0
#define ORTHOGRAPHIC_CAMERA 1
#define PERSPECTIVE_CAMERA 2

namespace Renderer {

    struct Pixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        int d;
    };

    int Init(int width, int height);
    int Cleanup();
    int SetCamera(int cameraType);
    int Render(Vec3* vertices, int* indices, int indexCount);
    int SaveBMP(const char* filepath);

}

