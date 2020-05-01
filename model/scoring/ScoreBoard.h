#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "ScoreNode.h"
#include "ScoreEntry.h"

namespace model::scoring {

class ScoreBoard {
public:
    static const int MAX_SCORES = 10;

    ScoreBoard();
    virtual ~ScoreBoard();

    void addScore(int time, const std::string& name, int puzzleLevel);
    const ScoreEntry* getScore(int position, ScoreEntry::SortType sortType) const;
    int getSize() const;
    void resetScores();

private:
    ScoreNode* timeHead;
    ScoreNode* puzzleHead;
    int size;

    void insertScore(ScoreNode* newScore, ScoreEntry::SortType sortType);
    ScoreNode** getHead(ScoreEntry::SortType sortType);
};

}

#endif // SCOREBOARD_H
