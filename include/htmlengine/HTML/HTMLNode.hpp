#pragma once

#include <htmlengine/XML/XMLNode.hpp>

#include <cairomm/cairomm.h>
#include <string>

namespace HTMLEngine::HTML
{
    class HTMLNode : public XML::XMLNode
    {
    public:
        HTMLNode(XML::NodeType type);
        virtual ~HTMLNode();

        HTMLNode *get_parent();

        virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    };
}