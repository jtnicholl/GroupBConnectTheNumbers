#include "ScoreBoardWindow.h"

namespace view
{

ScoreBoardWindow::ScoreBoardWindow(int width, int height, const std::string& title, PuzzleWindow* parent) : Fl_Window(width, height, title.c_str())
{
    begin();

    this->parent = parent;

    this->output = new Fl_Multiline_Output(25, 25, 250, 225, nullptr);
    this->reset = new Fl_Button(110, 260, 80, 30, "Reset");

    this->reset->callback(cbReset, this);

    updateScores();

    end();
}

ScoreBoardWindow::~ScoreBoardWindow()
{
    delete this->output;
}

void ScoreBoardWindow::cbReset(Fl_Widget* widget, void* data)
{
    ScoreBoardWindow* window = (ScoreBoardWindow*)data;
    window->parent->getGameController()->resetScoreBoard();
    window->updateScores();
}

void ScoreBoardWindow::updateScores()
{
    this->output->value(this->parent->getGameController()->getScoreBoardData().c_str());
}

}
