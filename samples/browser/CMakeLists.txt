project(Browser)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

add_executable(Browser main.cpp BrowserWindow.cpp BrowserWidget.cpp)

target_link_directories(Browser PUBLIC ${GTKMM_LIBRARY_DIRS})
target_include_directories(Browser PUBLIC ${GTKMM_INCLUDE_DIRS})
target_link_libraries(Browser ${GTKMM_LIBRARIES} HTMLEngine)