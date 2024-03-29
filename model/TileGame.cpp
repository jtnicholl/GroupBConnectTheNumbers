#include "TileGame.h"

namespace model {

TileGame::TileGame(TileBoard* board) {
    this->board = board;
}

TileGame::~TileGame() {
}

bool TileGame::isTileImmutable(int position) const {
    return this->board->getTile(position)->isImmutable();
}

int TileGame::getTileValue(int position) const {
    return this->board->getTile(position)->getValue();
}

bool TileGame::trySetTileValue(int position, int value) {
	if (this->board->getTile(position)->getValue() != value && this->board->contains(value)) {
		this->board->getTile(position)->trySetValue(0);
		return false;
	} else {
		return this->board->getTile(position)->trySetValue(value);
	}
}

void TileGame::setBoard(TileBoard* board) {
    this->board = board;
}

bool TileGame::isSolved() const {
    return this->board->isSolved();
}

}
