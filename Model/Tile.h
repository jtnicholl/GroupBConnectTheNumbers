#ifndef MODEL_TILE_H
#define MODEL_TILE_H

namespace model {

/**
 * Object representing a puzzle tile.
 */
class Tile
{
public:
	/**
	 * Construct a new tile. If a value is provided, the tile will be immutable.
	 *
	 * @param value Initial value for the tile
	 */
	Tile(int value = 0);
	/**
	 * Destructor.
	 */
	virtual ~Tile();
	/**
	 * Get the value in the tile.
	 *
	 * @return the value in the tile
	 */
	int getValue() const;
	/**
	 * Returns whether the tile is immutable or not.
	 *
	 * @return True if the tile's value cannot be changed, else false
	 */
	bool isImmutable() const;
	/**
	 * Set the value of the tile if it is mutable.
	 *
	 * @param value Value to set
	 *
	 * @return true if the value was set, else false
	 */
	bool trySetValue(int value);

private:
	int value;
	bool immutable;
};

} // namespace model

#endif // MODEL_TILE_H
