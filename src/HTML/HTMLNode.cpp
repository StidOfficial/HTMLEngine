#include <htmlengine/HTML/HTMLNode.hpp>

#include <htmlengine/HTML/HTMLElement.hpp>
#include <htmlengine/HTML/HTMLText.hpp>

namespace HTMLEngine::HTML
{
    HTMLNode::HTMLNode(XML::NodeType type)
        : XML::XMLNode(type)
    {
    }

    HTMLNode *HTMLNode::get_parent()
    {
        return reinterpret_cast<HTMLNode*>(m_parent);
    }

    void HTMLNode::draw(const Cairo::RefPtr<Cairo::Context>& cr)
    {
        for(auto &node : m_nodes)
            switch(node->get_type())
            {
                case XML::NodeType::Root:
                    break;
                case XML::NodeType::Element:
                {
                    HTMLElement *html_element = reinterpret_cast<HTMLElement*>(node.get());

                    html_element->draw(cr);
                    break;
                }
                case XML::NodeType::Text:
                {
                    HTMLText *html_text = reinterpret_cast<HTMLText*>(node.get());

                    html_text->draw(cr);
                    break;
                }
                case XML::NodeType::CDATA:
                    break;
                case XML::NodeType::Comment:
                    break;
                case XML::NodeType::Whitespace:
                    break;
                default:
                    break;
            }
    }

    HTMLNode::~HTMLNode()
    {
    }
}