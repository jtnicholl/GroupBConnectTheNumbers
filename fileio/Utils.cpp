#include "Utils.h"

#include <fstream>

namespace fileio {

inline bool fileExists(const std::string& filename)
{
	std::ifstream file(filename.c_str());
    return file.good();
}

}
