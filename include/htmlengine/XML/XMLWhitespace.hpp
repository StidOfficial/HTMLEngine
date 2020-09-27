#pragma once

#include <htmlengine/XML/XMLNode.hpp>

namespace HTMLEngine::XML
{
    class XMLWhitespace : public XMLNode
    {
    public:
        XMLWhitespace();
        ~XMLWhitespace();

        virtual std::string to_string();
    };
}