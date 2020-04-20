#include "TileBoard.h"

#include <assert.h>

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
	assert(x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_WIDTH);
	return this->tiles[x + y*BOARD_WIDTH];
}

Tile* TileBoard::getTile(int position) const
{
	assert(position >= 0 && position < BOARD_AREA);
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

bool TileBoard::isSolved() const
{
	return false; // TODO
}

} // namespace model
