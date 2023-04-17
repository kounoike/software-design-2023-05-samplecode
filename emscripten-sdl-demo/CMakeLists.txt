cmake_minimum_required(VERSION 3.23)
project(sdl-demo LANGUAGES CXX)

add_executable(sdl-demo src/main.cpp)
target_compile_options(sdl-demo PRIVATE
  "SHELL:-s USE_SDL=2"
  "SHELL:-s USE_SDL_MIXER=2"
)
target_link_options(sdl-demo PRIVATE
  "SHELL:-s USE_SDL=2"
  "SHELL:-s USE_SDL_MIXER=2"
  "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/BGM.mp3@/BGM.mp3"
)
set_property(TARGET sdl-demo PROPERTY SUFFIX .html)
