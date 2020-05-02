#ifndef PUZZLECOLORPERSISTENCE_H
#define PUZZLECOLORPERSISTENCE_H

#include <string>
#include <vector>

namespace fileio {

/**
 * This class manages loading and saving color settings.
 */
class PuzzleColorPersistence {
public:
    /**
     * This struct groups color information to be
     * loaded/saved.
     */
    struct PuzzleColor {
        int8_t red;
        int8_t green;
        int8_t blue;
    };

    /**
     * Saves the two colors in the specified file in csv format.
     *
     * @param cellColor the game's cell color.
     * @param numberColor the game's number color.
     * @param filename the file to save the information to.
     */
    static void savePuzzleColorsToFile(const PuzzleColor& cellColor, const PuzzleColor& numberColor, const std::string& filename);

    /**
     * Loads the puzzle colors from the specified file.
     *
     * @param filename the file to load the colors from
     *
     * @return a vector containing the two colors
     */
    static std::vector<PuzzleColor> loadPuzzleColorsFromFile(const std::string& filename);
};

}

#endif // PUZZLECOLORPERSISTENCE_H
