# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\build

# Include any dependencies generated for this target.
include CMakeFiles/ex3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex3.dir/flags.make

CMakeFiles/ex3.dir/main.cpp.obj: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/main.cpp.obj: CMakeFiles/ex3.dir/includes_CXX.rsp
CMakeFiles/ex3.dir/main.cpp.obj: C:/Users/Ian/Desktop/IT360/OpenGL_Crowd_Sim_C++/ex3/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex3.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ex3.dir\main.cpp.obj -c C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\src\main.cpp

CMakeFiles/ex3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex3.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\src\main.cpp > CMakeFiles\ex3.dir\main.cpp.i

CMakeFiles/ex3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex3.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\src\main.cpp -o CMakeFiles\ex3.dir\main.cpp.s

# Object files for target ex3
ex3_OBJECTS = \
"CMakeFiles/ex3.dir/main.cpp.obj"

# External object files for target ex3
ex3_EXTERNAL_OBJECTS =

ex3.exe: CMakeFiles/ex3.dir/main.cpp.obj
ex3.exe: CMakeFiles/ex3.dir/build.make
ex3.exe: CMakeFiles/ex3.dir/linklibs.rsp
ex3.exe: CMakeFiles/ex3.dir/objects1.rsp
ex3.exe: CMakeFiles/ex3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ex3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex3.dir/build: ex3.exe

.PHONY : CMakeFiles/ex3.dir/build

CMakeFiles/ex3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ex3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ex3.dir/clean

CMakeFiles/ex3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\src C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\src C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\build C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\build C:\Users\Ian\Desktop\IT360\OpenGL_Crowd_Sim_C++\ex3\build\CMakeFiles\ex3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex3.dir/depend

