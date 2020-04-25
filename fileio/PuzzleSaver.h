#ifndef FILEIO_PUZZLESAVER_H
#define FILEIO_PUZZLESAVER_H

#include <string>
#include <vector>

#include "../model/TileBoard.h"

using namespace model;

namespace fileio {

class PuzzleSaver
{
public:
	static void savePuzzlesToFile(const std::vector<TileBoard*>& boards, const std::string& filename);

private:
	static std::string puzzleToLine(TileBoard* board);
};

} // namespace fileio

#endif // FILEIO_PUZZLESAVER_H
