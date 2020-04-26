#include "PuzzleWindow.h"

#include <string>
#include <FL/Fl_Menu_Item.H>

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
	this->puzzleStatus = new Fl_Output(40, 390, 170, 24, "1");
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

inline void PuzzleWindow::addInputBox(int number)
{
	int x_offset = (number % model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
	int y_offset = (number / model::TileBoard::BOARD_WIDTH) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
    this->inputs[number] = new Fl_Input(GRID_STARTING_X + x_offset, GRID_STARTING_Y + y_offset, GRID_BOX_WIDTH, GRID_BOX_WIDTH);
    this->inputs[number]->callback(cbSubmit, this);
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
	this->puzzleStatus->value(this->gameController->isSolved() ? SOLVED_MESSAGE : NOT_SOLVED_MESSAGE);
}

void PuzzleWindow::pushInputs()
{
	for (int i = 0; i < model::TileBoard::BOARD_AREA; i++)
	{
		int tileValue = parseEntry(this->inputs[i]->value());
		this->gameController->trySetTileValue(i, tileValue);
	}
	this->gameController->saveAllPuzzles(); // TODO this should only be called once when exiting the application
}

inline void PuzzleWindow::populateMenu()
{
	for (unsigned int i = 0; i < this->gameController->getAvailableLevels(); i++)
	{
		std::string label = std::to_string(i + 1);
		this->puzzleSelectMenu->add(label.c_str(), 0, cbChangePuzzle, this);
	}
}

void PuzzleWindow::cbReset(Fl_Widget* widget, void* data)
{
	PuzzleWindow* window = (PuzzleWindow*) data;
	window->gameController->resetCurrentPuzzle();
	window->updateInputs();
}

void PuzzleWindow::cbChangePuzzle(Fl_Widget* widget, void* data)
{
	PuzzleWindow* window = (PuzzleWindow*) data;
	const char* label = ((Fl_Menu_*)widget)->text();
    int puzzleSelected = std::atoi(label) - 1;
    window->pushInputs();
    window->gameController->setCurrentLevel(puzzleSelected);
    window->updateInputs();
    window->puzzleStatus->label(label);
}

void PuzzleWindow::cbSubmit(Fl_Widget* widget, void* data)
{
	PuzzleWindow* window = (PuzzleWindow*) data;
	window->pushInputs();
	window->updateInputs();
}

int PuzzleWindow::parseEntry(const char* entry)
{
	int output = 0;
	for (int i = 0; entry[i] != '\0'; i++)
	{
		if (std::isdigit(entry[i]))
		{
			output *= 10;
			output += entry[i] - '0';
		}
		else
		{
			return 0;
		}
	}
	return output > 64 ? 0 : output;
}

}
