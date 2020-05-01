#include "ScoreEntry.h"

namespace model::scoring {

ScoreEntry::ScoreEntry(int time, std::string name, int puzzleLevel) {
    this->time = time;
    this->name = name;
    this->puzzleLevel = puzzleLevel;
}

ScoreEntry::~ScoreEntry() {

}

const int ScoreEntry::getTime() const {
    return this->time;
}

const std::string& ScoreEntry::getName() const {
    return this->name;
}

const int ScoreEntry::getPuzzleLevel() const {
    return this->puzzleLevel;
}

int ScoreEntry::compare(const ScoreEntry* other, SortType sortType) const {
    if (sortType == TIME_ASCENDING) {
        return compareTimes(other);
    } else if (sortType == PUZZLE_LEVEL_DESCENDING) {
        return comparePuzzleLevel(other);
    }
}

int ScoreEntry::compareTimes(const ScoreEntry* other) const {
    return this->getTime() - other->getTime();
}

int ScoreEntry::comparePuzzleLevel(const ScoreEntry* other) const {
    return this->getPuzzleLevel() - other->getPuzzleLevel();
}

}
