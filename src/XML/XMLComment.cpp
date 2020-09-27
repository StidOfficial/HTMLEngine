#include <htmlengine/XML/XMLComment.hpp>

namespace HTMLEngine::XML
{
    XMLComment::XMLComment()
        : XMLNode(NodeType::Comment)
    {
        m_name = "#comment";
    }

    XMLComment::~XMLComment()
    {
    }
}