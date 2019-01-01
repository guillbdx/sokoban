cmake_minimum_required(VERSION 3.12)
project(sokoban_c C)
set(CMAKE_C_STANDARD 99)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(Freetype REQUIRED)
find_package(SDL_ttf REQUIRED)
include_directories(${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS})

set(MAIN main.c)

file(GLOB GRIDS ${PROJECT_SOURCE_DIR}/Assets/*)
file(COPY ${GRIDS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Assets
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_WRITE GROUP_READ WORLD_READ)

add_executable(sokoban_c main.c Model/model.h Service/prompt.h Service/prompt.c Model/grid.c Model/grid.h View/view.c View/view.h Service/game.c Service/game.h Model/move.c Model/move.h)

target_link_libraries(sokoban_c ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES} ${FREETYPE_LIBRARIES} ${SDL_TTF_LIBRARIES})