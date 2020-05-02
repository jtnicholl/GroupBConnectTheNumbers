#ifndef ITILEGAME_H
#define ITILEGAME_H

#include "TileBoard.h"

namespace model {

/**
 * Object representing a tile puzzle.
 */
class TileGame {
public:
    /**
     * Constructs a new TileGame.
     *
     * @pre board != nullptr
     *
     * @param board TileBoard to use for the game
     */
    TileGame(TileBoard* board);
    /**
     * Destructor. Does NOT delete the stored board.
     */
    virtual ~TileGame();

    /**
     * Returns true if the tile at the given position can not have its value changed.
     *
     * @pre position >= 0, x < TileBoard::BOARD_AREA
     *
     * @param position the position to check
     *
     * @return true if the tile is immutable, else false
     */
    bool isTileImmutable(int position) const;
    /**
     * Get the value of the specified tile.
     *
     * @pre position >= 0, x < TileBoard::BOARD_AREA
     *
     * @param position the position to get
     *
     * @return The value in the specified tile
     */
    int getTileValue(int position) const;
    /**
     * Sets the tile number at the specified position to the specified value.
     *
     * @pre position >= 0, x < TileBoard::BOARD_AREA, value >= 0, value <= 64
     * @post if isTileMutable(position) and the value is not already present, then getTileValue(position) == value
     *
     * @param position the position position of the tile to set
     * @param value the value to set at the position
     *
     * @return true if the value was set, else false
     */
    bool trySetTileValue(int position, int value);
    /**
     * Sets the board for the current game.
     *
     * @pre board != nullptr
     * @post board is updated
     *
     * @param board TileBoard to use for the game
     */
    void setBoard(TileBoard* board);
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
