#include <htmlengine/URI.hpp>

#include <map>

#include <iostream>

namespace HTMLEngine
{
    URI::URI()
        : m_port(0)
    {
    }

    URI::URI(std::string uri)
        : URI()
    {
        if(uri.length() == 0)
            return;

        m_uri = uri;

        std::size_t scheme_component_pos = uri.find(":");
        std::size_t authority_component_pos;
        if(scheme_component_pos != std::string::npos)
        {
            m_scheme  = uri.substr(0, scheme_component_pos);
            authority_component_pos = uri.find("//", scheme_component_pos + 1);
        }
        else
            authority_component_pos = uri.find("//");

        std::size_t path_component_pos;
        if(authority_component_pos != std::string::npos)
            path_component_pos = uri.find("/", authority_component_pos + 2);
        else if(scheme_component_pos != std::string::npos)
            path_component_pos = scheme_component_pos + 1;
        else
            path_component_pos = 0;

        // Authority block
        if(authority_component_pos != std::string::npos)
        {
            std::size_t userinfo_component_pos = uri.find("@", authority_component_pos + 2);
            std::size_t port_component_pos;
            if(userinfo_component_pos != std::string::npos)
                port_component_pos = uri.find(":", userinfo_component_pos + 1);
            else
                port_component_pos = uri.find(":", authority_component_pos + 2);

            if(port_component_pos > path_component_pos)
                port_component_pos = std::string::npos;

            if(userinfo_component_pos != std::string::npos)
                m_userinfo = uri.substr(authority_component_pos + 2, userinfo_component_pos - (authority_component_pos + 2));

            if(userinfo_component_pos != std::string::npos && port_component_pos != std::string::npos)
                m_host = uri.substr(userinfo_component_pos + 1, port_component_pos - (userinfo_component_pos + 1));
            else if(userinfo_component_pos != std::string::npos)
                m_host = uri.substr(userinfo_component_pos + 1, path_component_pos - (userinfo_component_pos + 1));
            else if(port_component_pos != std::string::npos)
                m_host = uri.substr(authority_component_pos + 2, port_component_pos - (authority_component_pos + 2));
            else
                m_host = uri.substr(authority_component_pos + 2, path_component_pos - (authority_component_pos + 2));

            if(port_component_pos != std::string::npos)
                try
                {
                    m_port = std::stoi(uri.substr(port_component_pos + 1, path_component_pos - (port_component_pos + 1)));
                }
                catch(std::exception e)
                {
                    throw uri_invalid_port();
                }
        }

        // If no path, skip
        if(path_component_pos == std::string::npos)
            return;

        std::size_t query_component_pos = uri.find("?", path_component_pos);
        std::size_t fragment_component_pos;
        if(query_component_pos != std::string::npos)
            fragment_component_pos = uri.find("#", query_component_pos + 1);
        else
            fragment_component_pos = uri.find("#", path_component_pos);

        if(query_component_pos != std::string::npos)
            m_path = uri.substr(path_component_pos, query_component_pos - path_component_pos);
        else if(fragment_component_pos != std::string::npos)
            m_path = uri.substr(path_component_pos, fragment_component_pos - path_component_pos);
        else
            m_path = uri.substr(path_component_pos);

        if(query_component_pos != std::string::npos)
            if(fragment_component_pos != std::string::npos)
                m_query = uri.substr(query_component_pos + 1, fragment_component_pos - (query_component_pos + 1));
            else
                m_query = uri.substr(query_component_pos + 1);

        if(fragment_component_pos != std::string::npos)
            m_fragment = uri.substr(fragment_component_pos + 1);
    }

    URI::operator const std::string()
    {
        return m_uri;
    }

    URI::operator const char*()
    {
        return m_uri.c_str();
    }

    void URI::set_scheme(std::string scheme)
    {
        m_scheme = scheme;
    }

    std::string URI::get_scheme()
    {
        return m_scheme;
    }
    void URI::set_userinfo(std::string userinfo)
    {
        m_userinfo = userinfo;
    }

    std::string URI::get_userinfo()
    {
        return m_userinfo;
    }

    void URI::set_host(std::string host)
    {
        m_host = host;
    }

    std::string URI::get_host()
    {
        return m_host;
    }

    void URI::set_port(uint16_t port)
    {
        m_port = port;
    }

    uint16_t URI::get_port()
    {
        return m_port;
    }

    void URI::set_path(std::string path)
    {
        m_path = path;
    }

    std::string URI::get_path()
    {
        return m_path;
    }

    void URI::set_query(std::string query)
    {
        m_query = query;
    }

    std::string URI::get_query()
    {
        return m_query;
    }

    void URI::set_fragment(std::string fragment)
    {
        m_fragment = fragment;
    }

    std::string URI::get_fragment()
    {
        return m_fragment;
    }

    URI::~URI()
    {

    }
}
