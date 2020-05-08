cmake_minimum_required(VERSION 3.15)
project(Lab_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_3
        main.c
        repo.c
        UI.c UI.h repo.h domain.h controller.h controller.c domain.c tests.c tests.h)
