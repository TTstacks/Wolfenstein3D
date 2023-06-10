#include "WorldMap.h"

const int& WorldMap::GetElement(size_t x, size_t y)
{
	return worldMapData[y * width + x];
}
