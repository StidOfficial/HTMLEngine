#pragma once

#include <htmlengine/XML/XMLNode.hpp>

#include <string>
#include <memory>
#include <cctype>
#include <map>
#include <algorithm>

#include <iostream>

namespace HTMLEngine::XML
{
    template<class T, class TE, class TT, class TCD, class TC, class TW>
    class XMLDocument
    {
    public:
        XMLDocument()
        {
        }
        virtual ~XMLDocument()
        {
        }

        void parse(std::string text, bool clear)
        {
            if(clear)
                m_root.release();

            m_root = std::unique_ptr<T>(XMLDocument<T, TE, TT, TCD, TC, TW>::parse(text));
        }

        T *get_root()
        {
            return m_root.get();
        }
    protected:
        std::unique_ptr<T> m_root;

    private:
        static T *parse(std::string text)
        {
            T *root = new T(NodeType::Root);
            T *current_node = root;

            bool is_begin_tag = false;
            bool is_tag_name = false;
            bool is_tag_quoted = false;
            bool is_tag_attribute_key = false;
            bool is_tag_attribute_value = false;

            bool is_end_tag = false;

            bool is_section = false;
            bool is_comment = false;

            std::string tag_name = "";
            std::string tag_attribute_key = "";
            std::string tag_attribute_value = "";
            std::map<std::string, std::string> tag_attributes;
            std::string tag_content = "";

            std::string last_value = "";
            for(int i = 0; i < text.length(); i++)
            {
                char character = text.at(i);
                char next_chararacter;
                if(i + 1 < text.length())
                    next_chararacter = text.at(i + 1);

                
                if(is_begin_tag && !is_tag_quoted && character == '"')
                {
                    is_tag_quoted = true;

                    continue;
                }
                else if(is_tag_quoted && character == '"')
                {
                    is_tag_quoted = false;

                    continue;
                }
                else if(!is_begin_tag && !is_end_tag && !is_section && character == '<')
                {
                    TE* current_element;
                    std::string current_element_tag_name;

                    if(!TE::support_content(current_node->get_name()))
                    {
                        current_node = current_node->get_parent();
                    }
                    
                    if(!last_value.empty() && std::count_if(last_value.begin(), last_value.end(), [](unsigned char c) {
                        return std::isspace(c);
                    }) == last_value.length())
                    {
                        TW *new_node = new TW();
                        new_node->set_value(last_value);

                        current_node->append(new_node);

                        last_value = "";
                    }

                    //std::cout << current_node->get_name() << " - " << TE::support_child_element(current_node->get_name()) << std::endl;
                    if(TE::support_child_element(current_node->get_name()) && std::isalpha(next_chararacter))
                    {
                        is_begin_tag = true;
                        is_tag_name = true;

                        if(!last_value.empty())
                        {
                            TT *new_node = new TT();
                            new_node->set_value(last_value);

                            current_node->append(new_node);
                        }

                        last_value = "";

                        // Skip next character
                        continue;
                    }
                    else if(next_chararacter == '/')
                    {
                        std::string tag_name = text.substr(i + 2, current_node->get_name().length());

                        if(current_node->get_name() == tag_name)
                        {
                            is_end_tag = true;

                            tag_content = last_value;
                            last_value = "";

                            // Skip next characters
                            i++;
                            continue;
                        }
                    }
                    else if(TE::support_child_element(current_node->get_name()) && next_chararacter == '!')
                    {
                        is_section = true;

                        //std::cout << "Start section" << std::endl;

                        // Skip next characters
                        i++;
                        continue;
                    }

                    if((is_begin_tag || is_section) && !last_value.empty())
                    {
                        std::cout << "Value : " << last_value << std::endl;
                        last_value = "";
                    }
                }
                else if(is_begin_tag && character == '/')
                {
                    if(next_chararacter == '>')
                    {
                        if(!tag_attribute_key.empty())
                        {
                            tag_attribute_value = last_value;
                            last_value = "";

                            tag_attributes.insert(std::pair<std::string, std::string>(tag_attribute_key, tag_attribute_value));
                        }

                        TE* new_node = new TE();
                        new_node->set_name(tag_name);

                        for(auto &attribute : tag_attributes)
                            new_node->add_attribute(attribute.first, attribute.second);

                        current_node->append(new_node);

                        is_begin_tag = false;

                        tag_name = "";
                        tag_attribute_key = "";
                        tag_attribute_value = "";
                        tag_attributes.clear();
                        tag_content = "";
                        last_value = "";

                        // Skip next characters
                        i++;
                        continue;
                    }
                }
                else if(is_begin_tag && !is_tag_name && is_tag_attribute_key && character == '=')
                {
                    is_tag_attribute_key = false;
                    is_tag_attribute_value = true;

                    tag_attribute_key = last_value;
                    last_value = "";

                    continue;
                }
                else if((is_begin_tag || is_end_tag || is_section) && character == '>')
                {
                    TE *current_element = reinterpret_cast<TE*>(current_node);
                    if(is_begin_tag)
                    {
                        if(tag_name.empty())
                        {
                            tag_name = last_value;
                            last_value = "";
                        }

                        if(!tag_attribute_key.empty() || !last_value.empty())
                        {
                            if(!tag_attribute_key.empty())
                                tag_attribute_value = last_value;
                            else
                                tag_attribute_key = last_value;

                            last_value = "";

                            tag_attributes.insert(std::pair<std::string, std::string>(tag_attribute_key, tag_attribute_value));
                        }

                        TE* new_node = new TE();
                        new_node->set_name(tag_name);

                        for(auto &attribute : tag_attributes)
                            new_node->add_attribute(attribute.first, attribute.second);

                        current_node->append(new_node);

                        current_node = reinterpret_cast<T*>(new_node);
                    }
                    else if(is_end_tag)
                    {
                        TT *node_text = new TT();
                        node_text->set_value(tag_content);

                        current_node->append(node_text);

                        last_value = "";

                        current_node = current_node->get_parent();
                    }
                    else if(is_section)
                    {
                        //std::cout << "create section" << std::endl;

                        last_value = "";
                    }
                    else
                    {
                        std::cout << "lol" << std::endl;
                        //current_node = current_node->get_parent();
                    }

                    //std::cout << "Last value : " << is_end_tag << " - " << tag_name << " : " << tag_content << " : " << last_value << std::endl;

                    is_begin_tag = false;
                    is_end_tag = false;
                    is_section = false;

                    tag_name = "";
                    tag_attribute_key = "";
                    tag_attribute_value = "";
                    tag_attributes.clear();
                    tag_content = "";
                    last_value = "";

                    continue;
                }
                else if(is_begin_tag && is_tag_name && character == ' ')
                {
                    tag_name = last_value;
                    last_value = "";

                    is_tag_name = false;
                    is_tag_attribute_key = true;
                    is_tag_attribute_value = false;

                    continue;
                }
                else if(is_begin_tag && !is_tag_name && character == ' ')
                {
                    if(is_tag_attribute_key)
                    {
                        continue;
                    }
                    else if(is_tag_attribute_value)
                    {
                        tag_attribute_value = last_value;
                        last_value = "";
                    }

                    tag_attributes.insert(std::pair<std::string, std::string>(tag_attribute_key, tag_attribute_value));

                    tag_attribute_key = "";
                    tag_attribute_value = "";

                    is_tag_attribute_key = true;
                    is_tag_attribute_value = false;

                    continue;
                }

                last_value += character;
            }

            //std::cout << "End Last value : " << last_value << std::endl;

            return root;
        }
    };
}