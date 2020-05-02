#ifndef SCOREBOARDSAVER_H
#define SCOREBOARDSAVER_H

#include "../model/scoring/ScoreBoard.h"
#include "../model/scoring/ScoreEntry.h"

#include <string>

using namespace model::scoring;

namespace fileio {

/**
 * Class for saving high score boards to files.
 */
class ScoreBoardSaver {
public:
    /**
     * Saves a scoreboard to a file. The file is overwritten if it already exists.
     *
     * @pre scoreboard != null
     * @post scoreboard is saved to disk
     *
     * @param scoreboard scoreboard to save
     * @param filename name of the file to save to
     */
    static void saveScoreBoardToFile(const ScoreBoard* scoreboard, const std::string& filename);

private:
    static std::string scoreEntryToLine(const ScoreEntry* entry);
};

}

#endif // SCOREBOARDSAVER_H
