#include "BrowserWindow.hpp"

#include <htmlengine/HTMLEngine.hpp>

BrowserWindow::BrowserWindow()
    : m_historyBox(Gtk::ORIENTATION_HORIZONTAL),
        m_imageBack(Gtk::Stock::GO_BACK, Gtk::ICON_SIZE_BUTTON),
        m_imageForward(Gtk::Stock::GO_FORWARD, Gtk::ICON_SIZE_BUTTON),
        m_imageRefresh(Gtk::Stock::REFRESH, Gtk::ICON_SIZE_BUTTON),
        m_browser(m_htmlEngine)
{
    m_headerBar.set_visible(true);
    m_headerBar.set_show_close_button(true);
    m_headerBar.set_decoration_layout("menu:close");

    m_historyBox.get_style_context()->add_class("linked");

    m_historyBack.set_image(m_imageBack);
    m_historyBack.set_sensitive(false);
    m_historyBack.signal_clicked().connect(sigc::mem_fun(*this, &BrowserWindow::on_back_clicked));
    m_historyBox.add(m_historyBack);

    m_historyForward.set_image(m_imageForward);
    m_historyForward.set_sensitive(false);
    m_historyForward.signal_clicked().connect(sigc::mem_fun(*this, &BrowserWindow::on_forward_clicked));
    m_historyBox.add(m_historyForward);

    m_headerBar.pack_start(m_historyBox);

    m_address.set_text("https://google.com");
    m_address.signal_key_press_event().connect(sigc::mem_fun(*this, &BrowserWindow::on_address_key_press), false);
    m_headerBar.set_custom_title(m_address);

    m_refresh.set_image(m_imageRefresh);
    m_refresh.set_sensitive(false);
    m_refresh.signal_clicked().connect(sigc::mem_fun(*this, &BrowserWindow::on_refresh_clicked));
    m_headerBar.pack_end(m_refresh);

    set_titlebar(m_headerBar);

    add(m_browser);

    show_all_children();

    go_to(m_address.get_text());
}

void BrowserWindow::on_back_clicked()
{
    m_historyForward.set_sensitive(true);

    m_historyCursor--;

    if(m_historyCursor == m_history.begin())
        m_historyBack.set_sensitive(false);

    go_to(*m_historyCursor);
}

void BrowserWindow::on_forward_clicked()
{
    m_historyBack.set_sensitive(true);

    m_historyCursor++;

    if(m_historyCursor == --m_history.end())
        m_historyForward.set_sensitive(false);

    go_to(*m_historyCursor);
}

bool BrowserWindow::on_address_key_press(GdkEventKey* event)
{
    if(event->keyval != GDK_KEY_Return)
        return false;

    if(m_history.size() > 0)
        m_historyBack.set_sensitive(true);
    m_historyForward.set_sensitive(false);
    m_refresh.set_sensitive(false);

    go_to(m_address.get_text());

    m_historyCursor = m_history.emplace(m_history.end(), m_address.get_text());

    return true;
}

void BrowserWindow::on_refresh_clicked()
{
    
}

void BrowserWindow::go_to(std::string address)
{
    m_refresh.set_sensitive(false);

    m_address.progress_pulse();

    m_address.set_progress_pulse_step(0.3);
    try
    {
        m_browser.load_from_uri(address);
    }
    catch(HTMLEngine::uri_invalid_port)
    {
    }
    catch(HTMLEngine::unsupported_scheme)
    {
    }

    m_address.set_progress_pulse_step(0.5);

    m_refresh.set_sensitive(true);
}

BrowserWindow::~BrowserWindow()
{
    
}