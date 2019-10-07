cmake_minimum_required (VERSION 2.6)
project (Nightmare3d)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_BUILD_TYPE Debug)
set(CORE_SOURCES pal.cpp img.cpp pal.h img.h)

add_executable(pal_loader ${CORE_SOURCES} palLoader.cpp) 
target_link_libraries(pal_loader ${SDL2_LIBRARIES})
add_executable(img_loader ${CORE_SOURCES} imgLoader.cpp) 
target_link_libraries(img_loader ${SDL2_LIBRARIES})
