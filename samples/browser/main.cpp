#include "BrowserWindow.hpp"

#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.htmlengine.brownser");

    BrowserWindow window;
    window.set_default_size(800, 600);

    return app->run(window);
}