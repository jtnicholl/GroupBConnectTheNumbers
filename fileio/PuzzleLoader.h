#ifndef FILEIO_PUZZLELOADER_H
#define FILEIO_PUZZLELOADER_H

#include <vector>
#include <string>

#include "../model/TileBoard.h"
#include "../model/Tile.h"

using namespace model;

namespace fileio {

struct TileEntry { int position; Tile* tile; };

class PuzzleLoader
{
public:
	static std::vector<TileBoard*> loadPuzzlesFromFile(const std::string& filename);

private:
	static TileBoard* loadPuzzleFromLine(const std::string& line);
	static std::vector<TileEntry> parseLine(const std::string& line);
	static TileEntry parseEntry(const std::string& entry);
};

} // namespace fileio

#endif // FILEIO_PUZZLELOADER_H
