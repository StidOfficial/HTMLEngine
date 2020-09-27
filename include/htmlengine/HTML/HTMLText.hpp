#pragma once

#include <htmlengine/XML/XMLText.hpp>
#include <cairomm/cairomm.h>

#define TEXT_DEFAULT_SIZE 16

namespace HTMLEngine::HTML
{
    class HTMLText : public XML::XMLText
    {
    public:
        HTMLText();
        ~HTMLText();

        virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    };
}