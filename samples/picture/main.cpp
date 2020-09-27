#include <htmlengine/HTMLEngine.hpp>

int main(int argc, char *argv[])
{
    HTMLEngine::HTMLEngine *htmlEngine = new HTMLEngine::HTMLEngine();

    HTMLEngine::WebView * webView = htmlEngine->load_from_uri(HTMLEngine::URI("https://google.com"));
    htmlEngine->destroy(webView);

    delete htmlEngine;

    return 0;
}