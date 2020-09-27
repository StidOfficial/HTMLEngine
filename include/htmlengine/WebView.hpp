#pragma once

#include <htmlengine/URI.hpp>
#include <htmlengine/HTML/HTMLDocument.hpp>

#include <curl/curl.h>
#include <cairomm/cairomm.h>

namespace HTMLEngine
{
    class WebView
    {
    public:
        WebView();
        WebView(URI uri);
        ~WebView();

        void load_from_uri(URI uri);

        void on_button_pressed(int x, int y, uint32_t button);
        void on_button_released(int x, int y, uint32_t button);
        void on_motion(int x, int y);
        void set_size(int width, int height);

        void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    protected:
        CURL *m_curl;
        std::string m_chunk;
        
        HTML::HTMLDocument m_document;
        int m_width, m_height;
    private:
        static size_t write_memory_callback(void *content, size_t size, size_t nmemb, void *userp);
    };
}
