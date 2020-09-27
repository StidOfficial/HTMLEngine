#pragma once

#include <htmlengine/XML/XMLComment.hpp>

namespace HTMLEngine::HTML
{
    class HTMLComment : public XML::XMLComment
    {
    public:
        HTMLComment();
        ~HTMLComment();
    };
}