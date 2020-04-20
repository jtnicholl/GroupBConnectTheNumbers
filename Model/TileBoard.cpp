#include "TileBoard.h"

namespace model {

TileBoard::TileBoard()
{
	this->tiles = new Tile*[BOARD_AREA];
	for (int i = 0; i < BOARD_AREA; i++)
	{
		this->tiles[i] = nullptr;
	}
}

TileBoard::~TileBoard()
{
	for (int i = 0; i < BOARD_AREA; i++)
	{
		if (this->tiles[i] != nullptr)
		{
			delete this->tiles[i];
		}
	}
	delete this->tiles;
}

Tile* TileBoard::getTile(int x, int y) const
{
	return this->tiles[x + y*BOARD_WIDTH];
}

Tile* TileBoard::getTile(int position) const
{
	return this->tiles[position];
}

void TileBoard::setTile(int position, Tile* tile)
{
	if (this->tiles[position] != nullptr)
	{
		delete this->tiles[position];
	}
	this->tiles[position] = tile;
}

} // namespace model
