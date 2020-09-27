#include <htmlengine/XML/XMLElement.hpp>

#include <algorithm>

namespace HTMLEngine::XML
{
    XMLElement::XMLElement()
        : XMLNode(NodeType::Element)
    {
    }

    void XMLElement::add_attribute(std::string key, std::string value)
    {
        m_attributes.insert(std::pair<std::string, std::string>(key, value));
    }

    std::string *XMLElement::get_attribute(std::string key)
    {
        std::map<std::string, std::string>::iterator attribute = m_attributes.find(key);
        if(attribute != m_attributes.end())
            return &attribute->second;

        return nullptr;
    }

    std::vector<XMLElement*> XMLElement::get_elements_by_tag_name(std::string tag_name)
    {
        std::vector<XMLElement*> elements;

        for(auto &node : m_nodes)
        {
            if(node.get()->get_type() != NodeType::Element)
                continue;

            XMLElement *node_element = reinterpret_cast<XMLElement*>(node.get());

            std::vector<XMLElement*> node_elements = node_element->get_elements_by_tag_name(tag_name);

            elements.insert(elements.end(), node_elements.begin(), node_elements.end());
        }

        if(get_name() == tag_name)
            elements.emplace_back(this);

        return elements;
    }

    std::string XMLElement::get_text_content()
    {
        return XMLNode::to_string();
    }

    std::string XMLElement::to_string()
    {
        std::string output;

        output += "<" + m_name;
        for(auto &attribute : m_attributes)
            output +=  " " + attribute.first + "=\"" + attribute.second + "\"";

        if(m_nodes.size() > 0)
        {
            output += ">";
            output += XMLNode::to_string();
            output += "</" + m_name + ">";
        }
        else
            output += "/>";

        return output;
    }

    bool XMLElement::support_child_element(std::string tag_name)
    {
        return true;
    }

    bool XMLElement::support_content(std::string tag_name)
    {
        return true;
    }

    XMLElement::~XMLElement()
    {
    }
}