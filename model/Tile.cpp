#include "Tile.h"

namespace model {

Tile::Tile()
{
	this->value = 0;
	this->immutable = false;
}

Tile::Tile(int value, bool immutable)
{
	this->value = value;
	this->immutable = immutable;
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
