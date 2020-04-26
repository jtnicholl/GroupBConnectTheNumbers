#ifndef FILEIO_PUZZLESAVER_H
#define FILEIO_PUZZLESAVER_H

#include <string>
#include <vector>

#include "../model/TileBoard.h"

using namespace model;

namespace fileio {

class PuzzleSaver {
public:
    /**
     * Save puzzle boards to a file.
     *
     * @param boards puzzle boards to save, stored in a vector
     * @param filename filename to save to
     */
    static void savePuzzlesToFile(const std::vector<TileBoard*>& boards, const std::string& filename);

private:
    static std::string puzzleToLine(TileBoard* board);
};

} // namespace fileio

#endif // FILEIO_PUZZLESAVER_H
