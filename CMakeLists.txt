#version minimale de cmake nécessaire
cmake_minimum_required(VERSION 2.6)

#nom du projet
project (Pavage C)

#activation des tests
enable_testing()
include(CTest)

#positionne la variable
set(CMAKE_C_FLAGS " -std=c99 -g -Wall")

#------------- SDL2 CONFIG ---------------#
## use pkgconfig to solve SDL2 dependencies (Linux only)
# include(FindPkgConfig) # pkg-config --list-all  | grep -i sdl2
# pkg_search_module(SDL2 REQUIRED sdl2)
# pkg_search_module(SDL2_IMG REQUIRED SDL2_image)
# pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
# set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES})
# set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS} ${SDL2_IMG_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

## use a CMake3 package to solve SDL2 dependencies
find_package(SDL2 REQUIRED)
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS})
set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} -lSDL2_ttf -lSDL2_image) # add extra SDL2 libraries

## print this 
message(STATUS "SDL2 include dir: ${SDL2_ALL_INC}")
message(STATUS "SDL2 all libraries: ${SDL2_ALL_LIBS}")

## compilation rules
include_directories(${SDL2_ALL_INC})
add_executable(model pavage_sdl.c model.c)
target_link_libraries(model ${SDL2_ALL_LIBS} m)
#----------------------------------------#

#------ EXECUTABLES ET BIBLIOTHEQUE ------#
add_executable(pavage_text pavage_text.c)
add_executable(pavage_test pavage_test.c)

add_library(pavage point.c cell.c hash_table.c heap.c pavage.c)

target_link_libraries(pavage_text pavage)
target_link_libraries(pavage_test pavage)
#les dépendances sont calculées automatiquement
#----------------------------------------#

#------ AJOUT DES TESTS ------#
add_test(test_point_new ./pavage_test point_new)
add_test(test_point_is_equal ./pavage_test point_is_equal)

add_test(test_cell_new ./pavage_test cell_new)
add_test(test_cell_is_equal ./pavage_test cell_is_equal)

add_test(test_hash_new ./pavage_test hash_new)
add_test(test_hash_print ./pavage_test hash_print)
add_test(test_hash_add ./pavage_test hash_add)
add_test(test_hash_search ./pavage_test hash_search)

add_test(test_heap_new ./pavage_test heap_new)
add_test(test_heap_print ./pavage_test heap_print)
add_test(test_heap_empty ./pavage_test heap_empty)
add_test(test_heap_add ./pavage_test heap_add)
add_test(test_heap_top ./pavage_test heap_top)
add_test(test_heap_pop ./pavage_test heap_pop)
#-----------------------------#