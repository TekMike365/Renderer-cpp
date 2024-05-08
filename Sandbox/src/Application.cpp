#include <iostream>
#include <string>

#include "Renderer.h"

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    Renderer::Vec3 vertices[4] = {
        Renderer::Vec3(-0.5f, -0.5f, -0.5f),
        Renderer::Vec3( 0.5f, -0.5f, -0.5f),
        Renderer::Vec3( 0.5f,  0.5f, -0.5f),
        Renderer::Vec3(-0.5f,  0.5f, -0.5f)
    };

    int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    Renderer::Mat4 mat = Renderer::Mat4::Identity();
    mat.Transform(Renderer::Vec3(0.0f, 0.0f, -10.0f));
    //mat.Scale(Renderer::Vec3(1.0f, 1.0f, 1.0f) / 2);
    printf(mat.ToString().c_str());

    for (int i = 0; i < 4; i++) {
        std::cout << vertices[i].ToString() + " ";
        Renderer::Vec4 oldVertex(vertices[i].x, vertices[i].y, vertices[i].z, 1.0f);
        Renderer::Vec4 newVertex = mat * oldVertex;
        vertices[i] = Renderer::Vec3(newVertex.x, newVertex.y, newVertex.z);
        std::cout << vertices[i].ToString() << std::endl;
    }

    Renderer::Init(640, 480);
    Renderer::Render(vertices, indices, 6);
    Renderer::SaveBMP("test.bmp");
    Renderer::Cleanup();

    return 0;
}

