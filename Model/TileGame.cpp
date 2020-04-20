#include "TileGame.h"

namespace model
{

TileGame::TileGame(TileBoard* board)
{
    this->board = board;
}

TileGame::~TileGame()
{
	delete this->board;
}

bool TileGame::isTileMutable(int x, int y) const
{
	return !this->board->getTile(x, y)->isImmutable();
}

int TileGame::getTileValue(int x, int y) const
{
	return this->board->getTile(x, y)->getValue();
}

bool TileGame::setTileValue(int x, int y, int value)
{
	return this->board->getTile(x, y)->trySetValue(value);
}

bool TileGame::isSolved() const
{
	return this->board->isSolved();
}

}
