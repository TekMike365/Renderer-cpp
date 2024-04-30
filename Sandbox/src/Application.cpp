#include <iostream>
#include <string>

#include "Vec3.h"

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    Renderer::Vec3 vec(1.0f, 2.0f, 3.0f);
    std::cout << vec.ToString() << std::endl;
    
    return 0;
}

