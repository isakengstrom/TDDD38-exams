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


# Part I

add_executable( executable0 forms.cc )
enable_warnings( executable0 )

# Part II


# Part III
#add_executable( assignment1 assignment1.cc )
#enable_warnings( assignment1 )

#add_executable( assignment2 assignment2.cc )
#enable_warnings( assignment2 )

