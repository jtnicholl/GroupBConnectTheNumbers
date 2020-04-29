#include "PuzzleSaver.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../model/Tile.h"

namespace fileio {

void PuzzleSaver::savePuzzlesToFile(const std::vector<TileBoard*>& boards, const std::string& filename) {
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);
    for (unsigned int i = 0; i < boards.size(); i++) {
        outfile << puzzleToLine(boards[i]) << std::endl;
    }
    outfile.close();
}

std::string PuzzleSaver::puzzleToLine(TileBoard* board) {
    std::stringstream output;
    for (int i = 0; i < TileBoard::BOARD_AREA; i++) {
        Tile* currentTile = board->getTile(i);
        if (currentTile->getValue() != 0) {
            output << i;
            output << (currentTile->isImmutable() ? ':' : ';');
            output << currentTile->getValue() << ',';
        }
    }
    return output.str();
}

void PuzzleSaver::savePuzzleTimesToFile(const std::vector<timing::Timer*>& times, const std::string& filename)
{
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);
    if (outfile.is_open())
    {
        for (std::vector<timing::Timer*>::const_iterator i = times.cbegin(); i != times.cend(); i++)
        {
            timing::Timer* currentTimer = *i;
            outfile << currentTimer->getSecondCount() << std::endl;
        }
        outfile.close();
    }
}

} // namespace fileio
