#include "ScoreEntry.h"

namespace model::scoring
{

ScoreEntry::ScoreEntry(int time, std::string name, int puzzleLevel)
{
    this->time = time;
    this->name = name;
    this->puzzleLevel = puzzleLevel;
}

ScoreEntry::~ScoreEntry()
{

}

const int ScoreEntry::getTime() const
{
    return this->time;
}

const std::string& ScoreEntry::getName() const
{
    return this->name;
}

const int ScoreEntry::getPuzzleLevel() const
{
    return this->puzzleLevel;
}

bool ScoreEntry::compare(ScoreEntry* entry, SortType type) const
{
    bool isLessThan = false;
    if (type == TIME_ASCENDING)
    {
        isLessThan = compareTimes(entry);
    }
    else if (type == PUZZLE_LEVEL_DESCENDING)
    {
        isLessThan = comparePuzzleLevel(entry);
    }
}

bool ScoreEntry::compareTimes(ScoreEntry* entry) const
{
    if (this->getTime() <= entry->getTime())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ScoreEntry::comparePuzzleLevel(ScoreEntry* entry) const
{
    if (this->getPuzzleLevel() > entry->getPuzzleLevel())
    {
        return true;
    }
    // part 3 functionality needs to be added here
}

}
