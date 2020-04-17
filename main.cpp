#include <FL/Fl.H>

#include "View/PuzzleWindow.h"

using namespace view;

int main (int argc, char ** argv)
{
  Fl_Window* window;

  window = new PuzzleWindow(350, 430, "Connect the Numbers by Morgenstern, Nicholl, Whaley");

  window->show();

  return(Fl::run());
}
