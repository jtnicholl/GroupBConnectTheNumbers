#ifndef ADDNEWSCOREWINDOW_H
#define ADDNEWSCOREWINDOW_H

#include <FL/Fl_Window.H>

#include "PuzzleWindow.h"

namespace view {

class AddNewScoreWindow : public Fl_Window {
public:
    AddNewScoreWindow(int width, int height, const std::string& title, PuzzleWindow* parent);
    virtual ~AddNewScoreWindow();

private:
    Fl_Input* nameEntry;
    Fl_Button* saveNameButton;
    PuzzleWindow* parent;

    static void cbSaveName(Fl_Widget* widget, void* data);
};

}

#endif // ADDNEWSCOREWINDOW_H
