#ifndef ITILE_H
#define ITILE_H

namespace model::tiles
{

/**
 * This interface is implemented by object's that
 * behave as tiles in the game. Tiles have x and
 * y positions as well as hold values. An immutable
 * tile is one that can not have its value changed.
 */
class ITile
{
public:
    /**
     * Deallocates this ITile object and all of
     * its resources.
     */
    virtual ~ITile();

    /**
     * Gets the x position of this tile on the game
     * board.
     *
     * @return the x position of this tile.
     */
    virtual int getX() const = 0;

    /**
     * Gets the y position of this tile on the game
     * board.
     *
     * @return the y position of this tile.
     */
    virtual int getY() const = 0;

    /**
     * Determines whether this tile is immutable or not.
     * An immutable tile means its value can not be changed.
     *
     * @return true if this tile can not have its value changed; false otherwise.
     */
    virtual bool isValueImmutable() const = 0;

    /**
     * Gets the current value of this tile.
     *
     * @return the current value of this tile.
     */
    virtual int getValue() const = 0;

    /**
     * Tries to set the value of this tile. If this tile is
     * immutable, then the value is not changed and this method
     * returns false.
     *
     * @pre value > 0 && value < 65
     * @post if trySetValue(x), then getValue() == x
     *
     * @param value the new value to set.
     *
     * @return true if the value is successfully set; false otherwise.
     */
    virtual bool trySetValue(int value) = 0;
};

}

#endif // ITILE_H
