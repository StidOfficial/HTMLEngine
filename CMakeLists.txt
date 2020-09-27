cmake_minimum_required(VERSION 3.0.0)
project(HTMLEngine VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(HTMLEngine src/HTMLEngine.cpp
    src/URI.cpp
    src/WebView.cpp
    src/CSS/CSSDocument.cpp
    src/HTML/Elements/HTMLElementH1.cpp
    src/HTML/HTMLCDATA.cpp
    src/HTML/HTMLComment.cpp
    src/HTML/HTMLDocument.cpp
    src/HTML/HTMLElement.cpp
    src/HTML/HTMLNode.cpp
    src/HTML/HTMLText.cpp
    src/HTML/HTMLWhitespace.cpp
    src/XML/XMLCDATA.cpp
    src/XML/XMLComment.cpp
    src/XML/XMLElement.cpp
    src/XML/XMLNode.cpp
    src/XML/XMLText.cpp
    src/XML/XMLWhitespace.cpp)

find_package(PkgConfig REQUIRED)

# Cairomm
pkg_check_modules(Cairomm REQUIRED cairomm-1.0)
include_directories(${Cairomm_INCLUDE_DIRS})
target_link_libraries(HTMLEngine ${Cairomm_LIBRARIES})

# CURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(HTMLEngine ${CURL_LIBRARIES})

# Gumbo Parser (unused currently)
target_link_libraries(HTMLEngine gumbo)

# Boost
find_package(Boost 1.69.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(HTMLEngine ${Boost_LIBRARIES})

# HTMLEngine
include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(samples)