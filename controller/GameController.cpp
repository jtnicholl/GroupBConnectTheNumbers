#include "GameController.h"

#include "../fileio/PuzzleLoader.h"
#include "../fileio/PuzzleSaver.h"
#include "../fileio/Utils.cpp"
#include "../model/TileBoard.h"

using namespace fileio;

namespace controller
{

GameController::GameController()
{
    this->currentLevel = fileExists(LAST_OPEN_PUZZLE_FILENAME) ? std::stoi(loadText(LAST_OPEN_PUZZLE_FILENAME)) : 0;
    std::string filename = fileExists(SAVED_PUZZLES_FILENAME) ? SAVED_PUZZLES_FILENAME : DEFAULT_PUZZLES_FILENAME;
	this->boards = PuzzleLoader::loadPuzzlesFromFile(filename);
	this->game = new TileGame(this->boards[this->currentLevel]);
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
	this->game->setBoard(this->boards[level]);
	saveText(std::to_string(level), LAST_OPEN_PUZZLE_FILENAME);
}

unsigned int GameController::getAvailableLevels() const
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
	return this->game->trySetTileValue(position, value);
}

int GameController::getTileValue(int position) const
{
	return this->game->getTileValue(position);
}

bool GameController::isTileImmutable(int position) const
{
	return this->game->isTileImmutable(position);
}

bool GameController::isSolved() const
{
	return this->game->isSolved();
}

void GameController::resetCurrentPuzzle()
{
	for (int i = 0; i < TileBoard::BOARD_AREA; i++)
	{
		this->game->trySetTileValue(i, 0);
	}
}

void GameController::saveAllPuzzles() const
{
	PuzzleSaver::savePuzzlesToFile(this->boards, SAVED_PUZZLES_FILENAME);
}

}
