#include <htmlengine/XML/XMLWhitespace.hpp>

namespace HTMLEngine::XML
{
    XMLWhitespace::XMLWhitespace()
        : XMLNode(NodeType::Whitespace)
    {
    }

    std::string XMLWhitespace::to_string()
    {
        return m_value;
    }

    XMLWhitespace::~XMLWhitespace()
    {
    }
}