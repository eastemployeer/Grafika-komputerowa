cmake_minimum_required(VERSION 3.17)
project(grafika_jajko_zad3)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.



add_executable(grafika_jajko_zad3 main.cpp)

target_link_libraries(grafika_jajko_zad3 ${OpenGlLinkers}) # linking opengl libraries to the project