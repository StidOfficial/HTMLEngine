#include <htmlengine/HTML/HTMLElement.hpp>

#include <htmlengine/HTML/HTMLText.hpp>

namespace HTMLEngine::HTML
{
    HTMLElement::HTMLElement()
        : XML::XMLElement()
    {
    }

    std::vector<HTMLElement*> HTMLElement::get_elements_by_tag_name(std::string tag_name)
    {
        std::vector<HTMLElement*> elements;

        for(auto &node : m_nodes)
        {
            if(node.get()->get_type() != XML::NodeType::Element)
                continue;

            HTMLElement *node_element = reinterpret_cast<HTMLElement*>(node.get());

            std::vector<HTMLElement*> node_elements = node_element->get_elements_by_tag_name(tag_name);

            elements.insert(elements.end(), node_elements.begin(), node_elements.end());
        }

        if(get_name() == tag_name)
            elements.emplace_back(this);

        return elements;
    }

    bool HTMLElement::support_child_element(std::string tag_name)
    {
        if(tag_name == "title")
            return false;

        if(tag_name == "meta")
            return false;

        if(tag_name == "script")
            return false;

        return true;
    }

    bool HTMLElement::support_content(std::string tag_name)
    {
        if(tag_name == "meta")
            return false;

        return true;
    }

    void HTMLElement::draw(const Cairo::RefPtr<Cairo::Context>& cr)
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

    HTMLElement::~HTMLElement()
    {
    }
}