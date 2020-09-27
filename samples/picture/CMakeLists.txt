project(Picture)

#find_package(PkgConfig)
#pkg_check_modules(GTKMM gtkmm-3.0)

add_executable(Picture main.cpp)

#target_link_directories(Picture PUBLIC ${GTKMM_LIBRARY_DIRS})
#target_include_directories(Picture PUBLIC ${GTKMM_INCLUDE_DIRS})
target_link_libraries(Picture HTMLEngine)