#include <htmlengine/HTMLEngine.hpp>

#include <stdexcept>
#include <curl/curl.h>

namespace HTMLEngine
{
    HTMLEngine::HTMLEngine()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    WebView *HTMLEngine::load_from_uri(URI uri)
    {
        if(uri.get_scheme() != "http" && uri.get_scheme() != "https")
            throw unsupported_scheme();

        return new WebView(uri);
    }

    void HTMLEngine::destroy(WebView *view)
    {
        delete view;
    }

    HTMLEngine::~HTMLEngine()
    {
        curl_global_cleanup();
    }
}