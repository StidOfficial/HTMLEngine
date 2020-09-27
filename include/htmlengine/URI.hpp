#pragma once

#include <string>
#include <exception>

namespace HTMLEngine
{
    struct uri_invalid_port : public std::exception
    {
        const char* what() const throw()
        {
            return "Invalid port value";
        }
    };

    class URI
    {
    public:
        URI();
        URI(std::string uri);
        ~URI();

        operator const std::string();
        operator const char*();

        void set_scheme(std::string scheme);
        std::string get_scheme();
        void set_userinfo(std::string userinfo);
        std::string get_userinfo();
        void set_host(std::string host);
        std::string get_host();
        void set_port(uint16_t port);
        uint16_t get_port();
        void set_path(std::string path);
        std::string get_path();
        void set_query(std::string query);
        std::string get_query();
        void set_fragment(std::string fragment);
        std::string get_fragment();
    protected:
        std::string m_uri;
        std::string m_scheme;
        std::string m_userinfo;
        std::string m_host;
        uint16_t m_port;
        std::string m_path;
        std::string m_query;
        std::string m_fragment;
    };
}
