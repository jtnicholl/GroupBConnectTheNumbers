#ifndef FILEIO_PUZZLELOADER_H
#define FILEIO_PUZZLELOADER_H

#include <vector>
#include <string>

#include "../model/TileBoard.h"
#include "../model/Tile.h"
#include "../model/timing/Timer.h"

using namespace model;

namespace fileio {

class PuzzleLoader {
public:
    /**
     * Load puzzles from the specified file.
     *
     * @param filename filename to load from
     *
     * @return the tile boards in a vector
     */
    static std::vector<TileBoard*> loadPuzzlesFromFile(const std::string& filename);

    /**
     * Load puzzle times from the specified file.
     *
     * @param filename filename to load from.
     * @return the Timer objects in a vector.
     */
    static std::vector<timing::Timer*> loadPuzzleTimesFromFile(const std::string& filename);

private:
    struct TileEntry {
        int position;
        Tile* tile;
    };

    static TileBoard* loadPuzzleFromLine(const std::string& line);
    static std::vector<TileEntry> parseLine(const std::string& line);
    static TileEntry parseEntry(const std::string& entry);
};

} // namespace fileio

#endif // FILEIO_PUZZLELOADER_H
