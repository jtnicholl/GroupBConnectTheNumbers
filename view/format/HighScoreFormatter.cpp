#include "HighScoreFormatter.h"

#include <sstream>
#include <iostream>

namespace view {
namespace format {

std::string HighScoreFormatter::formatHighScores(const ScoreBoard* scoreBoard, ScoreEntry::SortType sortType) {
	std::stringstream output;
	for (int i = 0; i < DISPLAYED_SCORES && i < scoreBoard->getSize(); i++) {
		output << formatEntry(scoreBoard->getScore(i, sortType)) << std::endl;
	}
	return output.str();
}

std::string HighScoreFormatter::formatEntry(const ScoreEntry* entry) {
	std::stringstream output;
	output << entry->getName();
	for (int i = output.str().length(); i < FIRST_COLUMN_WIDTH; i++) {
		output << " ";
	}
	output << entry->getTime();
	for (int i = output.str().length(); i < FIRST_COLUMN_WIDTH + SECOND_COLUMN_WIDTH; i++) {
		output << " ";
	}
	output << entry->getPuzzleLevel();
	return output.str();
}

} // namespace format
} // namespace view
