#ifndef WORLDMAP_H_
#define WORLDMAP_H_
#include <array>
#include "SFML/Graphics.hpp"

class WorldMap
{
public:
	WorldMap() = delete;
	static const int& GetElement(size_t x, size_t y);
public:
	static constexpr size_t width = 19;
	static constexpr size_t height = 8;
private:
	static constexpr std::array<int, width * height> worldMapData = {   
		1, 1, 2, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 2, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	};
};
#endif