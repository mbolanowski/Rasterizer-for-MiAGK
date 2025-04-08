//
// Created by mbola on 3/20/2025.
//

#ifndef INC_1_RENDERER_H
#define INC_1_RENDERER_H

#pragma once

#include <iostream>
#include <algorithm>

class Renderer
{
public:
    Renderer(char ARGB[4], short SIZE[2]);
    ~Renderer();

    void Save();
    void RenderTriangle(float x1, float y1,float x2, float y2, float x3, float y3, float z1, float z2, float z3, char ARGB[3][4]);
    float EdgeFunction(float x1, float x2, float y1, float y2, float x, float y);
    void SetPixel(int x, int y, char ARGB[4]);
    void SetDepth(int x, int y, float depth);

    char header[18];
    short sizes[2];
    char* pixelData;
    float* depthData;

    void MultiplyColor(float f, const char in[4], float out[4]) {
        out[0] = in[0] * f;
        out[1] = in[1] * f;
        out[2] = in[2] * f;
        out[3] = in[3] * f;
    }

    void AddColors(char a[4], char b[4], char c[4], char final[4]){
        final[0] = a[0] + b[0] + c[0];
        final[1] = a[1] + b[1] + c[1];
        final[2] = a[2] + b[2] + c[2];
        final[3] = a[3] + b[3] + c[3];

        std::cout << final[0];
    }

private:
};


#endif //INC_1_RENDERER_H
