#include <string>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl.H>

#include <iostream>

#include "../model/TileBoard.h"
#include "../fileio/Utils.h"
#include "fileio/PuzzleColorPersistence.h"
#include "PuzzleWindow.h"
#include "SettingsWindow.h"
#include "ScoreBoardWindow.h"
#include "AddNewScoreWindow.h"

namespace view {

const std::string PuzzleWindow::COLOR_SAVE_FILENAME = "colors.csv";

PuzzleWindow::PuzzleWindow(int width, int height, const char* title) : Fl_Window(width, height, title) {
    begin();
    this->gameController = new GameController();
    this->gameController->setTimerPropertyChangedHandler(PuzzleWindow::cbUpdateTimer, this);
    this->inputs = new Fl_Input*[model::TileBoard::BOARD_AREA];

    this->settingsButton = new Fl_Button(290, 30, 80, 24, "Settings");
    this->puzzleSelectMenu = new Fl_Menu_Button(20, 30, 200, 24, "Select Puzzle");
    this->resetButton = new Fl_Button(380, 30, 80, 24, "Reset");
    this->puzzleStatus = new Fl_Output(70, 440, 170, 24);
    this->pauseButton = new Fl_Button(380, 440, 80, 24, "Pause");
    this->scoreboardButton = new Fl_Button(290, 60, 170, 24, "ScoreBoard");
    this->timerDisplay = new Fl_Output(300, 440, 60, 24, "s");
    this->timerDisplay->value(std::to_string(this->gameController->getCurrentBoardTime()).c_str());
    this->timerDisplay->align(FL_ALIGN_RIGHT);

    for (int i = 0; i < 64; i++) {
        this->addInputBox(i);
    }
    this->updateFromController();
    this->populateMenu();

    this->resetButton->callback(PuzzleWindow::cbReset, this);
    this->pauseButton->callback(PuzzleWindow::cbPause, this);
    this->settingsButton->callback(PuzzleWindow::cbSettings, this);
    this->scoreboardButton->callback(PuzzleWindow::cbScoreBoard, this);
    this->setInitialColors();
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
    delete this->settingsButton;
    delete this->scoreboardButton;
}

Fl_Color PuzzleWindow::getInputTileColor() const {
    return this->currentCellColor;
}

Fl_Color PuzzleWindow::getInputNumberColor() const {
    return this->currentNumberColor;
}

void PuzzleWindow::setInitialColors() {
    if (fileio::fileExists(COLOR_SAVE_FILENAME)) {
        std::vector<io::PuzzleColorPersistence::PuzzleColor> colors = io::PuzzleColorPersistence::loadPuzzleColorsFromFile(COLOR_SAVE_FILENAME);
        this->currentCellColor = fl_rgb_color(colors[0].red, colors[0].green, colors[0].blue);
        this->currentNumberColor = fl_rgb_color(colors[1].red, colors[1].green, colors[1].blue);
    } else {
        this->currentCellColor = DEFAULT_MUTABLE_CELL_COLOR;
        this->currentNumberColor = DEFAULT_CELL_TEXT_COLOR;
    }
    this->setInputTileColor(this->currentCellColor);
    this->setInputNumberColor(this->currentNumberColor);
}

void PuzzleWindow::cbOnCloseWindow(Fl_Widget*, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->gameController->saveAllPuzzles();
    window->gameController->saveScoreBoard();
    window->hide();
}

inline void PuzzleWindow::addInputBox(int number) {
    int x_offset = (number % model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
    int y_offset = (number / model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
    this->inputs[number] = new Fl_Input(GRID_STARTING_X + x_offset, GRID_STARTING_Y + y_offset, GRID_BOX_WIDTH, GRID_BOX_WIDTH);
    this->inputs[number]->callback(cbSubmit, this);
}

void PuzzleWindow::updateFromController() {
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        int tileValue = this->gameController->getTileValue(i);
        bool tileImmutable = this->gameController->isTileImmutable(i);
        const std::string boxValue = tileValue == 0 ? "" : std::to_string(tileValue);
        inputs[i]->value(boxValue.c_str());
        inputs[i]->readonly(tileImmutable);
    }
    std::string puzzleLabel = std::to_string(this->gameController->getCurrentLevel() + 1);
    this->puzzleStatus->copy_label(puzzleLabel.c_str());
    this->puzzleStatus->value(this->gameController->isSolved() ? SOLVED_MESSAGE : NOT_SOLVED_MESSAGE);
    this->setInputTileColor(this->currentCellColor);
    this->setInputNumberColor(this->currentNumberColor);
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

void PuzzleWindow::setInputTileColor(Fl_Color color) {
    this->currentCellColor = color;
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        Fl_Input* currentInput = this->inputs[i];
        bool isTileImmutable = this->gameController->isTileImmutable(i);
        currentInput->color(isTileImmutable ? fl_darker(this->currentCellColor) : this->currentCellColor);
        currentInput->selection_color(fl_darker(currentInput->color()));
    }
    this->redraw();
}

void PuzzleWindow::setInputNumberColor(Fl_Color color) {
    this->currentNumberColor = color;
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        Fl_Input* currentInput = this->inputs[i];
        currentInput->textcolor(this->currentNumberColor);
    }
    this->redraw();
}

void PuzzleWindow::cbReset(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->gameController->resetCurrentPuzzle();
    window->updateFromController();
    window->gameController->saveAllPuzzles();
    window->timerDisplay->value("0");
}

void PuzzleWindow::cbChangePuzzle(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    const char* label = ((Fl_Menu_*)widget)->text();
    int puzzleSelected = std::atoi(label) - 1;
    window->pushInputs();
    window->gameController->setCurrentLevel(puzzleSelected);
    window->updateFromController();
}

void PuzzleWindow::cbSubmit(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->pushInputs();
    window->updateFromController();
    window->gameController->toggleTimer(false);

    if (window->gameController->isSolved())
    {
        AddNewScoreWindow* addScoreWindow = new AddNewScoreWindow(275, 100, "Score Entry", window);
        addScoreWindow->set_modal();
        addScoreWindow->show();
    }
}

void PuzzleWindow::completeLevel() {
    bool isAdvanced = this->gameController->tryAdvanceLevel();
    if (isAdvanced) {
        this->updateFromController();
    }
}

void PuzzleWindow::cbSettings(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    SettingsWindow* settings = new SettingsWindow(475, 250, "Settings", window);
    settings->set_modal();
    settings->show();
}

void PuzzleWindow::cbPause(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    window->makeInputsVisible(window->isPaused);
    window->pauseButton->label(window->isPaused ? "Pause" : "Unpause");
    window->isPaused = !window->isPaused;
    window->gameController->toggleTimer(window->isPaused);
}

void PuzzleWindow::makeInputsVisible(bool isVisible) {
    for (int i = 0; i < model::TileBoard::BOARD_AREA; i++) {
        Fl_Input* currentInput = this->inputs[i];
        if (isVisible) {
            currentInput->show();
        } else {
            currentInput->hide();
        }
    }
}

void PuzzleWindow::cbUpdateTimer(int number, void* data) {
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
    return output > model::TileBoard::BOARD_AREA ? 0 : output;
}

void PuzzleWindow::cbScoreBoard(Fl_Widget* widget, void* data) {
    PuzzleWindow* window = (PuzzleWindow*) data;
    ScoreBoardWindow* scoreboard = new ScoreBoardWindow(300, 300, "ScoreBoard", window);
    scoreboard->set_modal();
    scoreboard->show();
}

GameController* const PuzzleWindow::getGameController() const
{
    return this->gameController;
}

}
