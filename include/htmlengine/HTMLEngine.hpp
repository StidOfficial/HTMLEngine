#pragma once

#include <htmlengine/WebView.hpp>

#include <exception>

namespace HTMLEngine
{
    struct unsupported_scheme : public std::exception
    {
        const char* what() const throw()
        {
            return "Unsupported scheme";
        }
    };

    class HTMLEngine
    {
    public:
        HTMLEngine();
        ~HTMLEngine();

        WebView *load_from_uri(URI uri);
        void destroy(WebView *view);
    };
}
