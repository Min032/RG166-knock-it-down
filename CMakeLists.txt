cmake_minimum_required(VERSION 3.16.3)
project(KnockItDown VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_compile_options(-g -Wall -Wextra -Wno-unused-parameter -I/usr/X11R6/include -I/usr/pkg/include -L/usr/X11R6/lib -L/usr/pkg/lib -lglut -lGLU -lGL -lm)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=.*;
    -checks=-*,clang-analyzer-*,cppcoreguidelines-*,hicpp-*,modernize-*,google-*,misc-*;
    -fix;
    -quiet;)

set (SRC_LIST 
    main.cpp
    libs/callbackFunctions.hpp
    libs/callbackFunctions.cpp
    libs/helperFunctions.hpp
    libs/helperFunctions.cpp
    libs/shapes.hpp
    libs/shapes.cpp
    libs/image.hpp
    libs/image.cpp
)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/libs)
add_subdirectory(libs)

add_executable(game ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_libraries(shapes ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} helper_functions image)
target_link_libraries(callback_functions ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} helper_functions shapes)
target_link_libraries(game ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} image helper_functions shapes callback_functions)