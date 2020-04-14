#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <vector>

namespace view
{

/**
 * Each view gui class that handles user input
 * or presents model information should extend
 * this class to interact with the system.
 */
class GameInterface
{
protected:
    GameInterface();

    virtual ~GameInterface();

    int getCurrentLevel() const;
    bool tryAdvanceLevel();

    int getGameBoardWidth() const;
    int getGameBoardHeight() const;

    bool trySetTileNumber(int xPosition, int yPosition, int value);
    const std::vector<const std::vector<int>> getPlayerTileValues() const;

};

}

#endif // GAMEINTERFACE_H
