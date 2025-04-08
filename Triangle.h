//
// Created by mbola on 3/26/2025.
//

#ifndef INC_1_TRIANGLE_H
#define INC_1_TRIANGLE_H

#pragma once

#include "Renderer.h"

class Triangle{
public:
    Triangle() : x1(0.0f), x2(0.0f), x3(0.0f), y1(0.0f), y2(0.0f), y3(0.0f){};
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3) : x1(x1), x2(x2), x3(x3), y1(y1), y2(y2), y3(y3){

    }

    void DrawTriangle(char ARGB[4]);
    float EdgeFunction(float );

    float x1,x2,x3,y1,y2,y3;
};

#endif //INC_1_TRIANGLE_H
