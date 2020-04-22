#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

namespace view
{

class PuzzleWindow : public Fl_Window
{
	public:
		PuzzleWindow(int width, int height, const char* title);
		virtual ~PuzzleWindow();

	private:
		const int GRID_STARTING_X = 20;
		const int GRID_STARTING_Y = 60;
		const int GRID_BOX_WIDTH = 30;
		const int GRID_BOX_PADDING = 10;
		Fl_Menu_Button* puzzleSelectMenu;
		Fl_Button* resetButton;
		Fl_Input** inputs;
		Fl_Output* timerDisplay;
		Fl_Button* pauseButton;
		void addInputBox(int number);
};

}

#endif // PUZZLEWINDOW_H
