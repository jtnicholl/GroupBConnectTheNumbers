#include "ScoreBoardSaver.h"

#include <fstream>

namespace fileio
{

void ScoreBoardSaver::saveScoreBoardToFile(const ScoreBoard* const scoreboard, const std::string& filename)
{
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);
    outfile << scoreboard->printScores();
    outfile.close();
}

}
