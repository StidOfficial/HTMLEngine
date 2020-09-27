#include <htmlengine/HTML/HTMLDocument.hpp>

namespace HTMLEngine::HTML
{
    HTMLDocument::HTMLDocument()
        : XML::XMLDocument<HTMLNode, HTMLElement, HTMLText, HTMLCDATA, HTMLComment, HTMLWhitespace>()
    {
    }

    HTMLElement *HTMLDocument::get_body()
    {
        HTMLElement *html_element;

        for(auto &node : m_root->get_nodes())
            if(node->get_name() == "html")
            {
                html_element = reinterpret_cast<HTMLElement*>(node.get());
                break;
            }

        if(!html_element)
            return nullptr;

        for(auto &node : html_element->get_nodes())
            if(node->get_name() == "body")
                return reinterpret_cast<HTMLElement*>(node.get());

        return nullptr;
    }

    std::vector<HTMLElement*> HTMLDocument::get_elements_by_tag_name(std::string tag_name)
    {
        HTMLNode *root = m_root.get();

        std::vector<HTMLElement*> elements;

        for(auto &node : root->get_nodes())
        {
            if(node.get()->get_type() != XML::NodeType::Element)
                continue;

            HTMLElement *node_element = reinterpret_cast<HTMLElement*>(node.get());
            std::vector<HTMLElement*> node_elements = node_element->get_elements_by_tag_name(tag_name);

            elements.insert(elements.end(), node_elements.begin(), node_elements.end());
        }

        return elements;
    }

    void HTMLDocument::set_lang(std::string lang)
    {
        //m_lang = lang;
    }

    std::string HTMLDocument::get_lang()
    {
        return "";
    }

    void HTMLDocument::load_style_sheets()
    {
        std::vector<HTMLElement*> elements = get_elements_by_tag_name("style");

        for(auto &element : elements)
        {
            CSS::CSSDocument *document = new CSS::CSSDocument();
            document->parse(element->get_text_content(), true);
        }
    }

    void HTMLDocument::draw(const Cairo::RefPtr<Cairo::Context>& cr)
    {
        m_root->draw(cr);
    }

    HTMLDocument::~HTMLDocument()
    {
    }
}