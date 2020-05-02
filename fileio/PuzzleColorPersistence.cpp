#include "PuzzleColorPersistence.h"

#include <fstream>

#include "Utils.h"

namespace fileio {

void PuzzleColorPersistence::savePuzzleColorsToFile(const PuzzleColor& cellColor, const PuzzleColor& numberColor, const std::string& filename) {
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);
    if (outfile.is_open()) {
        outfile << std::to_string(cellColor.red) << "," << std::to_string(cellColor.green) << "," << std::to_string(cellColor.blue) << std::endl;
        outfile << std::to_string(numberColor.red) << "," << std::to_string(numberColor.green) << "," << std::to_string(numberColor.blue) << std::endl;
        outfile.close();
    }
}

std::vector<PuzzleColorPersistence::PuzzleColor> PuzzleColorPersistence::loadPuzzleColorsFromFile(const std::string& filename) {
    std::vector<PuzzleColor> times;
    std::ifstream infile;
    std::string::size_type stringSize;
    infile.open(filename, std::ios::in);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::vector<std::string> components = fileio::split(line, ",");
            PuzzleColor color;
            color.red = std::stoi(components[0], &stringSize);
            color.green = std::stoi(components[1], &stringSize);
            color.blue = std::stoi(components[2], &stringSize);
            times.push_back(color);
        }
    }
    return times;
}

}
