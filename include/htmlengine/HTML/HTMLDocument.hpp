#pragma once

#include <htmlengine/XML/XMLDocument.hpp>
#include <htmlengine/HTML/HTMLNode.hpp>
#include <htmlengine/HTML/HTMLElement.hpp>
#include <htmlengine/HTML/HTMLText.hpp>
#include <htmlengine/HTML/HTMLCDATA.hpp>
#include <htmlengine/HTML/HTMLComment.hpp>
#include <htmlengine/HTML/HTMLWhitespace.hpp>
#include <htmlengine/CSS/CSSDocument.hpp>

#include <vector>
#include <cairomm/cairomm.h>

namespace HTMLEngine::HTML
{
    class HTMLDocument : public XML::XMLDocument<HTMLNode, HTMLElement, HTMLText, HTMLCDATA, HTMLComment, HTMLWhitespace>
    {
    public:
        HTMLDocument();
        ~HTMLDocument();

        HTMLElement *get_body();
        std::vector<HTMLElement*> get_elements_by_tag_name(std::string tag_name);
        void set_lang(std::string lang);
        std::string get_lang();
        void load_style_sheets();

        virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    private:
        std::vector<std::unique_ptr<CSS::CSSDocument>> m_CSS_documents;
    };
}