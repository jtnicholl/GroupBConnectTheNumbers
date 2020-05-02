#ifndef SCOREBOARDLOADER_H
#define SCOREBOARDLOADER_H

#include <vector>

#include "../model/scoring/ScoreEntry.h"
#include "../model/scoring/ScoreBoard.h"

using namespace model;

namespace fileio {

/**
 * Class for loading high score boards.
 */
class ScoreBoardLoader {
public:
    /**
     * Load a high score board from a file.
     *
     * @param filename name of the file to laod
     *
     * @return the scoreboard
     */
    static scoring::ScoreBoard* loadScoresFromFile(const std::string& filename);

private:
    static const char DELIMETER = ',';
    static scoring::ScoreEntry* loadScoreFromLine(const std::string& line);
};

}

#endif // SCOREBOARDLOADER_H
