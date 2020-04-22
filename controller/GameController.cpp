#include "GameController.h"

#include "../fileio/PuzzleLoader.h"

namespace controller
{

GameController::GameController()
{
    this->currentLevel = 0;
	this->boards = fileio::PuzzleLoader::loadPuzzlesFromFile(PUZZLES_FILENAME);
	this->game = new TileGame(this->boards.front());
}

GameController::~GameController()
{
	delete this->game;
	// TODO delete boards
}

int GameController::getCurrentLevel() const
{
	return this->currentLevel;
}

void GameController::setCurrentLevel(int level)
{
	this->currentLevel = level;
	delete this->game;
	this->game = new TileGame(this->boards[level]);
}

int GameController::getAvailableLevels() const
{
	return this->boards.size();
}

bool GameController::tryAdvanceLevel()
{
	if (this->game->isSolved() && this->currentLevel < this->boards.size() - 1)
	{
		setCurrentLevel(this->currentLevel + 1);
		return true;
	}
	else
	{
		return false;
	}
}

bool GameController::trySetTileValue(int position, int value)
{
	return this->game->setTileValue(position, value);
}

int GameController::getTileValue(int position) const
{
	return this->game->getTileValue(position);
}

void GameController::saveAllPuzzles() const
{
	// TODO
}

}
