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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\super\CLionProjects\Pokemon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\super\CLionProjects\Pokemon\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Pokemon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Pokemon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Pokemon.dir/flags.make

CMakeFiles/Pokemon.dir/main.cpp.obj: CMakeFiles/Pokemon.dir/flags.make
CMakeFiles/Pokemon.dir/main.cpp.obj: CMakeFiles/Pokemon.dir/includes_CXX.rsp
CMakeFiles/Pokemon.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\super\CLionProjects\Pokemon\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Pokemon.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Pokemon.dir\main.cpp.obj -c C:\Users\super\CLionProjects\Pokemon\main.cpp

CMakeFiles/Pokemon.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pokemon.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\super\CLionProjects\Pokemon\main.cpp > CMakeFiles\Pokemon.dir\main.cpp.i

CMakeFiles/Pokemon.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pokemon.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\super\CLionProjects\Pokemon\main.cpp -o CMakeFiles\Pokemon.dir\main.cpp.s

# Object files for target Pokemon
Pokemon_OBJECTS = \
"CMakeFiles/Pokemon.dir/main.cpp.obj"

# External object files for target Pokemon
Pokemon_EXTERNAL_OBJECTS =

Pokemon.exe: CMakeFiles/Pokemon.dir/main.cpp.obj
Pokemon.exe: CMakeFiles/Pokemon.dir/build.make
Pokemon.exe: C:/Program\ Files\ (x86)/mingw-w64/i686-7.3.0-posix-dwarf-rt_v5-rev0/mingw32/lib/libsfml-graphics-d.a
Pokemon.exe: C:/Program\ Files\ (x86)/mingw-w64/i686-7.3.0-posix-dwarf-rt_v5-rev0/mingw32/lib/libsfml-window-d.a
Pokemon.exe: C:/Program\ Files\ (x86)/mingw-w64/i686-7.3.0-posix-dwarf-rt_v5-rev0/mingw32/lib/libsfml-system-d.a
Pokemon.exe: CMakeFiles/Pokemon.dir/linklibs.rsp
Pokemon.exe: CMakeFiles/Pokemon.dir/objects1.rsp
Pokemon.exe: CMakeFiles/Pokemon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\super\CLionProjects\Pokemon\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Pokemon.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Pokemon.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Pokemon.dir/build: Pokemon.exe

.PHONY : CMakeFiles/Pokemon.dir/build

CMakeFiles/Pokemon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Pokemon.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Pokemon.dir/clean

CMakeFiles/Pokemon.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\super\CLionProjects\Pokemon C:\Users\super\CLionProjects\Pokemon C:\Users\super\CLionProjects\Pokemon\cmake-build-debug C:\Users\super\CLionProjects\Pokemon\cmake-build-debug C:\Users\super\CLionProjects\Pokemon\cmake-build-debug\CMakeFiles\Pokemon.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Pokemon.dir/depend

