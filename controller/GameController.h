#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include <vector>
#include <thread>

#include "../model/TileGame.h"
#include "../model/TileBoard.h"
#include "../model/Timing/Timer.h"
#include "ScoreBoard.h"

using namespace model;

namespace controller {

/**
 * This controller interacts with the model game logic.
 * All access to the model should be made through this unified interface.
 */
class GameController {
public:
    /**
     * Construct a new GameController.
     */
    GameController();
    /**
     * Deconstructor.
     */
    virtual ~GameController();
    /**
     * Gets the time recorded that it has taken for the player on the
     * currently active board.
     *
     * @return the time record for the current board.
     */
    int getCurrentBoardTime() const;
    /**
     * Gets the current level of the game. The higher the level,
     * the higher the difficulty. getCurrentLevel() will never return
     * a number less than 0.
     *
     * @return the current game level
     */
    int getCurrentLevel() const;
    /**
     * Gets the current level of the game. The higher the level,
     * the higher the difficulty.
     *
     * @pre level > 0, level < getAvailableLevels()
     * @post level is changed
     *
     * @param level new level to go to
     */
    void setCurrentLevel(int level);
    /**
     * Gets the number of levels available.
     *
     * @return the number of available levels
     */
    unsigned int getAvailableLevels() const;
    /**
     * Advances the game to the next level. If the level increment
     * is successful, then tryAdvanceLevel() returns true.
     *
     * @post if tryAdvanceLevel(), then getCurrentLevel() == getCurrentLevel()@prev + 1
     *
     * @return true if the level advancement was successful; false otherwise
     */
    bool tryAdvanceLevel();
    /**
     * Attempts to set the tile number at the specified position
     * to the specified value. If the position is immutable, then
     * this method will return false.
     *
     * @pre position >= 0, position < 64, value >= 0 value < 65
     * @post if trySetTileNumber(x, y, value), then getTileValue(x, y) == value
     *
     * @param position the position of the tile to set.
     * @param value the value to set
     *
     * @return true if the set operation is successful; false otherwise
     */
    bool trySetTileValue(int position, int value);
    /**
     * Gets the tile number at the specified position.
     *
     * @pre position >= 0, position < 64
     *
     * @return the value at the specified position
     */
    int getTileValue(int position) const;
    /**
     * Returns if the given tile is immutable.
     *
     * @pre position >= 0, position < 64
     *
     * @param position the position of the tile to check
     *
     * @return true if the tile is immutable, else false
     */
    bool isTileImmutable(int position) const;
    /**
     * Check if the current puzzle has been solved with a valid solution.
     *
     * @return true if the puzzle has been solved, else false
     */
    bool isSolved() const;
    /**
     * Reset the current puzzle by clearing all the player's inputs.
     *
     * @post puzzle is reset
     */
    void resetCurrentPuzzle();
    /**
     * Saves all of the player's puzzles in progress to a file.
     *
     * @post puzzles are saved to a file on disk
     */
    void saveAllPuzzles();
    /**
     * Sets the callback that is called when the current game board's
     * timer is changed.
     *
     * @param callback the function pointer to call when the current game board's timer is changed.
     * @param data the data to pass to the callback when it is called.
     */
    void setTimerPropertyChangedHandler(void (*callback)(int, void*), void* data);
    /**
     * Pauses or unpauses the games timer.
     *
     * @param shouldPause whether or not to pause or unpause the timer.
     */
    void pause(bool shouldPause);
    /**
     * Removes the entries in the scoreboard.
     */
    void resetScoreBoard() const;
    /**
     * Gets the score board data as a string.
     *
     * @return Score board data as a string.
     */
    const std::string getScoreBoardData() const;

private:
    const std::string DEFAULT_PUZZLES_FILENAME = "default_puzzles.csv";
    const std::string SAVED_PUZZLES_FILENAME = "saved_puzzles.csv";
    const std::string LAST_OPEN_PUZZLE_FILENAME = "open_puzzle";
    const std::string SAVED_PUZZLE_TIMES_FILENAME = "puzzle_times.txt";

    int currentLevel;
    std::vector<TileBoard*> boards;
    TileGame* game;
    scoring::ScoreBoard* scoreboard;

    std::vector<timing::Timer*> gameTimers;
    std::thread* currentTimerThread;

    static void cbCurrentGameTimerUpdated(void* data);
    void fireTimerEvent();

    void (*notifyTimerPropertyChanged)(int, void*);
    void* timerPropertyChangedData;

    std::vector<timing::Timer*> createDefaultGameTimers();
    timing::Timer* startCurrentTimer();
    timing::Timer* stopCurrentTimer();
};

}

#endif // GAMECONTROLLER_H
