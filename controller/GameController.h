#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include <vector>

#include "../model/TileGame.h"
#include "../model/TileBoard.h"

using namespace model;

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
     * Construct a new GameController.
     */
    GameController();
    /**
     * Deconstructor.
     */
    virtual ~GameController();
    /**
     * Gets the current level of the game. The higher the level,
     * the higher the difficulty. getCurrentLevel() will never return
     * a number less than 0.
     *
     * @return the current game level
     */
    int getCurrentLevel() const;
	/**
	 * Gets the current level of the game. The higher the level,
     * the higher the difficulty.
     *
     * @pre level > 0, level < getAvailableLevels()
     * @post level is changed
     *
     * @param level new level to go to
     */
    void setCurrentLevel(int level);
	/**
     * Gets the number of levels available.
     *
     * @return the number of available levels
     */
    unsigned int getAvailableLevels() const;
    /**
     * Advances the game to the next level. If the level increment
     * is successful, then tryAdvanceLevel() returns true.
     *
     * @post if tryAdvanceLevel(), then getCurrentLevel() == getCurrentLevel()@prev + 1
     *
     * @return true if the level advancement was successful; false otherwise
     */
    bool tryAdvanceLevel();
    /**
     * Attempts to set the tile number at the specified position
     * to the specified value. If the position is immutable, then
     * this method will return false.
     *
     * @pre position >= 0, position < 64, value >= 0 value < 65
     * @post if trySetTileNumber(x, y, value), then getTileValue(x, y) == value
     *
     * @param position the position of the tile to set.
     * @param value the value to set
     *
     * @return true if the set operation is successful; false otherwise
     */
    bool trySetTileValue(int position, int value);
	/**
     * Gets the tile number at the specified position.
     *
     * @pre position >= 0, position < 64
     *
     * @return the value at the specified position
     */
    int getTileValue(int position) const;
    /**
     * Returns if the given tile is immutable.
     *
     * @pre position >= 0, position < 64
     *
     * @param position the position of the tile to check
     *
     * @return true if the tile is immutable, else false
     */
	bool isTileImmutable(int position) const;
	/**
	 * Reset the current puzzle by clearing all the player's inputs.
	 *
	 * @post puzzle is reset
	 */
	void resetCurrentPuzzle();
	/**
     * Saves all of the player's puzzles in progress to a file.
     *
     * @post puzzles are saved to a file on disk
     */
    void saveAllPuzzles() const;

private:
	const std::string PUZZLES_FILENAME = "default_puzzles.csv";

	int currentLevel;
	std::vector<TileBoard*> boards;
	TileGame* game;
};

}

#endif // GAMECONTROLLER_H
