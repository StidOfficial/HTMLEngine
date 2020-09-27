#include <htmlengine/XML/XMLNode.hpp>

namespace HTMLEngine::XML
{
    XMLNode::XMLNode(NodeType type)
        : m_type(type), m_parent(nullptr)
    {
    }

    void XMLNode::set_name(std::string name)
    {
        m_name = name;
    }

    std::string XMLNode::get_name()
    {
        return m_name;
    }

    NodeType XMLNode::get_type()
    {
        return m_type;
    }

    void XMLNode::set_parent(XMLNode *parent)
    {
        m_parent = parent;
    }

    XMLNode *XMLNode::get_parent()
    {
        return m_parent;
    }

    std::vector<std::shared_ptr<XMLNode>> XMLNode::get_nodes()
    {
        return m_nodes;
    }

    void XMLNode::append(XMLNode *element)
    {
        m_nodes.emplace_back(element);

        element->set_parent(this);
    }

    void XMLNode::clear()
    {
        m_nodes.clear();
    }

    std::string XMLNode::to_string()
    {
        std::string output;

        for(auto &node : m_nodes)
            output += node.get()->to_string();

        return output;
    }

    void XMLNode::set_value(std::string value)
    {
        m_value = value;
    }

    std::string XMLNode::get_value()
    {
        return m_value;
    }

    XMLNode::~XMLNode()
    {
        clear();
    }
}