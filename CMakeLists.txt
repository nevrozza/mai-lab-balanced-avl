cmake_minimum_required(VERSION 4.1)
project(avl C)

set(CMAKE_C_STANDARD 17)

add_executable(avl main.c
        parser/parser.c
        parser/parser.h
        avl/avl.c
        avl/avl.h
        avl/avl_utils.c
        avl/avl_utils.h
        utils/utils.c
        utils/utils.h
        cli/cli.c
        cli/cli.h
        avl/avl_handlers.c
        avl/avl_handlers.h
)
