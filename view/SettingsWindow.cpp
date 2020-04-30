#include <string>
#include <FL/Fl.H>

#include "SettingsWindow.h"
#include "fileio/PuzzleColorPersistence.h"

namespace view
{

SettingsWindow::SettingsWindow(int width, int height, const std::string& title, PuzzleWindow* parent) : Fl_Window(width, height, title.c_str())
{
    begin();
    this->cellColorMenu = new Fl_Color_Chooser(25, 25, 200, 150, "Cell Color");
    this->numberColorMenu = new Fl_Color_Chooser(250, 25, 200, 150, "Number Color");
    this->cellColorMenu->mode(0);
    this->numberColorMenu->mode(0);

    unsigned char cellRed, cellGreen, cellBlue;
    Fl::get_color(parent->getInputTileColor(), cellRed, cellGreen, cellBlue);
    unsigned char numberRed, numberGreen, numberBlue;
    Fl::get_color(parent->getInputNumberColor(), numberRed, numberGreen, numberBlue);

    this->cellColorMenu->rgb((double)cellRed / 255, (double)cellGreen / 255, (double)cellBlue / 255);
    this->numberColorMenu->rgb((double)numberRed / 255, (double)numberGreen / 255, (double)numberBlue / 255);

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

    io::PuzzleColorPersistence::PuzzleColor numberColorData;
    numberColorData.red = window->numberColorMenu->r() * 255;
    numberColorData.green = window->numberColorMenu->g() * 255;
    numberColorData.blue = window->numberColorMenu->b() * 255;

    io::PuzzleColorPersistence::PuzzleColor cellColorData;
    cellColorData.red = window->cellColorMenu->r() * 255;
    cellColorData.green = window->cellColorMenu->g() * 255;
    cellColorData.blue = window->cellColorMenu->b() * 255;

    io::PuzzleColorPersistence::savePuzzleColorsToFile(cellColorData, numberColorData, PuzzleWindow::COLOR_SAVE_FILENAME);

    Fl_Color numberColor = fl_rgb_color(numberColorData.red, numberColorData.green, numberColorData.blue);
    Fl_Color cellColor = fl_rgb_color(cellColorData.red, cellColorData.green, cellColorData.blue);

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
