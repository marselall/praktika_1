cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Pac_man)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_definitions(-DSFML_STATIC)

include_directories("SFML-2.6.1/include")
link_directories("SFML-2.6.1/lib")

add_executable("${PROJECT_NAME}" pac_man.cpp "map.hpp" "Enemy.hpp" "Entity.hpp" "Player.hpp")

target_link_libraries("${PROJECT_NAME}" sfml-graphics-s-d
						  sfml-window-s-d
						  sfml-system-s-d
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s-d
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)
file(COPY "src" DESTINATION "/") 