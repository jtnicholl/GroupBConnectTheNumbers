#include <FL/Fl.H>

#include "view/PuzzleWindow.h"

using namespace view;

int main (int argc, char ** argv) {
    Fl::lock();
    Fl_Window* window = new PuzzleWindow(350, 430, "Connect the Numbers by Morgenstern, Nicholl, Whaley");
    window->callback(PuzzleWindow::cbOnCloseWindow, window);
    window->show();

    return(Fl::run());
}
