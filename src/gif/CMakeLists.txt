cmake_minimum_required(VERSION 3.10)

set(INC_DIRS
	../../inc/gif/

)

add_library(gif STATIC
	./gifdec.c
	
)

target_compile_options(gif PRIVATE -Wall)
target_include_directories(gif PUBLIC ${INC_DIRS})
