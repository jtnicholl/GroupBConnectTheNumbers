#ifndef SCOREBOARDSAVER_H
#define SCOREBOARDSAVER_H

#include "../model/scoring/ScoreBoard.h"
#include "../model/scoring/ScoreEntry.h"

#include <string>

using namespace model::scoring;

namespace fileio {

class ScoreBoardSaver {
public:
    static void saveScoreBoardToFile(const ScoreBoard* scoreboard, const std::string& filename);

private:
    static std::string scoreEntryToLine(const ScoreEntry* entry);
};

}

#endif // SCOREBOARDSAVER_H
