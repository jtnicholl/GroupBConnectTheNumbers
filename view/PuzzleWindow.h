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

private:
    const int GRID_STARTING_X = 20;
    const int GRID_STARTING_Y = 60;
    const int GRID_BOX_WIDTH = 30;
    const int GRID_BOX_PADDING = 10;
    const char* NOT_SOLVED_MESSAGE = "Puzzle not yet solved...";
    const char* SOLVED_MESSAGE = "Puzzle solved!";
    const Fl_Color MUTABLE_COLOR = FL_WHITE;
    const Fl_Color IMMUTABLE_COLOR = FL_LIGHT2;

    GameController* gameController;

    Fl_Menu_Button* puzzleSelectMenu;
    Fl_Button* resetButton;
    Fl_Input** inputs;
    Fl_Output* puzzleStatus;
    Fl_Output* timerDisplay;
    Fl_Button* pauseButton;

    void addInputBox(int number);
    void updateInputs();
    void pushInputs();
    void populateMenu();

    static void cbReset(Fl_Widget* widget, void* data);
    static void cbChangePuzzle(Fl_Widget* widget, void* data);
    static void cbSubmit(Fl_Widget* widget, void* data);
    static void cbUpdateTimer(int number, void* data);

    static int parseEntry(const char* entry);
};

}

#endif // PUZZLEWINDOW_H
