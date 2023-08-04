#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <windows.h>

#include "Vector3.h"

class Renderer {
private:
	Vector3 offset;
	double scale{ 1.0 };
	//heightmap, quite literally a heightmap
	std::map<int, std::vector<Vector3>> heightmap;
	std::vector<Vector3> vertices;

public:
	void draw();
	void swap();
	void addVertex(float x, float y, float z);
	void clearVertices();
	void rotateVertices(float rX, float rY, float rZ);
	void setVertexOffset(float offsetX, float offsetY, float offsetZ);
	void setScale(double scale);
	void clearScreen();
};