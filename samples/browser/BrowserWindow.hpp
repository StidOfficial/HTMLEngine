#pragma once

#include "BrowserWidget.hpp"

#include <gtkmm.h>
#include <vector>

class BrowserWindow : public Gtk::Window
{
public:
    BrowserWindow();
    virtual ~BrowserWindow();
protected:
    void on_back_clicked();
    void on_forward_clicked();
    bool on_address_key_press(GdkEventKey* event);
    void on_refresh_clicked();
    void go_to(std::string address);

    std::vector<std::string> m_history;
    std::vector<std::string>::iterator m_historyCursor;
private:
    Gtk::HeaderBar m_headerBar;
    Gtk::Box m_historyBox;
    Gtk::Image m_imageBack;
    Gtk::Button m_historyBack;
    Gtk::Image m_imageForward;
    Gtk::Button m_historyForward;
    Gtk::Entry m_address;
    Gtk::Image m_imageRefresh;
    Gtk::Button m_refresh;
    BrowserWidget m_browser;
    HTMLEngine::HTMLEngine m_htmlEngine;
};