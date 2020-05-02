#ifndef SCOREENTRY_H
#define SCOREENTRY_H

#include <string>

namespace model::scoring {

/**
 * Class representing a high score entry.
 */
class ScoreEntry {
public:
    /**
     * Sorting methods for high scores.
     */
    enum SortType { TIME_ASCENDING, PUZZLE_LEVEL_DESCENDING };

    /**
     * Construct a new ScoreEntry.
     *
     * @param time time taken
     * @param name name of the player
     * @param puzzleLevel level the score was earned on
     */
    ScoreEntry(int time, std::string name, int puzzleLevel);
    /**
     * Destructor.
     */
    virtual ~ScoreEntry();

    /**
     * Get the time.
     *
     * @return the time
     */
    const int getTime() const;
    /**
     * Get the name.
     *
     * @return the name
     */
    const std::string& getName() const;
    /**
     * Get the level.
     *
     * @return the level
     */
    const int getPuzzleLevel() const;
    /**
     * Compare this entry to another for sorting.
     *
     * @pre othert != nullptr
     *
     * @param other entry to compare to
     * @param sortType sorting method to use
     *
     * @return comparison result
     */
    int compare(const ScoreEntry* other, SortType sortType) const;

private:
    int time;
    std::string name;
    int puzzleLevel;

    int compareTimes(const ScoreEntry* other) const;
    int comparePuzzleLevel(const ScoreEntry* other) const;
};

}

#endif // SCOREENTRY_H
