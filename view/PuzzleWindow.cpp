#include "PuzzleWindow.h"

#include <string>

#include "../model/TileBoard.h"

namespace view
{

PuzzleWindow::PuzzleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
	begin();
	this->gameController = new GameController();
	this->inputs = new Fl_Input*[model::TileBoard::BOARD_AREA];

	this->puzzleSelectMenu = new Fl_Menu_Button(20, 20, 200, 24, "Select Puzzle");
	this->resetButton = new Fl_Button(250, 20, 80, 24, "Reset");
	this->timerDisplay = new Fl_Output(20, 390, 80, 24);
	this->pauseButton = new Fl_Button(250, 390, 80, 24, "Pause");

	for (int i = 0; i < 64; i++)
	{
		addInputBox(i);
	}
	updateInputs();
	populateMenu();

	this->resetButton->callback(cbReset, this);

	end();
}

PuzzleWindow::~PuzzleWindow()
{
	delete this->puzzleSelectMenu;
	delete this->resetButton;
	for (int i = 0; i < model::TileBoard::BOARD_AREA; i++)
	{
		delete this->inputs[i];
	}
	delete this->inputs;
	delete this->timerDisplay;
	delete this->pauseButton;
}

void PuzzleWindow::addInputBox(int number)
{
	int x_offset = (number % model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
	int y_offset = (number / model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
    this->inputs[number] = new Fl_Input(GRID_STARTING_X + x_offset, GRID_STARTING_Y + y_offset, GRID_BOX_WIDTH, GRID_BOX_WIDTH);
}

void PuzzleWindow::updateInputs()
{
	for (int i = 0; i < model::TileBoard::BOARD_AREA; i++)
	{
		int tileValue = this->gameController->getTileValue(i);
		bool tileImmutable = this->gameController->isTileImmutable(i);
		std::string boxValue = tileValue == 0 ? "" : std::to_string(tileValue);
		inputs[i]->value(boxValue.c_str());
		inputs[i]->readonly(tileImmutable);
	}
}

inline void PuzzleWindow::populateMenu()
{
	for (unsigned int i = 0; i < this->gameController->getAvailableLevels(); i++)
	{
		this->puzzleSelectMenu->add(std::to_string(i + 1).c_str());
	}
}

void PuzzleWindow::cbReset(Fl_Widget* widget, void* data)
{
	PuzzleWindow* window = (PuzzleWindow*) data;
	window->gameController->resetCurrentPuzzle();
	window->updateInputs();
}

}
