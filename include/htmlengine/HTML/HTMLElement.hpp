#pragma once

#include <htmlengine/XML/XMLElement.hpp>

#include <cairomm/cairomm.h>

namespace HTMLEngine::HTML
{
    class HTMLElement : public XML::XMLElement
    {
    public:
        HTMLElement();
        ~HTMLElement();

        std::vector<HTMLElement*> get_elements_by_tag_name(std::string tag_name);
        static bool support_child_element(std::string tag_name);
        static bool support_content(std::string tag_name);

        virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    private:
        
    };
}