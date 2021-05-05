#version minimale de cmake nécessaire
cmake_minimum_required(VERSION 2.6)

#nom du projet
project (Pavage C)

#activation des tests
enable_testing()
include(CTest)

#positionne la variable
set(CMAKE_C_FLAGS "-O0 -std=c99 -g -Wall")

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