#include <htmlengine/XML/XMLText.hpp>

namespace HTMLEngine::XML
{
    XMLText::XMLText()
        : XMLNode(NodeType::Text)
    {
        m_name = "#text";
    }

    std::string XMLText::to_string()
    {
        return m_value;
    }

    XMLText::~XMLText()
    {
    }
}