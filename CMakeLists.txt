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

target_link_libraries(pavage_text tools)
target_link_libraries(pavage_test tools)

add_library(tools tools.c)
#les dépendances sont calculées automatiquement
#----------------------------------------#

#------ AJOUT DES TESTS ------#
#add_test(pavage_test_clear ./pavage_test clear)
#-----------------------------#