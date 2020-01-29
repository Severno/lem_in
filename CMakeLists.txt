cmake_minimum_required(VERSION 3.15)
project(lem_in)

set(CMAKE_CXX_STANDARD 14)

add_executable(lem_in
        author
        README.md src/get_info.c includes/lem_in.h src/lem_in.c src/read_map.c)

target_link_libraries(lem_in ${CMAKE_SOURCE_DIR}/libft/libft.a)
