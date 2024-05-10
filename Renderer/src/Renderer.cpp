#include "Renderer.h"

#include <iostream>
#include <fstream>

#define NO_DEPTH_DATA 1

namespace Renderer {

    Pixel* screen = nullptr;
    int screenWidth = 0;
    int screenHeight = 0;
    int camera = RENDERER_NONE;

    int Init(int width, int height)
    {
        screenWidth = width;
        screenHeight = height;
        screen = new Pixel[width * height];
        if (screen == nullptr)
            return 1;
        
        for (int i = 0; i < screenWidth * screenHeight; i++) {
            screen[i].r = 0x00;
            screen[i].g = 0x00;
            screen[i].b = 0x00;
            screen[i].d = NO_DEPTH_DATA;
        }

        return 0;
    }

    int Cleanup()
    {
        delete[] screen;
        return 0;
    }

    int SetCamera(int cameraType)
    {
        if (cameraType != RENDERER_ORTHOGRAPHIC_CAMERA && cameraType != RENDERER_PERSPECTIVE_CAMERA) {
            return 1;
        }
        camera = cameraType;
        return 0;
    }

    Vec3 ProjectPoint(Vec3 point) {
        switch (camera)
        {
            case RENDERER_ORTHOGRAPHIC_CAMERA:
                return point;
            case RENDERER_PERSPECTIVE_CAMERA:
            {
                // TODO add focal distance as a setting of FOV
                float focalDist = 1.036596; // FOV = 60 deg
                float t = focalDist / (focalDist - point.z);
                return Vec3(point.x * t, point.y * t, point.z);
            }
            default:
                return point;
        }
    }

    float GetTriangleArea(Vec2 p1, Vec2 p2, Vec2 p3)
    {
        Vec2 v1 = p1 - p3;
        Vec2 v2 = p2 - p3;
        Vec3 a = Vec3(v1.x, v1.y, 0.0);
        Vec3 b = Vec3(v2.x, v2.y, 0.0);
        return std::abs(a.Cross(b).GetScale() / 2);
    }

    float Lerp(float v1, float v2, float t) 
    {
        return (1 - t) * v1 + t * v2;
    }

    float TLerp(float v1, float v2, float v3, Vec2 t) 
    {
        float i = Lerp(v1, v2, t.x);
        return Lerp(v3, i, t.y);
    }

    Vec2 GetLerpValues(Vec2 point, Vec3 p1, Vec3 p2, Vec3 p3) {
        Vec2 va = Vec2(p2.x, p2.y) - Vec2(p1.x, p1.y);
        Vec2 vc = point - Vec2(p3.x, p3.y);

        float b = vc.y * (p1.x - p3.x) - vc.x * (p1.y - p3.y);
        float a = vc.y * va.x - vc.x * va.y;

        if (a == 0)
            return Vec2(-1, -1);

        float t = - b / a;

        Vec2 vi = Vec2(p1.x, p1.y) + va * t;
        Vec2 vn = vi - Vec2(p3.x, p3.y);

        if (vn.GetScale() == 0)
            return Vec2(-1, -1);
        
        float s = vc.GetScale() / vn.GetScale();

        return Vec2(t, s);
    }

    int Render(Vec3 *vertices, int *indices, int indexCount)
    {
        // iterate trough triplets
        for (int i = 0; i < indexCount; i += 3) {
            Vec3 points[3] = {
                ProjectPoint(vertices[indices[i + 0]]),
                ProjectPoint(vertices[indices[i + 1]]),
                ProjectPoint(vertices[indices[i + 2]])
            };

            // Convert to pixels
            // TODO: exclude non renderable triangles
            for (int j = 0; j < 3; j++) {
                points[j] *= screenWidth;
                points[j] += Vec3(screenWidth / 2, screenHeight / 2, 0.0);
            }


            int p1_x = (int)std::min(points[0].x, std::min(points[1].x, points[2].x));
            p1_x = std::max(p1_x, 0);
            int p1_y = (int)std::min(points[0].y, std::min(points[1].y, points[2].y));
            p1_y = std::max(p1_y, 0);
            int p2_x = (int)std::max(points[0].x, std::max(points[1].x, points[2].x));
            p2_x = std::min(p2_x, screenWidth);
            int p2_y = (int)std::max(points[0].y, std::max(points[1].y, points[2].y));
            p2_y = std::min(p2_y, screenHeight);
            int width = p2_x - p1_x;
            int height = p2_y - p1_y;

            // Rasterize
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < width; k++) {
                    int x = p1_x + k;
                    int y = p1_y + j;
                    int idx = screenWidth * y + x;

                    // is point in triangle?
                    Vec2 pixelPos = Vec2(x, y);
                    Vec2 p1 = Vec2(std::floor(points[0].x), std::floor(points[0].y));
                    Vec2 p2 = Vec2(std::floor(points[1].x), std::floor(points[1].y));
                    Vec2 p3 = Vec2(std::floor(points[2].x), std::floor(points[2].y));
                    float a  = GetTriangleArea(p1, p2, p3);
                    float a1 = GetTriangleArea(pixelPos, p1, p2);
                    float a2 = GetTriangleArea(pixelPos, p2, p3);
                    float a3 = GetTriangleArea(pixelPos, p3, p1);
                    
                    float diff = a1 + a2 + a3 - a;
                    bool isInside = diff == 0.0;

                    if (!isInside)
                        continue;

                    // lerp Z coords
                    Vec2 lerpVals = GetLerpValues(Vec2(x, y), points[0], points[1], points[2]);
                    if (lerpVals.x < 0 || lerpVals.y < 0)
                        continue;

                    float depth = TLerp(points[0].z, points[1].z, points[2].z, lerpVals);
                    Pixel pixel = screen[idx];
                    if (depth > pixel.d)
                        continue;
                    
                    pixel.r = 0xff * k / width;
                    pixel.g = 0xff * j / height;
                    pixel.b = 0x00;

                    screen[idx] = pixel;
                }
            }
        }
        return 0;
    }

    void ToBinary(char* arr, uint32_t val)
    {
        for (int i = 0; i < 4; i++) {
            arr[i] = (val & 0xff << i * 8) >> i * 8;
        }
    }

    int SaveBMP(const char* filepath)
    {
        if (screen == nullptr)
            return 1;

        uint32_t r = (screenWidth * 3) % 4;
        uint32_t pad = r == 0 ? 0 : 4 - r;
        uint32_t row = screenWidth * 3 + pad;
        uint32_t dataSize = row * screenHeight;
        uint32_t fileSize = dataSize + 54;

        char data[fileSize];
        // BMP header
        data[0] = 'B';
        data[1] = 'M';                      // 2    ID field
        ToBinary(data + 2, fileSize);       // 4    Size of BMP file
        ToBinary(data + 6, 0);              // 2+2  Unused
        ToBinary(data + 10, 54);            // 4    Offset to pixel array
        // DIB header
        ToBinary(data + 14, 40);            // 4    DIB header size
        ToBinary(data + 18, screenWidth);   // 4    BMP width in pixels
        ToBinary(data + 22, screenHeight);  // 4    BMP height in pixels
        data[26] = 0x01;
        data[27] = 0x00;                    // 2    Number of color planes
        data[28] = 0x18;
        data[29] = 0x00;                    // 2    Number of bits pre pixel (BPP)
        ToBinary(data + 30, 0);             // 4    BI_RGB, pixel array compression (none)
        ToBinary(data + 34, dataSize);      // 4    Size of raw BMP data
        ToBinary(data + 38, 2835);          // 4    Horizontal resolution of the image (pixel prem meter)
        ToBinary(data + 42, 2835);          // 4    Vertical resolution of the image (pixel prem meter)
        ToBinary(data + 46, 0);             // 4    number of colors in palette
        ToBinary(data + 50, 0);             // 4    number of important colors (all)

        // Pixel Array
        char* pArr = data + 54;
        for (int i = 0; i < screenHeight; i++) {
            for (int j = 0; j < screenWidth; j++) {
                int si = screenWidth * i + j;
                Pixel p = screen[si];
                pArr[0] = p.b;
                pArr[1] = p.g;
                pArr[2] = p.r;
                pArr += 3;
            }
            
            for (int n = 0; n < pad; n++) {
                *pArr = 0;
                pArr++;
            }
        }

        std::ofstream file(filepath, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file)
            return 2;

        file.write(data, sizeof(data));
        if (file.bad())
            return 3;

        file.close();
        return 0;
    }

}

