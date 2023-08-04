#include "Renderer.h"

void Renderer::draw()
{
	//add offsets

	clearScreen();
	std::vector<int> yValues;
	for (auto& vertex : vertices)
	{
		int roundedVertexY = std::round(vertex.y);
		yValues.emplace_back(roundedVertexY);
	}

	std::sort(yValues.begin(), yValues.end(), std::less<int>());

	//init heightmap

	for (int y : yValues)
	{
		heightmap.emplace(y, std::vector<Vector3>());
	}

	int maxY{};

	for (auto& vertex : vertices)
	{
		int roundedVertexY = std::round(vertex.y);
		heightmap.at(roundedVertexY).emplace_back(vertex);
		//std::cout << "added vertex: " << vertex.x << ' ' << vertex.y << '\n';
	}

	// draw
	int prevY{};
	for (auto& it : heightmap)
	{
		int difY{};
		if ((difY = it.first - prevY) > 0)
		{
			prevY = it.first;
			for (int i = 0; i < difY; i++)
				std::cout << '\n';
		}

		std::vector<int> xValues;

		//get all x values
		for (int j = 0; j < it.second.size(); j++)
		{
			xValues.push_back(std::round(it.second.at(j).x));
		}

		std::sort(xValues.begin(), xValues.end(), std::less<int>());

		//draw stuff from x values
		int prevX{};
		std::string line{};
		for (int x : xValues)
		{
			if (x - prevX > 0)
			{
				for (int i = 0; i < x - prevX; i++)
					line.append("  ");
				line.append("X");
				prevX = x;
			}
			else if (x == 0)
			{
				line.append("X");
			}
		}
		if (line.size() != 0)
			std::cout << line;
	}
	
	heightmap.clear();
}

void Renderer::swap()
{

}

void Renderer::addVertex(float x, float y, float z)
{
	vertices.emplace_back(x + offset.x, y + offset.y, z + offset.z);
}

void Renderer::clearVertices()
{
	vertices.clear();
}

// in radians, btw
void Renderer::rotateVertices(float rX, float rY, float rZ)
{
	for (auto& vertex : vertices)
	{
		vertex = vertex - offset;
		vertex.rotate(rX, rY, rZ);
		vertex = vertex + offset;
	}
}

void Renderer::setVertexOffset(float offsetX, float offsetY, float offsetZ)
{
	this->offset = Vector3(offsetX, offsetY, offsetZ);
}

void Renderer::setScale(double scale)
{
	this->scale = scale;
}

void Renderer::clearScreen()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}