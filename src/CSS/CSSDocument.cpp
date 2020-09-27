#include <htmlengine/CSS/CSSDocument.hpp>

#include <iostream>
#include <boost/algorithm/string.hpp>

namespace HTMLEngine::CSS
{
    CSSDocument::CSSDocument()
    {

    }

    void CSSDocument::parse(std::string text, bool clear)
    {
        bool is_group_selectors = true;
        bool is_block = false;
        bool is_rule = false;

        std::vector<std::string> selectors;

        std::string declaration_property = "";
        std::string declaration_value = "";

        std::string last_value = "";
        for(int i = 0; i < text.length(); i++)
        {
            char character = text.at(i);

            if(is_group_selectors && character == ',')
            {
                clean_selector(last_value);
                std::cout << last_value << std::endl;

                last_value = "";

                continue;
            }
            else if(is_group_selectors && character == '{')
            {
                is_group_selectors = false;
                is_block = true;

                clean_selector(last_value);
                std::cout << last_value << std::endl;

                last_value = "";

                continue;
            }
            else if(is_block && character == ':')
            {
                declaration_property = last_value;

                last_value = "";

                continue;
            }
            else if(is_block && character == ';')
            {
                declaration_value = last_value;

                last_value = "";

                continue;
            }
            
            last_value += character;
        }
    }

    CSSDocument::~CSSDocument()
    {
        
    }

    CSSDocument *CSSDocument::parse(std::string text)
    {
        return nullptr;
    }

    void CSSDocument::clean_selector(std::string selector)
    {
        selector.erase(std::remove(selector.begin(), selector.end(), '\n'), selector.end());
        selector.erase(std::remove(selector.begin(), selector.end(), '\r'), selector.end());
        boost::algorithm::trim(selector);
    }
}