#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>

namespace controller
{

/**
 * This controller interacts with the model game logic.
 * All access to the model should be made through this unified interface.
 */
class GameController
{
public:
    /**
     * Gets the singleton game controller that interactes
     * with the model logic.
     *
     * @return the singleton game controller.
     */
    static GameController* getSingleton();

    /**
     * Deallocates the GameController and all of its
     * respective resources.
     */
    virtual ~GameController();

    /**
     * Gets the current level of the game. The higher the level,
     * the higher the difficulty. getCurrentLevel() will never return
     * a number less than 1.
     *
     * @return the current game level.
     */
    virtual int getCurrentLevel() const = 0;

    /**
     * Advances the game to the next level. If the level increment
     * is successful, then tryAdvanceLevel() returns true.
     *
     * @post if tryAdvanceLevel(), then getCurrentLevel() == getCurrentLevel()@prev
     *
     * @return true if the level advancement was successful; false otherwise.
     */
    virtual bool tryAdvanceLevel() = 0;

    /**
     * Gets the width of the game board.
     *
     * @return the width of the game board.
     */
    virtual int getGameBoardWidth() const = 0;

    /**
     * Gets the height of the game board.
     *
     * @return the height of the game board.
     */
    virtual int getGameBoardHeight() const = 0;

    /**
     * Attempts to set the tile number at the specified position
     * to the specified value. If the position is immutable, then
     * this method will return false.
     *
     * @pre xPosition > 0 && yPosition > 0 && xPosition < getGameBoardWidth() && yPosition < getGameBoardHeight()
     *      && value > 1 && value < 65
     * @post if trySetTileNumber(x, y, z), then getPlayerTileValues()[y][x] == z
     *
     * @param xPosition the x position of the tile to set.
     * @param yPosition the y position of the tile to set.
     * @param value the value to set at the x, y position.
     *
     * @return true if the set operation is successful; false otherwise.
     */
    virtual bool trySetTileNumber(int xPosition, int yPosition, int value) = 0;

    /**
     * Gets all of the palyer tile values. These are the values that the player
     * has placed via the trySetTileNumber(int,int,int) method. Blank tiles have
     * value and immutable tiles have value -1.
     *
     * @return the two-dimensional array of integers that hold the player tile values.
     */
    virtual const std::vector<const std::vector<int>> getPlayerTileValues() const = 0;

protected:
    GameController();

private:
    static GameController* controller = nullptr;

};

}

#endif // GAMECONTROLLER_H
