#include "model/scoring/ScoreNode.h"

namespace model {
namespace scoring {

ScoreNode::ScoreNode(ScoreEntry* entry) {
    this->entry = entry;
    this->nextTime = nullptr;
    this->nextPuzzle = nullptr;
}

ScoreNode::~ScoreNode() {
    delete this->entry;
}

const ScoreEntry* ScoreNode::getEntry() const {
    return this->entry;
}

int ScoreNode::compare(const ScoreNode* other, ScoreEntry::SortType sortType) const {
    return this->entry->compare(other->entry, sortType);
}

ScoreNode* ScoreNode::getNext(ScoreEntry::SortType sortType) const {
    if (sortType == ScoreEntry::SortType::TIME_ASCENDING) {
        return this->nextTime;
    } else if (sortType == ScoreEntry::SortType::PUZZLE_LEVEL_DESCENDING) {
        return this->nextPuzzle;
    }
}

void ScoreNode::insertNext(ScoreNode* node, ScoreEntry::SortType sortType) {
    if (sortType == ScoreEntry::SortType::TIME_ASCENDING) {
        node->nextTime = this->nextTime;
        this->nextTime = node;
    } else if (sortType == ScoreEntry::SortType::PUZZLE_LEVEL_DESCENDING) {
        node->nextPuzzle = this->nextPuzzle;
        this->nextPuzzle = node;
    }
}

void ScoreNode::setNext(ScoreNode* node, ScoreEntry::SortType sortType) {
	if (sortType == ScoreEntry::SortType::TIME_ASCENDING) {
		this->nextTime = node;
	} else if (sortType == ScoreEntry::SortType::PUZZLE_LEVEL_DESCENDING) {
        this->nextPuzzle = node;
    }
}

} // namespace scoring
} // namespace model
