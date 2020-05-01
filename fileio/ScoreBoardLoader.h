#ifndef SCOREBOARDLOADER_H
#define SCOREBOARDLOADER_H

#include "../model/scoring/ScoreEntry.h"
#include "../model/scoring/ScoreBoard.h"

#include <vector>

using namespace model;

namespace fileio
{

class ScoreBoardLoader
{
    public:
        static scoring::ScoreBoard* loadScoresFromFile(const std::string& filename);

    private:
        static const char DELIMETER = ' ';
        static scoring::ScoreEntry* loadScoreFromLine(const std::string& line);
};

}

#endif // SCOREBOARDLOADER_H
