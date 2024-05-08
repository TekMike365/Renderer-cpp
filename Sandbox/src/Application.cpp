#include <iostream>
#include <string>

#include "Renderer.h"

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    Renderer::Vec3 vertices[8] = {
        Renderer::Vec3(-0.5f, -0.5f, -0.5f),
        Renderer::Vec3( 0.5f, -0.5f, -0.5f),
        Renderer::Vec3( 0.5f,  0.5f, -0.5f),
        Renderer::Vec3(-0.5f,  0.5f, -0.5f),

        Renderer::Vec3(-0.5f, -0.5f,  0.5f),
        Renderer::Vec3( 0.5f, -0.5f,  0.5f),
        Renderer::Vec3( 0.5f,  0.5f,  0.5f),
        Renderer::Vec3(-0.5f,  0.5f,  0.5f)
    };

    int indices[36] = {
        0, 1, 2,
        2, 3, 0,

        1, 5, 6, // nope
        6, 2, 1,

        5, 4, 6, // nope
        6, 7, 5,

        4, 0, 3, // nope
        3, 7, 4,

        3, 2, 6, // nope
        6, 7, 3,

        1, 5, 4, // nope
        4, 0, 1
    };

    Renderer::Mat4 mat = Renderer::Mat4::Identity();
    mat.Transform(Renderer::Vec3(0.0f, 0.0f, 2.0f));
    mat.Scale(Renderer::Vec3(1.0f, 1.0f, 1.0f) / 5);

    for (int i = 0; i < 4; i++) {
        Renderer::Vec4 oldVertex(vertices[i].x, vertices[i].y, vertices[i].z, 1.0f);
        Renderer::Vec4 newVertex = mat * oldVertex;
        vertices[i] = Renderer::Vec3(newVertex.x, newVertex.y, newVertex.z);
    }

    Renderer::Init(640, 480);
    Renderer::SetCamera(RENDERER_PERSPECTIVE_CAMERA);
    Renderer::Render(vertices, indices, 36);
    Renderer::SaveBMP("test.bmp");
    Renderer::Cleanup();

    return 0;
}

