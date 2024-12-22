cmake_minimum_required(VERSION 3.28)


project(SunSystem)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

include_directories(include)

# sources files
set(
    SOURCES 
    src/main.cpp 
)

add_executable(SunSystem ${SOURCES})

target_link_libraries(SunSystem sfml-graphics sfml-window sfml-system)

configure_file(assets/arial.ttf COPYONLY)
