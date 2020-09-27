#pragma once

#include <htmlengine/HTML/HTMLElement.hpp>

#include <cairomm/cairomm.h>

namespace HTMLEngine::HTML::Elements
{
    class HTMLElementH1 : public HTMLElement
    {
    public:
        HTMLElementH1();
        ~HTMLElementH1();

        virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    };
}