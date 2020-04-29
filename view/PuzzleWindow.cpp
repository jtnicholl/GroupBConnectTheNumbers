#include "PuzzleWindow.h"

#include <string>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl.H>

#include "../model/TileBoard.h"

namespace view {

PuzzleWindow::PuzzleWindow(int width, int height, const char* title) : Fl_Window(width, height, title) {
    begin();
    this->gameController = new GameController();
    this->gameController->setTimerPropertyChangedHandler(PuzzleWindow::cbUpdateTimer, this);
    this->inputs = new Fl_Input*[model::TileBoard::BOARD_AREA];

    this->puzzleSelectMenu = new Fl_Menu_Button(20, 20, 200, 24, "Select Puzzle");
    this->resetButton = new Fl_Button(380, 20, 80, 24, "Reset");
    this->puzzleStatus = new Fl_Output(70, 440, 170, 24, "Status");
    this->pauseButton = new Fl_Button(380, 440, 80, 24, "Pause");
    this->timerDisplay = new Fl_Output(300, 440, 60, 24, "s");
    this->timerDisplay->value(std::to_string(this->gameController->getCurrentBoardTime()).c_str());
    this->timerDisplay->align(FL_ALIGN_RIGHT);

    for (int i = 0; i < 64; i++) {
        this->addInputBox(i);
    }
    this->updateInputs();
    this->populateMenu();

    this->resetButton->callback(PuzzleWindow::cbReset, this);
    this->pauseButton->callback(PuzzleWindow::cbPause, this);
    end();
}

PuzzleWindow::~PuzzleWindow() {
    delete this->puzzleSelectMenu;
    delete this->resetButton;
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        delete this->inputs[i];
    }
    delete this->inputs;
    delete this->timerDisplay;
    delete this->pauseButton;
}

void PuzzleWindow::cbOnCloseWindow(Fl_Widget*, void* data)
{
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->gameController->saveAllPuzzles();
    window->hide();
}

inline void PuzzleWindow::addInputBox(int number) {
    int x_offset = (number % model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
    int y_offset = (number / model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
    this->inputs[number] = new Fl_Input(GRID_STARTING_X + x_offset, GRID_STARTING_Y + y_offset, GRID_BOX_WIDTH, GRID_BOX_WIDTH);
    this->inputs[number]->callback(cbSubmit, this);
}

void PuzzleWindow::updateInputs() {
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        int tileValue = this->gameController->getTileValue(i);
        bool tileImmutable = this->gameController->isTileImmutable(i);
        std::string boxValue = tileValue == 0 ? "" : std::to_string(tileValue);
        inputs[i]->value(boxValue.c_str());
        inputs[i]->readonly(tileImmutable);
        inputs[i]->color(tileImmutable ? IMMUTABLE_COLOR : MUTABLE_COLOR);
    }
    this->puzzleStatus->value(this->gameController->isSolved() ? SOLVED_MESSAGE : NOT_SOLVED_MESSAGE);
}

void PuzzleWindow::pushInputs() {
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        int tileValue = parseEntry(this->inputs[i]->value());
        this->gameController->trySetTileValue(i, tileValue);
    }
    this->gameController->saveAllPuzzles();
}

inline void PuzzleWindow::populateMenu() {
    for (unsigned int i = 0; i < this->gameController->getAvailableLevels(); i++) {
        std::string label = std::to_string(i + 1);
        this->puzzleSelectMenu->add(label.c_str(), 0, cbChangePuzzle, this);
    }
}

void PuzzleWindow::cbReset(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->gameController->resetCurrentPuzzle();
    window->updateInputs();
    window->timerDisplay->value("0");
}

void PuzzleWindow::cbChangePuzzle(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    const char* label = ((Fl_Menu_*)widget)->text();
    int puzzleSelected = std::atoi(label) - 1;
    window->pushInputs();
    window->gameController->setCurrentLevel(puzzleSelected);
    window->updateInputs();
    window->puzzleStatus->label(label);
}

void PuzzleWindow::cbSubmit(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->pushInputs();
    window->updateInputs();
}

void PuzzleWindow::cbPause(Fl_Widget* widget, void* data)
{
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->makeInputsVisible(window->isPaused);
    window->pauseButton->label(window->isPaused ? "Pause" : "Unpause");
    window->isPaused = !window->isPaused;
    window->gameController->pause(window->isPaused);
}

void PuzzleWindow::makeInputsVisible(bool isVisible)
{
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        Fl_Input* currentInput = this->inputs[i];
        if (isVisible)
        {
            currentInput->show();
        }
        else
        {
            currentInput->hide();
        }
    }
}

void PuzzleWindow::cbUpdateTimer(int number, void* data)
{
    // NOTE (REMOVE THIS BEFORE SUBMISSION): The number parameter is the timer's value
    // in seconds. This can be changed here to another format such as minutes:seconds, etc.
    // Then display it in the timerDisplay->value() method.
    PuzzleWindow* window = (PuzzleWindow*) data;
    std::string numberText = std::to_string(number);

    Fl::lock();
    window->timerDisplay->value(numberText.c_str());
    Fl::awake();
    Fl::unlock();
}

int PuzzleWindow::parseEntry(const char* entry) {
    int output = 0;
    for (int i = 0; entry[i] != '\0'; i++) {
        if (std::isdigit(entry[i])) {
            output *= 10;
            output += entry[i] - '0';
        } else {
            return 0;
        }
    }
    return output > 64 ? 0 : output;
}

}
