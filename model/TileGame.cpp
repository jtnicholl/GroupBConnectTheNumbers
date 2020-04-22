#include "TileGame.h"

namespace model
{

TileGame::TileGame(TileBoard* board)
{
    this->board = board;
}

TileGame::~TileGame()
{

}

bool TileGame::isTileMutable(int position) const
{
	return !this->board->getTile(position)->isImmutable();
}

int TileGame::getTileValue(int position) const
{
	return this->board->getTile(position)->getValue();
}

bool TileGame::setTileValue(int position, int value)
{
	return this->board->getTile(position)->trySetValue(value);
}

bool TileGame::isSolved() const
{
	return this->board->isSolved();
}

}
