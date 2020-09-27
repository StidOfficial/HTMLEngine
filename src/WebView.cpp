#include <htmlengine/WebView.hpp>

#include <htmlengine/HTML/HTMLNode.hpp>

#include <iostream>
#include <cairo/cairo.h>

namespace HTMLEngine
{
    WebView::WebView()
    {
        m_curl = curl_easy_init();
        if(!m_curl)
            throw std::runtime_error("Failed to init curl");

        #ifdef SKIP_PEER_VERIFICATION
            curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
        #endif
        #ifdef SKIP_HOSTNAME_VERIFICATION
            curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
        #endif
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WebView::write_memory_callback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&m_chunk);
        curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    }

    WebView::WebView(URI uri)
        : WebView()
    {
        load_from_uri(uri);
    }

    void WebView::load_from_uri(URI uri)
    {
        curl_easy_setopt(m_curl, CURLOPT_URL, "file:///home/stidofficial/Documents/htmlengine/teste.html");

        std::cout << (const char*)uri << std::endl;

        CURLcode res = curl_easy_perform(m_curl);
        if(res != CURLE_OK)
            std::cerr << "Failed curl_easy_perform() : " << curl_easy_strerror(res) << std::endl;

        m_document.parse(m_chunk, true);
        m_document.load_style_sheets();

        //std::cout << m_document.get_root()->get_type() << std::endl;
        //std::cout << "Debug HTML root : " << m_document.get_root()->to_string() << std::endl;
    }

    size_t WebView::write_memory_callback(void *content, size_t size, size_t nmemb, void *userp)
    {
        size_t realsize = size * nmemb;
        std::string *chunk = (std::string*)userp;

        chunk->append((char*)content, realsize);

        return realsize;
    }

    void WebView::on_button_pressed(int x, int y, uint32_t button)
    {

    }

    void WebView::on_button_released(int x, int y, uint32_t button)
    {

    }

    void WebView::on_motion(int x, int y)
    {

    }

    void WebView::set_size(int width, int height)
    {
        m_width = width;
        m_height = height;
    }

    void WebView::draw(const Cairo::RefPtr<Cairo::Context>& cr)
    {
        m_document.draw(cr);
    }

    WebView::~WebView()
    {
        curl_easy_cleanup(m_curl);
    }
}