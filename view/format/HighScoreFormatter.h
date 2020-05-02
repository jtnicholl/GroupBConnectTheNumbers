#ifndef VIEW_FORMAT_HIGHSCOREFORMATTER_H
#define VIEW_FORMAT_HIGHSCOREFORMATTER_H

#include <string>

#include "../../model/scoring/ScoreBoard.h"
#include "../../model/scoring/ScoreEntry.h"

using namespace model::scoring;

namespace view {
namespace format {

class HighScoreFormatter {
public:
    static std::string formatHighScores(const ScoreBoard* scoreBoard, ScoreEntry::SortType sortType);

private:
    static const int DISPLAYED_SCORES = 10;
    static const int FIRST_COLUMN_WIDTH = 23;
    static const int SECOND_COLUMN_WIDTH = 5;

    static std::string formatEntry(const ScoreEntry* entry);
};

} // namespace format
} // namespace view

#endif // VIEW_FORMAT_HIGHSCOREFORMATTER_H
