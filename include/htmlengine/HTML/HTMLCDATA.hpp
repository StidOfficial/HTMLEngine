#pragma once

#include <htmlengine/XML/XMLCDATA.hpp>

namespace HTMLEngine::HTML
{
    class HTMLCDATA : public XML::XMLCDATA
    {
    public:
        HTMLCDATA();
        ~HTMLCDATA();
    };
}