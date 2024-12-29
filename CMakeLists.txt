cmake_minimum_required(VERSION 2.8.9)
project (lc3)

set(SOURCE_FILES
    utils.c
    core.c
    instruction_set.c
    lc3.c)

add_executable(lc3 ${SOURCE_FILES})
