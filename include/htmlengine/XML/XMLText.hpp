#pragma once

#include <htmlengine/XML/XMLNode.hpp>

namespace HTMLEngine::XML
{
    class XMLText : public XMLNode
    {
    public:
        XMLText();
        ~XMLText();

        virtual std::string to_string();
    };
}