#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

#include "../controller/GameController.h"

using namespace controller;

namespace view {

/**
 * Main window of the application.
 */
class PuzzleWindow : public Fl_Window {
public:
    static const std::string COLOR_SAVE_FILENAME;

    /**
     * This is the callback that is called when this window
     * is hidden/closed. Saves the state of the game, then closes
     * the window like normal.
     *
     * @param widget the widget firing the event.
     * @param data the data to pass to the callback.
     */
    static void cbOnCloseWindow(Fl_Widget* widget, void* data);

    /**
     * Construct a new PuzzleWindow.
     *
     * @param width width of the window
     * @param height height of the window
     * @param title title of the window
     */
    PuzzleWindow(int width, int height, const char* title);
    /**
     * Destructor.
     */
    virtual ~PuzzleWindow();
    /**
     * Sets the input tile's color.
     *
     * @param color the color for the input tiles.
     */
    void setInputTileColor(Fl_Color color);
    /**
     * Sets the input number color.
     *
     * @param color the input number color.
     */
    void setInputNumberColor(Fl_Color color);
    /**
     * Gets the input tile's color.
     *
     * @return the input tile's color.
     */
    Fl_Color getInputTileColor() const;
    /**
     * Gets the input number color.
     *
     * @return the input number color.
     */
    Fl_Color getInputNumberColor() const;
    /**
     * Gets the game controller.
     *
     * @return the game controller.
     */
    const GameController* const getGameController() const;

private:
    const int GRID_STARTING_X = 85;
    const int GRID_STARTING_Y = 95;
    const int GRID_BOX_WIDTH = 30;
    const int GRID_BOX_PADDING = 10;

    const char* NOT_SOLVED_MESSAGE = "Puzzle not yet solved...";
    const char* SOLVED_MESSAGE = "Puzzle solved!";

    const Fl_Color DEFAULT_COLOR = FL_WHITE;

    GameController* gameController;

    Fl_Color currentNumberColor;
    Fl_Color currentCellColor;

    Fl_Menu_Button* puzzleSelectMenu;
    Fl_Button* resetButton;
    Fl_Input** inputs;
    Fl_Output* puzzleStatus;
    Fl_Output* timerDisplay;
    Fl_Button* settingsButton;
    Fl_Button* pauseButton;
    Fl_Button* scoreboardButton;
    bool isPaused;

    void addInputBox(int number);
    void updateInputs();
    void pushInputs();
    void populateMenu();
    void makeInputsVisible(bool isVisible);
    void completeLevel();
    void setInitialColors();

    static void cbReset(Fl_Widget* widget, void* data);
    static void cbChangePuzzle(Fl_Widget* widget, void* data);
    static void cbSubmit(Fl_Widget* widget, void* data);
    static void cbPause(Fl_Widget* widget, void* data);
    static void cbUpdateTimer(int number, void* data);
    static void cbSettings(Fl_Widget* widget, void* data);
    static void cbScoreBoard(Fl_Widget* widget, void* data);

    static int parseEntry(const char* entry);
};

}

#endif // PUZZLEWINDOW_H
