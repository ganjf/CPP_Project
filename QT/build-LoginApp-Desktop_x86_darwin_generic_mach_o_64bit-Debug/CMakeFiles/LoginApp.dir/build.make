# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ganjiefeng/Desktop/algorithm/LoginApp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug

# Include any dependencies generated for this target.
include CMakeFiles/LoginApp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LoginApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LoginApp.dir/flags.make

LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp: /Users/ganjiefeng/Desktop/algorithm/LoginApp/resource.qrc
LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp: CMakeFiles/LoginApp_autogen.dir/AutoRcc_resource_EWIEGA46WW_Info.json
LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp: /Users/ganjiefeng/Desktop/algorithm/LoginApp/img/login.svg
LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp: /Users/ganjiefeng/Qt5.14.2/5.14.2/clang_64/bin/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for resource.qrc"
	/usr/local/Cellar/cmake/3.17.3/bin/cmake -E cmake_autorcc /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles/LoginApp_autogen.dir/AutoRcc_resource_EWIEGA46WW_Info.json Debug

CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.o: CMakeFiles/LoginApp.dir/flags.make
CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.o: LoginApp_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.o -c /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/LoginApp_autogen/mocs_compilation.cpp

CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/LoginApp_autogen/mocs_compilation.cpp > CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.i

CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/LoginApp_autogen/mocs_compilation.cpp -o CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.s

CMakeFiles/LoginApp.dir/main.cpp.o: CMakeFiles/LoginApp.dir/flags.make
CMakeFiles/LoginApp.dir/main.cpp.o: /Users/ganjiefeng/Desktop/algorithm/LoginApp/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LoginApp.dir/main.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoginApp.dir/main.cpp.o -c /Users/ganjiefeng/Desktop/algorithm/LoginApp/main.cpp

CMakeFiles/LoginApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoginApp.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ganjiefeng/Desktop/algorithm/LoginApp/main.cpp > CMakeFiles/LoginApp.dir/main.cpp.i

CMakeFiles/LoginApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoginApp.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ganjiefeng/Desktop/algorithm/LoginApp/main.cpp -o CMakeFiles/LoginApp.dir/main.cpp.s

CMakeFiles/LoginApp.dir/mainwindow.cpp.o: CMakeFiles/LoginApp.dir/flags.make
CMakeFiles/LoginApp.dir/mainwindow.cpp.o: /Users/ganjiefeng/Desktop/algorithm/LoginApp/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LoginApp.dir/mainwindow.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoginApp.dir/mainwindow.cpp.o -c /Users/ganjiefeng/Desktop/algorithm/LoginApp/mainwindow.cpp

CMakeFiles/LoginApp.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoginApp.dir/mainwindow.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ganjiefeng/Desktop/algorithm/LoginApp/mainwindow.cpp > CMakeFiles/LoginApp.dir/mainwindow.cpp.i

CMakeFiles/LoginApp.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoginApp.dir/mainwindow.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ganjiefeng/Desktop/algorithm/LoginApp/mainwindow.cpp -o CMakeFiles/LoginApp.dir/mainwindow.cpp.s

CMakeFiles/LoginApp.dir/secdialog.cpp.o: CMakeFiles/LoginApp.dir/flags.make
CMakeFiles/LoginApp.dir/secdialog.cpp.o: /Users/ganjiefeng/Desktop/algorithm/LoginApp/secdialog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/LoginApp.dir/secdialog.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoginApp.dir/secdialog.cpp.o -c /Users/ganjiefeng/Desktop/algorithm/LoginApp/secdialog.cpp

CMakeFiles/LoginApp.dir/secdialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoginApp.dir/secdialog.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ganjiefeng/Desktop/algorithm/LoginApp/secdialog.cpp > CMakeFiles/LoginApp.dir/secdialog.cpp.i

CMakeFiles/LoginApp.dir/secdialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoginApp.dir/secdialog.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ganjiefeng/Desktop/algorithm/LoginApp/secdialog.cpp -o CMakeFiles/LoginApp.dir/secdialog.cpp.s

CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.o: CMakeFiles/LoginApp.dir/flags.make
CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.o: LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.o -c /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp

CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp > CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.i

CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp -o CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.s

# Object files for target LoginApp
LoginApp_OBJECTS = \
"CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/LoginApp.dir/main.cpp.o" \
"CMakeFiles/LoginApp.dir/mainwindow.cpp.o" \
"CMakeFiles/LoginApp.dir/secdialog.cpp.o" \
"CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.o"

# External object files for target LoginApp
LoginApp_EXTERNAL_OBJECTS =

LoginApp: CMakeFiles/LoginApp.dir/LoginApp_autogen/mocs_compilation.cpp.o
LoginApp: CMakeFiles/LoginApp.dir/main.cpp.o
LoginApp: CMakeFiles/LoginApp.dir/mainwindow.cpp.o
LoginApp: CMakeFiles/LoginApp.dir/secdialog.cpp.o
LoginApp: CMakeFiles/LoginApp.dir/LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp.o
LoginApp: CMakeFiles/LoginApp.dir/build.make
LoginApp: /Users/ganjiefeng/Qt5.14.2/5.14.2/clang_64/lib/QtSql.framework/QtSql
LoginApp: /Users/ganjiefeng/Qt5.14.2/5.14.2/clang_64/lib/QtSvg.framework/QtSvg
LoginApp: /Users/ganjiefeng/Qt5.14.2/5.14.2/clang_64/lib/QtWidgets.framework/QtWidgets
LoginApp: /Users/ganjiefeng/Qt5.14.2/5.14.2/clang_64/lib/QtGui.framework/QtGui
LoginApp: /Users/ganjiefeng/Qt5.14.2/5.14.2/clang_64/lib/QtCore.framework/QtCore
LoginApp: CMakeFiles/LoginApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable LoginApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LoginApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LoginApp.dir/build: LoginApp

.PHONY : CMakeFiles/LoginApp.dir/build

CMakeFiles/LoginApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LoginApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LoginApp.dir/clean

CMakeFiles/LoginApp.dir/depend: LoginApp_autogen/EWIEGA46WW/qrc_resource.cpp
	cd /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ganjiefeng/Desktop/algorithm/LoginApp /Users/ganjiefeng/Desktop/algorithm/LoginApp /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug /Users/ganjiefeng/Desktop/algorithm/build-LoginApp-Desktop_x86_darwin_generic_mach_o_64bit-Debug/CMakeFiles/LoginApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LoginApp.dir/depend

