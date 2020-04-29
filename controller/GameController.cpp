#include "GameController.h"

#include "../fileio/PuzzleLoader.h"
#include "../fileio/PuzzleSaver.h"
#include "../fileio/Utils.cpp"
#include "../model/TileBoard.h"

using namespace fileio;

namespace controller {

GameController::GameController() {
    this->currentLevel = fileExists(LAST_OPEN_PUZZLE_FILENAME) ? std::stoi(loadText(LAST_OPEN_PUZZLE_FILENAME)) : 0;
    std::string filename = fileExists(SAVED_PUZZLES_FILENAME) ? SAVED_PUZZLES_FILENAME : DEFAULT_PUZZLES_FILENAME;
    this->boards = PuzzleLoader::loadPuzzlesFromFile(filename);
    this->game = new TileGame(this->boards[this->currentLevel]);
    this->gameTimers = fileExists(SAVED_PUZZLE_TIMES_FILENAME) ? PuzzleLoader::loadPuzzleTimesFromFile(SAVED_PUZZLE_TIMES_FILENAME) : this->createDefaultGameTimers();
    this->currentTimerThread = nullptr;
}

GameController::~GameController() {
    delete this->game;
    for (unsigned int i = 0; i < this->boards.size(); i++) {
        delete this->boards[i];
    }
    this->stopCurrentTimer();
    for (std::vector<timing::Timer*>::iterator i = this->gameTimers.begin(); i != this->gameTimers.end(); i++)
    {
        delete *i;
    }
}

int GameController::getCurrentBoardTime() const
{
    timing::Timer* currentTimer = this->gameTimers[this->currentLevel];
    return currentTimer->getSecondCount();
}

int GameController::getCurrentLevel() const {
    return this->currentLevel;
}

void GameController::setCurrentLevel(int level) {
    this->stopCurrentTimer();
    this->currentLevel = level;
    this->game->setBoard(this->boards[level]);
    saveText(std::to_string(level), LAST_OPEN_PUZZLE_FILENAME);
    this->fireTimerEvent();
}

unsigned int GameController::getAvailableLevels() const {
    return this->boards.size();
}

bool GameController::tryAdvanceLevel() {
    if (this->game->isSolved() && this->currentLevel < this->boards.size() - 1) {
        this->setCurrentLevel(this->currentLevel + 1);
        return true;
    } else {
        return false;
    }
}

bool GameController::trySetTileValue(int position, int value) {
    bool result = this->game->trySetTileValue(position, value);
    if (this->currentTimerThread == nullptr && result)
    {
        this->startCurrentTimer();
    }

    return result;
}

int GameController::getTileValue(int position) const {
    return this->game->getTileValue(position);
}

bool GameController::isTileImmutable(int position) const {
    return this->game->isTileImmutable(position);
}

bool GameController::isSolved() const {
    return this->game->isSolved();
}

void GameController::resetCurrentPuzzle() {
    for (int i = 0; i < TileBoard::BOARD_AREA; i++) {
        this->game->trySetTileValue(i, 0);
    }
    timing::Timer* currentTimer = this->stopCurrentTimer();
    currentTimer->reset();
}

void GameController::saveAllPuzzles() {
    PuzzleSaver::savePuzzlesToFile(this->boards, SAVED_PUZZLES_FILENAME);
    PuzzleSaver::savePuzzleTimesToFile(this->gameTimers, SAVED_PUZZLE_TIMES_FILENAME);
}

std::vector<timing::Timer*> GameController::createDefaultGameTimers()
{
    std::vector<timing::Timer*> timers;
    for (std::vector<TileBoard*>::size_type i = 0; i < this->boards.size(); i++)
    {
        timers.push_back(new timing::Timer());
    }
    return timers;
}

timing::Timer* GameController::startCurrentTimer()
{
    timing::Timer* currentTimer = this->gameTimers[this->currentLevel];
    currentTimer->addSecondsIncreasedListener(GameController::cbCurrentGameTimerUpdated, this);
    this->currentTimerThread = new std::thread(&timing::Timer::run, currentTimer);
    return currentTimer;
}

timing::Timer* GameController::stopCurrentTimer()
{
    timing::Timer* currentTimer = this->gameTimers[this->currentLevel];
    currentTimer->stop();
    if (this->currentTimerThread != nullptr)
    {
        this->currentTimerThread->join();

        delete this->currentTimerThread;
        this->currentTimerThread = nullptr;
    }
    return currentTimer;
}

void GameController::cbCurrentGameTimerUpdated(void* data)
{
    GameController* controller = (GameController*) data;
    controller->fireTimerEvent();
}

void GameController::fireTimerEvent()
{
    timing::Timer* currentTimer = this->gameTimers[this->currentLevel];
    int seconds = currentTimer->getSecondCount();
    if (this->notifyTimerPropertyChanged != nullptr)
    {
        this->notifyTimerPropertyChanged(seconds, this->timerPropertyChangedData);
    }
}

void GameController::setTimerPropertyChangedHandler(void (*callback)(int, void*), void* data)
{
    this->notifyTimerPropertyChanged = callback;
    this->timerPropertyChangedData = data;
}

void GameController::pause(bool shouldPause)
{
    if (shouldPause)
    {
        this->stopCurrentTimer();
    }
    else
    {
        this->startCurrentTimer();
    }
}

}
