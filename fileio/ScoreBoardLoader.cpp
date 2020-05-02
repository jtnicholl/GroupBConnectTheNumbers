#include "ScoreBoardLoader.h"

#include <fstream>
#include <sstream>

#include "Utils.h"

namespace fileio {

const std::string ScoreBoardLoader::DELIMETER = ",";

scoring::ScoreBoard* ScoreBoardLoader::loadScoresFromFile(const std::string& filename) {
    std::ifstream infile;
    scoring::ScoreBoard* output = new scoring::ScoreBoard();
    infile.open(filename, std::ios::in);
    while (infile) {
        std::string line;
        std::getline(infile, line);
        if (!line.empty()) {
            output->addScore(loadScoreFromLine(line));
        }
    }
    infile.close();
    return output;
}

scoring::ScoreEntry* ScoreBoardLoader::loadScoreFromLine(const std::string& line) {
    std::vector<std::string> lineValues = split(line, DELIMETER);

    std::string name = lineValues[0];
    int time = std::stoi(lineValues[1]);
    int level = std::stoi(lineValues[2]);

    return new scoring::ScoreEntry(time, name, level);
}

}
