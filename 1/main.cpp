#include <iostream>
#include "Renderer.h"
using namespace std;

int main()
{
    char ARGB[4] = {0,(char)0xFF,(char)0xFF,(char)0};
    short SIZE[2] = {100, 800};

    Renderer render(ARGB, SIZE);
    render.Save();

    return 0;
}
