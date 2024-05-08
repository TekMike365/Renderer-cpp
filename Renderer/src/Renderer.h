#pragma once

#include "vector/Vec2.h"
#include "vector/Vec3.h"
#include "vector/Vec4.h"
#include "vector/Mat4.h"

#define RENDERER_NONE 0
#define RENDERER_ORTHOGRAPHIC_CAMERA 1
#define RENDERER_PERSPECTIVE_CAMERA 2

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

