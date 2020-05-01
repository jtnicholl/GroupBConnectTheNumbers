#include "ScoreBoard.h"

#include <sstream>

namespace model::scoring {

ScoreBoard::ScoreBoard() {
    this->timeHead = nullptr;
    this->puzzleHead = nullptr;
    this->size = 0;
}

ScoreBoard::~ScoreBoard() {
    resetScores();
}

void ScoreBoard::addScore(int time, const std::string& name, int puzzleLevel) {
    ScoreEntry* entry = new ScoreEntry(time, name, puzzleLevel);
    this->addScore(entry);
}

void ScoreBoard::addScore(ScoreEntry* entry) {
	ScoreNode* node = new ScoreNode(entry);
    insertScore(node, ScoreEntry::SortType::TIME_ASCENDING);
    insertScore(node, ScoreEntry::SortType::PUZZLE_LEVEL_DESCENDING);
    this->size++;
}

const ScoreEntry* ScoreBoard::getScore(int position, ScoreEntry::SortType sortType) const {
    ScoreNode* output;
    if (sortType == ScoreEntry::SortType::TIME_ASCENDING) {
        output = this->timeHead;
    } else if (sortType == ScoreEntry::SortType::PUZZLE_LEVEL_DESCENDING) {
        output = this->puzzleHead;
    }
    for (int i = 0; i < position; i++) {
        output = output->getNext(sortType);
    }
    return output->getEntry();
}

int ScoreBoard::getSize() const {
    return this->size;
}

void ScoreBoard::insertScore(ScoreNode* newScore, ScoreEntry::SortType sortType) {
    ScoreNode** head = this->getHead(sortType);
    if (*(head) == nullptr) {
        *(head) = newScore;
    } else if ((*(head))->compare(newScore, sortType) > 0) {
        newScore->setNext(*(head), sortType);
        *(head) = newScore;
    } else {
        ScoreNode* currentNode = *(head);
        ScoreNode* nextNode = currentNode->getNext(sortType);
        while (nextNode != nullptr && nextNode->compare(newScore, sortType) < 0) {
            currentNode = nextNode;
            nextNode = currentNode->getNext(sortType);
        }
        currentNode->insertNext(newScore, sortType);
    }
}

void ScoreBoard::resetScores() {
    ScoreNode* currentNode = this->timeHead;
    while (currentNode != nullptr) {
        ScoreNode* toDelete = currentNode;
        currentNode = currentNode->getNext(ScoreEntry::SortType::TIME_ASCENDING);
        delete toDelete;
    }
    this->size = 0;
}

ScoreNode** ScoreBoard::getHead(ScoreEntry::SortType sortType) {
    if (sortType == ScoreEntry::SortType::TIME_ASCENDING) {
        return &(this->timeHead);
    } else if (sortType == ScoreEntry::SortType::PUZZLE_LEVEL_DESCENDING) {
        return &(this->puzzleHead);
    }
}

}
