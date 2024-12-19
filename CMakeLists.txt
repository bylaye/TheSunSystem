cmake_minimum_required(VERSION 3.28)


project(SunSystem)


# sources files
set(
    SOURCES 
    src/main.cpp 
)

include_directories(include)


add_executable(SunSystem ${SOURCES})


find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)
target_link_libraries(SunSystem sfml-graphics sfml-window sfml-system)
