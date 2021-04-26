#version minimale de cmake nécessaire
cmake_minimum_required(VERSION 2.6)

#nom du projet
project (Pavage C)

#activation des tests
enable_testing()
include(CTest)

#positionne la variable
set(CMAKE_C_FLAGS "-O0 -std=c99 -g -Wall --coverage")

#------ EXECUTABLES ET BIBLIOTHEQUE ------#
add_executable(pavage_text pavage_text.c)
add_executable(pavage_test pavage_test.c)

target_link_libraries(pavage_text pavage)
target_link_libraries(pavage_test pavage)

add_library(pavage coordinate.c hash_table.c pavage.c)
#les dépendances sont calculées automatiquement
#----------------------------------------#

#------ AJOUT DES TESTS ------#
add_test(test_coordinate_new ./pavage_test coordinate_new)
add_test(test_coordinate_is_equal ./pavage_test coordinate_is_equal)
add_test(test_coordinate_delete ./pavage_test coordinate_delete)
add_test(test_hash_new ./pavage_test hash_new)
add_test(test_hash_print ./pavage_test hash_print)
add_test(test_hash_add ./pavage_test hash_add)
add_test(test_hash_search ./pavage_test hash_search)
add_test(test_hash_delete ./pavage_test hash_delete)
#-----------------------------#