#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Button.H>

#include "PuzzleWindow.h"

namespace view
{

/**
 * This is the Settings window for the Puzzle Game.
 *
 * @author Thomas Luke Whaley
 */
class SettingsWindow : public Fl_Window
{
public:
    /**
     * Constructs a new SettingsWindow.
     *
     * @param width the window's width
     * @param height the window's height
     * @param title the window's title
     * @param parent the window's parent window.
     */
    SettingsWindow(int width, int height, const std::string& title, PuzzleWindow* parent);

    /**
     * Deallocates this setting window and all of its
     * resources.
     */
    virtual ~SettingsWindow();

private:
    Fl_Color_Chooser* cellColorMenu;
    Fl_Color_Chooser* numberColorMenu;
    Fl_Button* saveButton;
    Fl_Button* cancelButton;

    PuzzleWindow* parent;

    static void cbSave(Fl_Widget* widget, void* data);
    static void cbCancel(Fl_Widget* widget, void* data);
};

}

#endif // SETTINGSWINDOW_H
