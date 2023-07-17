cmake_minimum_required(VERSION 3.10)

project(snake)

set(CMAKE_C_STANDARD 99)


add_executable( 
	${CMAKE_PROJECT_NAME}
	src/main.c
	src/gif/gifdec.c
)


target_include_directories(
	${CMAKE_PROJECT_NAME} PRIVATE
	inc/gif/
)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)
        message("GCC IS USING")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
       	target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Weverything -Wno-disabled-macro-expansion) 
	message("CLANG IS USING")
endif()


