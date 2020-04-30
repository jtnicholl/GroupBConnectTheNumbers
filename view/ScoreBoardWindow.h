#ifndef SCOREBOARDWINDOW_H
#define SCOREBOARDWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Output.H>

#include "PuzzleWindow.h"

namespace view {

class ScoreBoardWindow : public Fl_Window {
public:
    ScoreBoardWindow(int width, int height, const std::string& title, PuzzleWindow* parent);
    virtual ~ScoreBoardWindow();

private:
    Fl_Multiline_Output* output;
    Fl_Button* reset;
    PuzzleWindow* parent;

    static void cbReset(Fl_Widget* widget, void* data);

    void updateScores();
};

}

#endif // SCOREBOARDWINDOW_H
