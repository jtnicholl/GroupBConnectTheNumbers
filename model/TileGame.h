#ifndef ITILEGAME_H
#define ITILEGAME_H

#include "TileBoard.h"

namespace model
{

/**
 * Object representing a tile puzzle.
 */
class TileGame
{
public:
	/**
	 * Constructs a new TileGame.
	 *
	 * @pre tileBoard != nullptr
	 *
	 * @param board TileBoard to use for the game
	 */
	TileGame(TileBoard* board);
    /**
     * Destructor.
     */
    virtual ~TileGame();

    /**
     * Returns true if the tile at the given position can have its value changed.
     *
     * @pre x >= 0, x < TileBoard::BOARD_WIDTH, y >= 0, y < TileBoard::BOARD_WIDTH, value >= 0
     *
     * @param x x position
     * @param y y position
     *
     * @return true if the tile is mutable, else false
     */
    bool isTileMutable(int x, int y) const;
    /**
     * Get the value of the specified tile.
     *
     * @pre x >= 0, x < TileBoard::BOARD_WIDTH, y >= 0, y < TileBoard::BOARD_WIDTH, value >= 0
     *
     * @param x x position
     * @param y y position
     *
     * @return The value in the specified tile
	 */
	int getTileValue(int x, int y) const;
    /**
     * Sets the tile number at the specified position to the specified value.
     *
     * @pre x >= 0, x < TileBoard::BOARD_WIDTH, y >= 0, y < TileBoard::BOARD_WIDTH, value >= 0, value <= 64
     * @post if isTileMutable(x, y), then getTileValue(x, y) == value
     *
     * @param x the x position of the tile to set
     * @param x the y position of the tile to set
     * @param value the value to set at the x, y position
     *
     * @return true if the value was set, else false
     */
    bool setTileValue(int x, int y, int value);
    /**
     * Retruns if the puzzle has been solved.
     *
     * @return true if the puzzle has been solved, else false
     */
     bool isSolved() const;

private:
	TileBoard* board;
};

}

#endif // ITILEGAME_H
