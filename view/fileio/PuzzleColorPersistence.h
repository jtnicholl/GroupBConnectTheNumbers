#ifndef PUZZLECOLORPERSISTENCE_H
#define PUZZLECOLORPERSISTENCE_H

#include <string>
#include <vector>

namespace view {
namespace io {

/**
 * This class manages loading and saving view information.
 * The PuzzleColor struct is used to group rgb values for
 * a particular color.
 *
 * @author Thomas Luke Whaley
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
    static void savePuzzleColorsToFile(PuzzleColor& cellColor, PuzzleColor& numberColor, const std::string& filename);

    /**
     * Loads the puzzle colors from the specified file.
     *
     * @post loadPuzzleColorsFromFile(std::string).size() == 2
     *
     * @param filename the file to load the colors from.
     * @return a vector containing the two puzzle colors.
     */
    static std::vector<PuzzleColor> loadPuzzleColorsFromFile(const std::string& filename);
};

}
}

#endif // PUZZLECOLORPERSISTENCE_H
