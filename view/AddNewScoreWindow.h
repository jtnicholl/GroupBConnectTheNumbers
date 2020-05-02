#ifndef ADDNEWSCOREWINDOW_H
#define ADDNEWSCOREWINDOW_H

#include <FL/Fl_Window.H>

#include "PuzzleWindow.h"

namespace view {

/**
 * Window for entering a name for new high scores.
 */
class AddNewScoreWindow : public Fl_Window {
public:
    /**
        * Construct a new AddNewScoreWindow.
        *
        * @param width width of the window
        * @param height height of the window
        * @param title title of the window
        * @param parent parent of the window
        */
    AddNewScoreWindow(int width, int height, const std::string& title, PuzzleWindow* parent);
    /**
     * Destructor.
     */
    virtual ~AddNewScoreWindow();

private:
    Fl_Input* nameEntry;
    Fl_Button* saveNameButton;
    PuzzleWindow* parent;

    static void cbSaveName(Fl_Widget* widget, void* data);
};

}

#endif // ADDNEWSCOREWINDOW_H
