#pragma once

#include <htmlengine/XML/XMLNode.hpp>

namespace HTMLEngine::XML
{
    class XMLComment : public XMLNode
    {
    public:
        XMLComment();
        ~XMLComment();
    };
}