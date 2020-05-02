#ifndef SCOREBOARDWINDOW_H
#define SCOREBOARDWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Multiline_Output.H>

#include "PuzzleWindow.h"
#include "../model/scoring/ScoreEntry.h"

using namespace model::scoring;

namespace view {

/**
 * Window for displaying high scores.
 */
class ScoreBoardWindow : public Fl_Window {
public:
    /**
     * Construct a new high score window.
     *
     * @param width width of the window
     * @param height height of the window
     * @param title title of the window
     * @param parent parent of the window
     */
    ScoreBoardWindow(int width, int height, const std::string& title, PuzzleWindow* parent);
    /**
     * Destructor.
     */
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
