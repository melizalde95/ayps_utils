# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/cuau/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/cuau/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug

# Include any dependencies generated for this target.
include src/executables/examples/CMakeFiles/ex_serial.dir/depend.make

# Include the progress variables for this target.
include src/executables/examples/CMakeFiles/ex_serial.dir/progress.make

# Include the compile flags for this target's objects.
include src/executables/examples/CMakeFiles/ex_serial.dir/flags.make

src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o: src/executables/examples/CMakeFiles/ex_serial.dir/flags.make
src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o: ../src/executables/examples/serial_port.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o"
	cd /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/src/executables/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex_serial.dir/serial_port.cpp.o -c /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/src/executables/examples/serial_port.cpp

src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex_serial.dir/serial_port.cpp.i"
	cd /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/src/executables/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/src/executables/examples/serial_port.cpp > CMakeFiles/ex_serial.dir/serial_port.cpp.i

src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex_serial.dir/serial_port.cpp.s"
	cd /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/src/executables/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/src/executables/examples/serial_port.cpp -o CMakeFiles/ex_serial.dir/serial_port.cpp.s

src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.requires:

.PHONY : src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.requires

src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.provides: src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.requires
	$(MAKE) -f src/executables/examples/CMakeFiles/ex_serial.dir/build.make src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.provides.build
.PHONY : src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.provides

src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.provides.build: src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o


# Object files for target ex_serial
ex_serial_OBJECTS = \
"CMakeFiles/ex_serial.dir/serial_port.cpp.o"

# External object files for target ex_serial
ex_serial_EXTERNAL_OBJECTS =

src/executables/examples/ex_serial: src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o
src/executables/examples/ex_serial: src/executables/examples/CMakeFiles/ex_serial.dir/build.make
src/executables/examples/ex_serial: src/core/liblib_core.a
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_system.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_thread.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_system.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_thread.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
src/executables/examples/ex_serial: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
src/executables/examples/ex_serial: src/executables/examples/CMakeFiles/ex_serial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex_serial"
	cd /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/src/executables/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex_serial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/executables/examples/CMakeFiles/ex_serial.dir/build: src/executables/examples/ex_serial

.PHONY : src/executables/examples/CMakeFiles/ex_serial.dir/build

src/executables/examples/CMakeFiles/ex_serial.dir/requires: src/executables/examples/CMakeFiles/ex_serial.dir/serial_port.cpp.o.requires

.PHONY : src/executables/examples/CMakeFiles/ex_serial.dir/requires

src/executables/examples/CMakeFiles/ex_serial.dir/clean:
	cd /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/src/executables/examples && $(CMAKE_COMMAND) -P CMakeFiles/ex_serial.dir/cmake_clean.cmake
.PHONY : src/executables/examples/CMakeFiles/ex_serial.dir/clean

src/executables/examples/CMakeFiles/ex_serial.dir/depend:
	cd /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/src/executables/examples /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/src/executables/examples /home/cuau/Documentos/procesamiento_senales/DistPipelineFWK/cmake-build-debug/src/executables/examples/CMakeFiles/ex_serial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/executables/examples/CMakeFiles/ex_serial.dir/depend
