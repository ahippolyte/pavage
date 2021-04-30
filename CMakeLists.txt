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

add_library(pavage point.c hash_table.c pavage.c queue.c)
#les dépendances sont calculées automatiquement
#----------------------------------------#

#------ AJOUT DES TESTS ------#
add_test(test_point_new ./pavage_test point_new)
add_test(test_point_is_equal ./pavage_test point_is_equal)

add_test(test_hash_new ./pavage_test hash_new)
add_test(test_hash_print ./pavage_test hash_print)
add_test(test_hash_add ./pavage_test hash_add)
add_test(test_hash_search ./pavage_test hash_search)

add_test(test_queue_new ./pavage_test queue_new)
add_test(test_queue_print ./pavage_test queue_print)
add_test(test_queue_enqueue ./pavage_test queue_enqueue)
add_test(test_queue_dequeue ./pavage_test queue_dequeue)
add_test(test_queue_is_empty ./pavage_test queue_is_empty)
add_test(test_queue_peek ./pavage_test queue_peek)
#-----------------------------#