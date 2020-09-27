#pragma once

#include <vector>
#include <memory>
#include <string>

namespace HTMLEngine::XML
{
    enum NodeType
    {
        Root,
        Element,
        Text,
        CDATA,
        Comment,
        Whitespace
    };

    class XMLNode
    {
    public:
        XMLNode(NodeType type);
        virtual ~XMLNode();

        virtual void set_name(std::string name);
        virtual std::string get_name();
        virtual NodeType get_type();
        virtual void set_parent(XMLNode *parent);
        virtual XMLNode *get_parent();
        virtual std::vector<std::shared_ptr<XMLNode>> get_nodes();
        virtual void append(XMLNode *element);
        virtual void clear();
        virtual void set_value(std::string value);
        virtual std::string get_value();
        virtual std::string to_string();
    protected:
        std::string m_name;
        NodeType m_type;
        XMLNode *m_parent;
        std::vector<std::shared_ptr<XMLNode>> m_nodes;
        std::string m_value;
    };
}