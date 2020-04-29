#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include <vector>

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
/**
 * Splits the given input string into components using the specified delimeter.
 *
 * @param input the string to split into components.
 * @param delimeter the delimeter to judge where the splits are made.
 * @return a vector of components that were separated in input by delimeter.
 */
std::vector<std::string> split(const std::string& input, const std::string& delimeter);

}

#endif // UTILS_H_INCLUDED
