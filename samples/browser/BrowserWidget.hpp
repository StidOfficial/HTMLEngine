#pragma once

#include <gtkmm.h>

#include <htmlengine/HTMLEngine.hpp>
#include <htmlengine/WebView.hpp>
#include <htmlengine/URI.hpp>

class BrowserWidget : public Gtk::ScrolledWindow
{
public:
    BrowserWidget(HTMLEngine::HTMLEngine &htmlEngine);
    ~BrowserWidget();

    void load_from_uri(HTMLEngine::URI uri);
protected:
    virtual bool on_button_press_event(GdkEventButton *event);
    virtual bool on_button_release_event(GdkEventButton *event);
    virtual bool on_motion_notify_event(GdkEventMotion *event);
    virtual void on_size_allocate(Gtk::Allocation allocation);
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

    HTMLEngine::HTMLEngine *m_htmlEngine;
    HTMLEngine::WebView *m_view;
};