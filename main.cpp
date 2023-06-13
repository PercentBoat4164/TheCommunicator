#include "gdkmm/display.h"
#include "gdkmm/rectangle.h"
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/application.h>
#include <gdkmm/monitor.h>
#include <iostream>

// MyWindow.hpp
class MyWindow : public Gtk::Window {
public:
    MyWindow();

protected:
    void on_button_clicked();

    Gtk::Button m_button;
};

// MyWindow.cpp
MyWindow::MyWindow() : m_button("Hello World!") {
    set_title("Basic application");
    m_button.set_margin(10);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));
    set_child(m_button);
    m_button.show();
}

void MyWindow::on_button_clicked() {
    std::cout << "Hello World!" << std::endl;
}

// main.cpp
int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create("com.daniel.thadd.thecommunicator");

    auto monitors = Gdk::Display::get_default()->get_monitors();
    for (uint32_t n{monitors->get_n_items()}; n > 0; n--) {
        auto monitor = monitors->get_typed_object<Gdk::Monitor>(n - 1);
        Gdk::Rectangle rect;
        monitor->get_geometry(rect);
        std::cout << monitor->get_width_mm() << 'x' << monitor->get_height_mm() << '|' << rect.get_width() << 'x' << rect.get_height() << '@' << monitor->get_refresh_rate()/1000.0 << std::endl;
    }

    return app->make_window_and_run<MyWindow>(argc, argv);
}