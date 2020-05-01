#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "ScoreEntry.h"

namespace model::scoring {

class ScoreBoard {
public:
    static const int MAX_SCORES = 10;

    ScoreBoard();
    ScoreBoard(ScoreEntry::SortType sortType);
    virtual ~ScoreBoard();

    void addScore(int time, const std::string& name, int puzzleLevel);
    const ScoreEntry* getScore(int position) const;
    const std::string printScores() const;
    void setSortType(ScoreEntry::SortType sortType);
    void resetScores();

private:
    ScoreEntry** scores;
    ScoreEntry::SortType sortType;

    const std::string buildScoreString(ScoreEntry* scoreEntry) const;
    bool canAddNewScore(ScoreEntry* newScore) const;
    void insertScore(ScoreEntry* newScore);
    void placeAndPushBack(ScoreEntry* entry, int index);
};

}

#endif // SCOREBOARD_H
