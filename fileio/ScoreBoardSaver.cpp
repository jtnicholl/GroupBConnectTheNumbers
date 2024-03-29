#include "ScoreBoardSaver.h"

#include <fstream>
#include <iostream>

namespace fileio {

void ScoreBoardSaver::saveScoreBoardToFile(const ScoreBoard* scoreboard, const std::string& filename) {
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);
    for (int i = 0; i < scoreboard->getSize(); i++) {
        outfile << scoreEntryToLine(scoreboard->getScore(i, ScoreEntry::SortType::TIME_ASCENDING)) << std::endl;
    }
    outfile.close();
}

std::string ScoreBoardSaver::scoreEntryToLine(const ScoreEntry* entry) {
    std::string name = entry->getName();
    std::string time = std::to_string(entry->getTime());
    std::string puzzle = std::to_string(entry->getPuzzleLevel());
    return name + "," + time + "," + puzzle;
}

}
