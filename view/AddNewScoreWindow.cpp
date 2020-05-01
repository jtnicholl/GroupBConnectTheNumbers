#include "AddNewScoreWindow.h"

namespace view {

AddNewScoreWindow::AddNewScoreWindow(int width, int height, const std::string& title, PuzzleWindow* parent) : Fl_Window(width, height, title.c_str()) {
    begin();

    this->nameEntry = new Fl_Input(100, 30, 130, 30, "Enter Name:");
    this->saveNameButton = new Fl_Button(100, 68, 50, 25, "OK");
    this->saveNameButton->callback(cbSaveName, this);
    this->parent = parent;

    end();
}

AddNewScoreWindow::~AddNewScoreWindow() {
    delete this->nameEntry;
    delete this->saveNameButton;
}

void AddNewScoreWindow::cbSaveName(Fl_Widget* widget, void* data) {
    AddNewScoreWindow* window = (AddNewScoreWindow*)data;
    window->parent->getGameController()->addScoreBoardEntry(window->nameEntry->value());
    window->hide();
    window->parent->completeLevel();
}

}
