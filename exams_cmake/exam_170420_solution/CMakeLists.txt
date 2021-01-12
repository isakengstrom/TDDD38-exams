cmake_minimum_required(VERSION 3.13.0...3.18.1)
project(Exam VERSION 1.0.0 DESCRIPTION "No description provided." LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
	target_compile_options(${target} PUBLIC 
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
		$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra -Wconversion>
	)
endfunction()

include_directories(include)

## Add all files with related extensions to solution

# file(GLOB_RECURSE sources  *.c* *.h* *.m src/*.c* src/*.h* src/*.m include/*.h* libs/*.c* libs/*.h* test/*.c* test/*.h*)
# add_executable( ${PROJECT_NAME} ${sources} )
# enable_warnings( ${PROJECT_NAME} )


## Create separate executables 

#add_executable( executable1 <filename> )
#enable_warnings( executable1 )

add_executable( executable6 program6.cc )
enable_warnings( executable6 )

add_executable( executable7 program7.cc )
enable_warnings( executable7 )

add_executable( executable8_1 program8_1.cc )
enable_warnings( executable8_1 )

add_executable( executable8_2 program8_2.cc )
enable_warnings( executable8_2 )

add_executable( executable8_3 program8_3.cc )
enable_warnings( executable8_3 )

add_executable( executable9 program9.cc )
enable_warnings( executable9 )

#add_executable( executable6 <filename> )
#enable_warnings( executable6 )


