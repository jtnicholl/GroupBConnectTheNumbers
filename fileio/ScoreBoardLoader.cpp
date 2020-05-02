#include "ScoreBoardLoader.h"

#include <fstream>
#include <sstream>

namespace fileio {

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
    std::vector<std::string> lineValues;
    std::size_t curPos = line.find(DELIMETER), prevPos = 0;
    while (curPos != std::string::npos) {
        lineValues.push_back(line.substr(prevPos, curPos - prevPos));
        prevPos = curPos + 1;
        curPos = line.find(DELIMETER, prevPos);
    }
    lineValues.push_back(line.substr(prevPos, curPos - prevPos));

    int puzzleLevel = std::stoi(lineValues.back());
    lineValues.pop_back();
    int time = std::stoi(lineValues.back());
    lineValues.pop_back();
    std::stringstream nameStream;
    for (std::vector<std::string>::iterator i = lineValues.begin(); i != lineValues.end(); i++) {
        nameStream << *i;
    }
    std::string name = nameStream.str();
    return new scoring::ScoreEntry(time, name, puzzleLevel);
}

}
