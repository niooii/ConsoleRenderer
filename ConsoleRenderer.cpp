// ConsoleRenderer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Renderer.h"

int main()
{
    printf("\033[?25l");
    Renderer renderer;

    renderer.setVertexOffset(20, 20, 0);


    renderer.addVertex(-8, -8, 8);
    renderer.addVertex(-8, 8, 8);
    renderer.addVertex(8, -8, 8);
    renderer.addVertex(8, 8, 8);

    renderer.addVertex(-8, -8, -8);
    renderer.addVertex(-8, 8, -8);
    renderer.addVertex(8, -8, -8);
    renderer.addVertex(8, 8, -8);
    
    
    while (true)
    {
        renderer.rotateVertices(0.1, 0.08, 0.07);
        Sleep(5);
        renderer.draw();
    }
}