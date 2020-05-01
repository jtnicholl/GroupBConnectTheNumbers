#include "ScoreBoardWindow.h"

namespace view {

ScoreBoardWindow::ScoreBoardWindow(int width, int height, const std::string& title, PuzzleWindow* parent) : Fl_Window(width, height, title.c_str()) {
    begin();

    this->parent = parent;

    this->sortMenu = new Fl_Menu_Button(25, 20, 250, 25, "Sort");
    this->output = new Fl_Multiline_Output(25, 65, 250, 185);
    this->reset = new Fl_Button(110, 260, 80, 30, "Reset");

    this->sortMenu->add("By time", 0, cbSortTime, this);
    this->sortMenu->add("By level", 0, cbSortLevel, this);
    this->output->textfont(FL_COURIER);
    this->reset->callback(cbReset, this);

    updateScores(ScoreEntry::SortType::TIME_ASCENDING);

    end();
}

ScoreBoardWindow::~ScoreBoardWindow() {
    delete this->output;
}

void ScoreBoardWindow::cbReset(Fl_Widget* widget, void* data) {
    ScoreBoardWindow* window = (ScoreBoardWindow*)data;
    window->parent->getGameController()->resetScoreBoard();
    window->updateScores(ScoreEntry::SortType::TIME_ASCENDING);
}

void ScoreBoardWindow::cbSortTime(Fl_Widget* widget, void* data) {
    ScoreBoardWindow* window = (ScoreBoardWindow*)data;
    window->updateScores(ScoreEntry::SortType::TIME_ASCENDING);
}

void ScoreBoardWindow::cbSortLevel(Fl_Widget* widget, void* data) {
    ScoreBoardWindow* window = (ScoreBoardWindow*)data;
    window->updateScores(ScoreEntry::SortType::PUZZLE_LEVEL_DESCENDING);
}

void ScoreBoardWindow::updateScores(ScoreEntry::SortType sortType) {
	std::string newText = this->parent->getGameController()->getScoreBoardText(sortType);
	this->output->value(newText.c_str());
}

}
