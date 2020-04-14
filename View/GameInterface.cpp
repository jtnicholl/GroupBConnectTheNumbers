#include "GameInterface.h"

namespace view
{

GameInterface::GameInterface()
{
}

int GameInterface::getCurrentLevel() const
{
    return controller::GameController::getSingleton()->getCurrentLevel();
}

bool GameInterface::tryAdvanceLevel()
{
    return controller::GameController::getSingleton()->tryAdvanceLevel();
}

int GameInterface::getGameBoardWidth() const
{
    return controller::GameController::getSingleton()->getGameBoardWidth();
}

int GameInterface::getGameBoardHeight() const
{
    return controller::GameController::getSingleton()->getGameBoardHeight();
}

bool GameInterface::trySetTileNumber(int xPosition, int yPosition, int value)
{
    return controller::GameController::getSingleton()->trySetTileNumber(xPosition, yPosition, value);
}

const std::vector<const std::vector<int>> GameInterface::getPlayerTileValues() const
{
    return controller::GameController::getSingleton()->getPlayerTileValues();
}

GameInterface::~GameInterface()
{
}

}
