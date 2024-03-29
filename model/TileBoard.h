#ifndef MODEL_TILEBOARD_H
#define MODEL_TILEBOARD_H

#include "Tile.h"

namespace model {

/**
 * Object representing a puzzle board.
 */
class TileBoard {
public:
    /**
    * The width of a puzzle board.
    */
    static const int BOARD_WIDTH = 8;
    /**
    * The total area of a puzzle board.
    */
    static const int BOARD_AREA = BOARD_WIDTH * BOARD_WIDTH;

    /**
     * Default constructor. Tiles must be set after constructing the board.
     */
    TileBoard();
    /**
     * Destructor.
     */
    virtual ~TileBoard();
    /**
     * Get a tile on the board using coordinates.
     *
     * @pre x >= 0, x < BOARD_WIDTH, y >= 0, y < BOARD_WIDTH
     *
     * @return the tile at the given position
     */
    Tile* getTile(int x, int y) const;
    /**
     * Get a tile on the board using a single position number.
     *
     * @pre position >= 0, position < BOARD_AREA
     *
     * @return the tile at the given position
     */
    Tile* getTile(int position) const;
    /**
     * Set a new tile at the given position.
     * If one already exists there, it will be deleted.
     *
     * @pre position >= 0, position < BOARD_AREA
     * @post getTile(position) == tile
     */
    void setTile(int position, Tile* tile);
    /**
     * Check if any of the tiles contain the given value.
     *
     * @param value value to check
     *
     * @return true if the number is present, else false
     */
    bool contains(int value) const;
    /**
     * Check if the puzzle has been solved.
     *
     * @return true if the puzzle is solved, else false
     */
    bool isSolved() const;

private:
    Tile** tiles;

    bool tileValid(int position) const;
    void checkPosition(int position, int value, bool& hasUpper, bool& hasLower) const;
};

} // namespace model

#endif // MODEL_TILEBOARD_H
