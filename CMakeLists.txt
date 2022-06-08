cmake_minimum_required(VERSION 3.0.0)
project(aula1_exercicio1 VERSION 0.1.0)

add_library(lib 
lib/dbClient.c
lib/utils.c
lib/menus.c
lib/authService.c
)

add_executable(aula1_exercicio1 aula1exer1_EduardoFarias_190086521.c)

target_link_libraries(aula1_exercicio1 lib)