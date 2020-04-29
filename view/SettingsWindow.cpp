#include <string>
#include <Fl/Fl.H>

#include "SettingsWindow.h"

namespace view
{

SettingsWindow::SettingsWindow(int width, int height, const std::string& title, PuzzleWindow* parent) : Fl_Window(width, height, title.c_str())
{
    begin();
    this->cellColorMenu = new Fl_Color_Chooser(25, 25, 200, 150, "Cell Color");
    this->numberColorMenu = new Fl_Color_Chooser(250, 25, 200, 150, "Number Color");
    this->cellColorMenu->mode(0);
    this->numberColorMenu->mode(0);

    this->saveButton = new Fl_Button(270, 200, 80, 27, "Save");
    this->cancelButton = new Fl_Button(370, 200, 80, 27, "Cancel");

    this->saveButton->callback(SettingsWindow::cbSave, this);
    this->cancelButton->callback(SettingsWindow::cbCancel, this);

    this->parent = parent;
    end();
}

SettingsWindow::~SettingsWindow()
{
    delete this->cellColorMenu;
    delete this->numberColorMenu;
    delete this->saveButton;
    delete this->cancelButton;
}

void SettingsWindow::cbSave(Fl_Widget* widget, void* data)
{
    SettingsWindow* window = (SettingsWindow*) data;

    Fl_Color numberColor = fl_rgb_color(window->numberColorMenu->r() * 255, window->numberColorMenu->g() * 255, window->numberColorMenu->b() * 255);
    Fl_Color cellColor = fl_rgb_color(window->cellColorMenu->r() * 255, window->cellColorMenu->g() * 255, window->cellColorMenu->b() * 255);

    window->parent->setInputNumberColor(Fl::get_color(numberColor));
    window->parent->setInputTileColor(Fl::get_color(cellColor));
    window->hide();
}

void SettingsWindow::cbCancel(Fl_Widget* widget, void* data)
{
    SettingsWindow* window = (SettingsWindow*) data;
    window->hide();
}

}
