#include <iostream>

#include "../../Renderer/src/vec3.h"

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    Renderer::Vec3 vec(1.0f, 2.0f, 3.0f);
    std::cout << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]" << std::endl;
    
    return 0;
}

