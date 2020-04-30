#include "ScoreBoard.h"

namespace model::scoring
{

ScoreBoard::ScoreBoard()
{
    this->scores = new ScoreEntry*[MAX_SCORES]();
    this->sortType = ScoreEntry::TIME_ASCENDING;
    addScore(10, "TestName1", 1);
    addScore(4, "TestName2", 1);
    addScore(20, "TestName3", 2);
    addScore(15, "TestName4", 3);
    addScore(15, "TestName5", 2);
    addScore(20, "TestName3", 2);
    addScore(20, "TestName3", 2);
    addScore(20, "TestName3", 2);
    addScore(20, "TestName3", 2);
    addScore(20, "TestName3", 2);
    addScore(1, "TestName3", 2);
}

ScoreBoard::ScoreBoard(ScoreEntry::SortType sortType)
{
    this->scores = new ScoreEntry*[MAX_SCORES];
    this->sortType = sortType;
}

ScoreBoard::~ScoreBoard()
{
    delete[] this->scores;
}

void ScoreBoard::addScore(int time, const std::string& name, int puzzleLevel)
{
    ScoreEntry* newScore = new ScoreEntry(time, name, puzzleLevel);
    if (!canAddNewScore(newScore))
    {
        delete newScore;
    }
    else
    {
        insertScore(newScore);
    }
}

bool ScoreBoard::canAddNewScore(ScoreEntry* newScore) const
{
    bool canAdd = false;
    for (unsigned int i = 0; i < MAX_SCORES && !canAdd; i++)
    {
        if (this->scores[i] == nullptr)
        {
            canAdd = true;
        }
        else if (!this->scores[i]->compare(newScore, this->sortType))
        {
            canAdd = true;
        }
    }
    return canAdd;
}

void ScoreBoard::insertScore(ScoreEntry* newScore)
{
    bool inserted = false;
    for (unsigned int i = 0; i < MAX_SCORES && !inserted; i++)
    {
        if (this->scores[i] == nullptr)
        {
            this->scores[i] = newScore;
            inserted = true;
        }
        else if (!this->scores[i]->compare(newScore, this->sortType))
        {
            ScoreEntry* temp = this->scores[i];
            this->scores[i] = newScore;
            placeAndPushBack(temp, i + 1);
            inserted = true;
        }
    }
}

void ScoreBoard::placeAndPushBack(ScoreEntry* entry, int index)
{
    ScoreEntry* temp1 = nullptr;
    ScoreEntry* temp2 = entry;
    for (int i = index; i < MAX_SCORES && temp2; i++)
    {
        temp1 = this->scores[i];
        this->scores[i] = temp2;
        temp2 = temp1;
    }
}

const std::string ScoreBoard::printScores() const
{
    std::string output = "";
    for (unsigned int i = 0; i < MAX_SCORES; i++)
    {
        if (this->scores[i] != nullptr)
        {
            output += buildScoreString(this->scores[i]);
        }
    }
    return output;
}

const std::string ScoreBoard::buildScoreString(ScoreEntry* scoreEntry) const
{
    std::string curName = scoreEntry->getName();
    std::string curTime = std::to_string(scoreEntry->getTime());
    std::string curPuzzle = std::to_string(scoreEntry->getPuzzleLevel());
    return curName + " " + curTime + " " + curPuzzle + "\n";
}

void ScoreBoard::resetScores()
{
    delete[] this->scores;
    this->scores = new ScoreEntry*[MAX_SCORES]();
}

}
