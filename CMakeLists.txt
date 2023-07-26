cmake_minimum_required(VERSION 3.10)

project(snake)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src/gif)

add_executable( 
	${CMAKE_PROJECT_NAME}
	src/main.c
	src/menu/menu.c
	src/sigterm/sigterm.c
	src/snake/snake.c
)

find_package(Curses REQUIRED)

target_include_directories(
	${CMAKE_PROJECT_NAME} PRIVATE
	${CURSES_INCLUDE_DIR}
	inc/gif/
	inc/menu/
	inc/sigterm/
	inc/snake/
)

target_link_libraries(
	${CMAKE_PROJECT_NAME} PRIVATE
 	${CURSES_LIBRARIES}
	gif
)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -lncurses)
        message("GCC IS USING")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
       	target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Weverything -Wno-disabled-macro-expansion) 
	message("CLANG IS USING")
endif()


