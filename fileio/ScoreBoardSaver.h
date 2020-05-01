#ifndef SCOREBOARDSAVER_H
#define SCOREBOARDSAVER_H

#include "../model/scoring/ScoreBoard.h"

#include <string>

using namespace model::scoring;

namespace fileio
{

class ScoreBoardSaver
{
    public:
        static void saveScoreBoardToFile(const ScoreBoard* const scoreboard, const std::string& filename);
};

}

#endif // SCOREBOARDSAVER_H
