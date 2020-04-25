#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>

namespace fileio {

/**
 * Returns true if the file with the given name exists.
 *
 * @param filename the filename
 *
 * @return true if the file exists, else false
 */
bool fileExists(const std::string& filename);

}

#endif // UTILS_H_INCLUDED
