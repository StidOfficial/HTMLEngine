#include "BrowserWidget.hpp"

BrowserWidget::BrowserWidget(HTMLEngine::HTMLEngine &htmlEngine)
    : m_htmlEngine(&htmlEngine)
{
    add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
}

void BrowserWidget::load_from_uri(HTMLEngine::URI uri)
{
    m_view = m_htmlEngine->load_from_uri(uri);
}

bool BrowserWidget::on_button_press_event(GdkEventButton *event)
{
    if(!m_view)
        return false;

    m_view->on_button_pressed(event->x, event->y, event->button);

    return true;
}

bool BrowserWidget::on_button_release_event(GdkEventButton *event)
{
    if(!m_view)
        return false;

    m_view->on_button_released(event->x, event->y, event->button);

    return true;
}

bool BrowserWidget::on_motion_notify_event(GdkEventMotion *event)
{
    if(!m_view)
        return false;

    m_view->on_motion(event->x, event->y);

    return true;
}

void BrowserWidget::on_size_allocate(Gtk::Allocation allocation)
{
    if(!m_view)
        return;

    m_view->set_size(allocation.get_width(), allocation.get_height());
}

bool BrowserWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if(!m_view)
        return false;

    // Init the base background at white
    cr->rectangle(0, 0, get_allocated_width(), get_allocated_height());
    cr->set_source_rgb(1, 1, 1);
    cr->fill();

    m_view->draw(cr);

    return true;
}

BrowserWidget::~BrowserWidget()
{
    m_htmlEngine->destroy(m_view);
}