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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\hanchong\CLionProjects\deque

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\hanchong\CLionProjects\deque\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/deque.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/deque.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/deque.dir/flags.make

CMakeFiles/deque.dir/code2.cpp.obj: CMakeFiles/deque.dir/flags.make
CMakeFiles/deque.dir/code2.cpp.obj: ../code2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\hanchong\CLionProjects\deque\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/deque.dir/code2.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\deque.dir\code2.cpp.obj -c C:\Users\hanchong\CLionProjects\deque\code2.cpp

CMakeFiles/deque.dir/code2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/deque.dir/code2.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanchong\CLionProjects\deque\code2.cpp > CMakeFiles\deque.dir\code2.cpp.i

CMakeFiles/deque.dir/code2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/deque.dir/code2.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanchong\CLionProjects\deque\code2.cpp -o CMakeFiles\deque.dir\code2.cpp.s

# Object files for target deque
deque_OBJECTS = \
"CMakeFiles/deque.dir/code2.cpp.obj"

# External object files for target deque
deque_EXTERNAL_OBJECTS =

deque.exe: CMakeFiles/deque.dir/code2.cpp.obj
deque.exe: CMakeFiles/deque.dir/build.make
deque.exe: CMakeFiles/deque.dir/linklibs.rsp
deque.exe: CMakeFiles/deque.dir/objects1.rsp
deque.exe: CMakeFiles/deque.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\hanchong\CLionProjects\deque\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable deque.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\deque.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/deque.dir/build: deque.exe

.PHONY : CMakeFiles/deque.dir/build

CMakeFiles/deque.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\deque.dir\cmake_clean.cmake
.PHONY : CMakeFiles/deque.dir/clean

CMakeFiles/deque.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\hanchong\CLionProjects\deque C:\Users\hanchong\CLionProjects\deque C:\Users\hanchong\CLionProjects\deque\cmake-build-debug C:\Users\hanchong\CLionProjects\deque\cmake-build-debug C:\Users\hanchong\CLionProjects\deque\cmake-build-debug\CMakeFiles\deque.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/deque.dir/depend

