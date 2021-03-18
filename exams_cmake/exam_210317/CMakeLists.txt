cmake_minimum_required(VERSION 3.13.0...3.19.0) # CMake version  
project(Exam VERSION 1.0.0 DESCRIPTION "No description provided." LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make sure that the correct flags are provided to the compiler here:
function(enable_warnings target) 
	target_compile_options(${target} PUBLIC 
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
		$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra -Wconversion>
	)
endfunction()

# Part I
add_executable( executable0 event.cc )
enable_warnings( executable0 )

# Part II


# Part III
add_executable( assignment1 assignment1.cc )
enable_warnings( assignment1 )

add_executable( assignment2 assignment2.cc )
enable_warnings( assignment2 )