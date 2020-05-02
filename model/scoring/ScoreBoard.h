#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "ScoreNode.h"
#include "ScoreEntry.h"

namespace model::scoring {

/**
 * Class representing a high score board.
 */
class ScoreBoard {
public:
    /**
     * Construct a new ScoreBoard.
     */
    ScoreBoard();
    /**
     * Destructor.
     */
    virtual ~ScoreBoard();

    /**
     * Add a new high score to the scoreboard.
     *
     * @post score is added
     *
     * @param time time to complete
     * @param name name of the player
     * @param puzzleLevel level the score was earned on
     */
    void addScore(int time, const std::string& name, int puzzleLevel);
    /**
     * Add a new high score to the scoreboard.
     *
     * @pre entry != null
     * @post score is added
     *
     * @param entry high score entry to add
     */
    void addScore(ScoreEntry* entry);
    /**
     * Get a score from the scoreboard.
     *
     * @param position position on the list to get
     * @param sortType sorting method to use
     *
     * @return the score entry
     */
    const ScoreEntry* getScore(int position, ScoreEntry::SortType sortType) const;
    /**
     * Get the number of entries on the scoreboard.
     *
     * @return the size of the board
     */
    int getSize() const;
    /**
     * Delete all entries and reset the high score board.
     *
     * @post scores are cleared
     */
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
