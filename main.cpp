#include <iostream>
#include "Renderer.h"
#include "Triangle.h"
#include "Color.h"

using namespace std;

int main()
{
    char ARGB[4] = {0,(char)0x00,(char)0x00,(char)0};
    short SIZE[2] = {800, 500};

    Renderer render(ARGB, SIZE);

    char triangleColors[3][4];
    memcpy(triangleColors[0], RED, 4);
    memcpy(triangleColors[1], GREEN, 4);
    memcpy(triangleColors[2], BLUE, 4);

    //render.RenderTriangle(-1.8f, -0.8f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.0f, triangleColors);
    render.RenderTriangle(-1.2f, -0.8f, 0.5f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, triangleColors);

    char triangleColors2[3][4];
    memcpy(triangleColors2[0], YELLOW, 4);
    memcpy(triangleColors2[1], CYAN, 4);
    memcpy(triangleColors2[2], MAGENTA, 4);

    //render.RenderTriangle(-0.7f, -0.2f, 0.2f, 0.6f, 0.8f, -0.6f, 0.0f, 0.0f, 0.5f, triangleColors2);
    render.RenderTriangle(0.5f, -0.5f, 0.5f, 0.5f, 0.8f, -0.6f, 0.0f, 0.0f, 0.0f, triangleColors2);

    render.Save();

    return 0;
}
