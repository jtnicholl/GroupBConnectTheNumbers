#include "Tile.h"

namespace model {

Tile::Tile(int value)
{
	this->value = value;
	this->immutable = value != 0;
}

Tile::~Tile()
{
}

int Tile::getValue() const
{
	return this->value;
}

bool Tile::isImmutable() const
{
	return this->immutable;
}

bool Tile::trySetValue(int value)
{
	if (this->immutable)
	{
		return false;
	}
	else
	{
		this->value = value;
		return true;
	}
}

} // namespace model
