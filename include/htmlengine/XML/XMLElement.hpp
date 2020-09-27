#pragma once

#include <htmlengine/XML/XMLNode.hpp>

#include <string>
#include <map>

namespace HTMLEngine::XML
{
    class XMLElement : public XMLNode
    {
    public:
        XMLElement();
        ~XMLElement();

        void add_attribute(std::string key, std::string value);
        std::string *get_attribute(std::string key);
        std::vector<XMLElement*> get_elements_by_tag_name(std::string tag_name);
        std::string get_text_content();

        virtual std::string to_string();

        static bool support_child_element(std::string tag_name);
        static bool support_content(std::string tag_name);
    protected:
        std::map<std::string, std::string> m_attributes;
    };
}