#ifndef SCOREBOARDWINDOW_H
#define SCOREBOARDWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Multiline_Output.H>

#include "PuzzleWindow.h"
#include "../model/scoring/ScoreEntry.h"

using namespace model::scoring;

namespace view {

class ScoreBoardWindow : public Fl_Window {
public:
    ScoreBoardWindow(int width, int height, const std::string& title, PuzzleWindow* parent);
    virtual ~ScoreBoardWindow();

private:
	Fl_Menu_Button* sortMenu;
    Fl_Multiline_Output* output;
    Fl_Button* reset;
    PuzzleWindow* parent;

    static void cbReset(Fl_Widget* widget, void* data);
    static void cbSortTime(Fl_Widget* widget, void* data);
    static void cbSortLevel(Fl_Widget* widget, void* data);

    void updateScores(ScoreEntry::SortType sortType);
};

}

#endif // SCOREBOARDWINDOW_H
