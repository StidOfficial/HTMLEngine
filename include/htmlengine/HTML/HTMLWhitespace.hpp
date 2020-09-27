#pragma once

#include <htmlengine/XML/XMLWhitespace.hpp>

namespace HTMLEngine::HTML
{
    class HTMLWhitespace : public XML::XMLWhitespace
    {
    public:
        HTMLWhitespace();
        ~HTMLWhitespace();
    };
}