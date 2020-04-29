#include "Utils.h"

#include <fstream>
#include <sstream>

namespace fileio {

inline bool fileExists(const std::string& filename) {
    std::ifstream file(filename.c_str());
    return file.good();
}

inline void saveText(const std::string& text, const std::string& filename) {
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);
    outfile << text;
    outfile.close();
}

inline std::string loadText(const std::string& filename) {
    std::ifstream infile;
    std::stringstream output;
    infile.open(filename, std::ios::in);
    while (infile) {
        std::string line;
        std::getline(infile, line);
        output << line;
    }
    return output.str();
}

std::vector<std::string> split(const std::string& input, const std::string& delimeter)
{
    std::vector<std::string> components;
    std::string phrase(input);
    std::string::size_type position = 0;
    std::string token;
    while ((position = phrase.find(delimeter)) != std::string::npos)
    {
        token = phrase.substr(0, position);
        components.push_back(token);
        phrase.erase(0, position + delimeter.length());
    }
    components.push_back(phrase);
    return components;
}

}
