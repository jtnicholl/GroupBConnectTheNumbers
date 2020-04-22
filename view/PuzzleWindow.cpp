#include "PuzzleWindow.h"

namespace view
{

PuzzleWindow::PuzzleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
	begin();
	this->inputs = new Fl_Input*[64];

	this->puzzleSelectMenu = new Fl_Menu_Button(20, 20, 200, 24, "Select Puzzle");
	this->resetButton = new Fl_Button(250, 20, 80, 24, "Reset");
	this->timerDisplay = new Fl_Output(20, 390, 80, 24);
	this->pauseButton = new Fl_Button(250, 390, 80, 24, "Pause");

	for (int i = 0; i < 64; i++)
	{
		addInputBox(i);
	}

	end();
}

PuzzleWindow::~PuzzleWindow()
{
	delete this->puzzleSelectMenu;
	delete this->resetButton;
	for (int i = 0; i < 64; i++)
	{
		delete this->inputs[i];
	}
	delete this->inputs;
	delete this->timerDisplay;
	delete this->pauseButton;
}

void PuzzleWindow::addInputBox(int number)
{
	int x_offset = (number % 8) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
	int y_offset = (number / 8) * (GRID_BOX_WIDTH + GRID_BOX_PADDING);
    this->inputs[number] = new Fl_Input(GRID_STARTING_X + x_offset, GRID_STARTING_Y + y_offset, GRID_BOX_WIDTH, GRID_BOX_WIDTH);
}

}
