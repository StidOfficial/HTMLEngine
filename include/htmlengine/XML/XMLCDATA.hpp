#pragma once

#include <htmlengine/XML/XMLNode.hpp>

namespace HTMLEngine::XML
{
    class XMLCDATA : public XMLNode
    {
    public:
        XMLCDATA();
        ~XMLCDATA();
    };
}