#include "Utils.h"

#include <fstream>
#include <sstream>

namespace fileio {

inline bool fileExists(const std::string& filename)
{
	std::ifstream file(filename.c_str());
    return file.good();
}

inline void saveText(const std::string& text, const std::string& filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios::out | std::ios::trunc);
	outfile << text;
	outfile.close();
}

inline std::string loadText(const std::string& filename)
{
    std::ifstream infile;
    std::stringstream output;
    infile.open(filename, std::ios::in);
    while (infile)
    {
		std::string line;
		std::getline(infile, line);
		output << line;
    }
    return output.str();
}

}
