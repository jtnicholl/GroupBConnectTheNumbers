#ifndef SCOREENTRY_H
#define SCOREENTRY_H

#include <string>

namespace model::scoring
{

class ScoreEntry
{
    public:
        enum SortType { TIME_ASCENDING, PUZZLE_LEVEL_DESCENDING };

        ScoreEntry(int time, std::string name, int puzzleLevel);
        virtual ~ScoreEntry();

        const int getTime() const;
        const std::string& getName() const;
        const int getPuzzleLevel() const;
        bool compare(ScoreEntry* entry, SortType type) const;
        bool compareTimes(ScoreEntry* entry) const;
        bool comparePuzzleLevel(ScoreEntry* entry) const;

    private:
        int time;
        std::string name;
        int puzzleLevel;
};

}

#endif // SCOREENTRY_H
