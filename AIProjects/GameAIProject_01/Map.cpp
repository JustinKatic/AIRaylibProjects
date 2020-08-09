#include "Map.h"

Map::Map()
{

	InitWindow(m_screenWidth, m_screenHeight, "TEST");
}

Map::~Map()
{

}

void Map::Load()
{
}

void Map::Update(float deltaTime)
{

}

void Map::Draw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	int tw = m_tileWidth;
	int th = m_tileHeight;

	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (size_t x = 0; x < MAP_COLS; x++)
		{
			int xPos = x * tw;
			int yPos = y * th;
			int tileID = m_map[y][x];

			if (tileID == WALL)
			{
				DrawRectangle(xPos, yPos, tw, th, GREEN);
			}
		}
	}
	EndDrawing();
}
