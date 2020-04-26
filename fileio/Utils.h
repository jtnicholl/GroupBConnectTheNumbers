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
/**
 * Write a single string to a text file. The file is overwritten if it already exists.
 *
 * @param text text to write
 * @param filename name of file to write to
 */
void saveText(const std::string& text, const std::string& filename);
/**
 * Read an entire file as text.
 *
 * @param filename name of the file to read
 *
 * @return text contents of the file
 */
std::string loadText(const std::string& filename);

}

#endif // UTILS_H_INCLUDED
