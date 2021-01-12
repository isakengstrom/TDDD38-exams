# TDDD38-exams
Previous exam files and solutions for the course [Advanced programming in C++ (TDDD38)](https://www.ida.liu.se/~TDDD38/) at LiU. 

This repo was created to simplify the process of downloading the exam files. It is a somewhat faster process to clone this repo, than to download each file separatly.

The repo contains two folders:

- [exams_cmake](exams_cmake/) - Contains the given files and solutions to the exams of the course, with ready to use Cmake configurations.
- [exams_raw](exams_raw/) - Just the files, no BS

<br />

## exams_cmake - CMakeLists.txt example
(Note that this configuration may not be up to date, but it can hopefully be used as a reference in that case)
```cmake
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

## Create separate executables, the following example is from "exam_200603"
add_executable( executable0 json.cc )
enable_warnings( executable0 )

add_executable( executable1 assignment1.cc )
enable_warnings( executable1 )

add_executable( executable2 assignment2.cc )
enable_warnings( executable2 )
```