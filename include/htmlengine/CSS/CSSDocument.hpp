#pragma once

#include <string>
#include <vector>

namespace HTMLEngine::CSS
{
    class CSSDocument
    {
    public:
        CSSDocument();
        ~CSSDocument();
        void parse(std::string text, bool clear);
    private:
        static CSSDocument *parse(std::string text);
        static void clean_selector(std::string selector);
    };
}