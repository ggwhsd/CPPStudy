# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gugw/linuxStudy_VsCode/51muduoBaseStudy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gugw/linuxStudy_VsCode/51muduoBaseStudy

# Include any dependencies generated for this target.
include CMakeFiles/muduo_base.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/muduo_base.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/muduo_base.dir/flags.make

CMakeFiles/muduo_base.dir/Date.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/Date.cc.o: Date.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/Date.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Date.cc.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Date.cc

CMakeFiles/muduo_base.dir/Date.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Date.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Date.cc > CMakeFiles/muduo_base.dir/Date.cc.i

CMakeFiles/muduo_base.dir/Date.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Date.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Date.cc -o CMakeFiles/muduo_base.dir/Date.cc.s

CMakeFiles/muduo_base.dir/Date.cc.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/Date.cc.o.requires

CMakeFiles/muduo_base.dir/Date.cc.o.provides: CMakeFiles/muduo_base.dir/Date.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/Date.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/Date.cc.o.provides

CMakeFiles/muduo_base.dir/Date.cc.o.provides.build: CMakeFiles/muduo_base.dir/Date.cc.o

CMakeFiles/muduo_base.dir/TimeZone.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/TimeZone.cpp.o: TimeZone.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/TimeZone.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/TimeZone.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/TimeZone.cpp

CMakeFiles/muduo_base.dir/TimeZone.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/TimeZone.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/TimeZone.cpp > CMakeFiles/muduo_base.dir/TimeZone.cpp.i

CMakeFiles/muduo_base.dir/TimeZone.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/TimeZone.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/TimeZone.cpp -o CMakeFiles/muduo_base.dir/TimeZone.cpp.s

CMakeFiles/muduo_base.dir/TimeZone.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/TimeZone.cpp.o.requires

CMakeFiles/muduo_base.dir/TimeZone.cpp.o.provides: CMakeFiles/muduo_base.dir/TimeZone.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/TimeZone.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/TimeZone.cpp.o.provides

CMakeFiles/muduo_base.dir/TimeZone.cpp.o.provides.build: CMakeFiles/muduo_base.dir/TimeZone.cpp.o

CMakeFiles/muduo_base.dir/LogStream.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/LogStream.cc.o: LogStream.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/LogStream.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/LogStream.cc.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/LogStream.cc

CMakeFiles/muduo_base.dir/LogStream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/LogStream.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/LogStream.cc > CMakeFiles/muduo_base.dir/LogStream.cc.i

CMakeFiles/muduo_base.dir/LogStream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/LogStream.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/LogStream.cc -o CMakeFiles/muduo_base.dir/LogStream.cc.s

CMakeFiles/muduo_base.dir/LogStream.cc.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/LogStream.cc.o.requires

CMakeFiles/muduo_base.dir/LogStream.cc.o.provides: CMakeFiles/muduo_base.dir/LogStream.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/LogStream.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/LogStream.cc.o.provides

CMakeFiles/muduo_base.dir/LogStream.cc.o.provides.build: CMakeFiles/muduo_base.dir/LogStream.cc.o

CMakeFiles/muduo_base.dir/CurrentThread.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/CurrentThread.cpp.o: CurrentThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/CurrentThread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/CurrentThread.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CurrentThread.cpp

CMakeFiles/muduo_base.dir/CurrentThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/CurrentThread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CurrentThread.cpp > CMakeFiles/muduo_base.dir/CurrentThread.cpp.i

CMakeFiles/muduo_base.dir/CurrentThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/CurrentThread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CurrentThread.cpp -o CMakeFiles/muduo_base.dir/CurrentThread.cpp.s

CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.requires

CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.provides: CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.provides

CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.provides.build: CMakeFiles/muduo_base.dir/CurrentThread.cpp.o

CMakeFiles/muduo_base.dir/Logging.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/Logging.cpp.o: Logging.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/Logging.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Logging.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Logging.cpp

CMakeFiles/muduo_base.dir/Logging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Logging.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Logging.cpp > CMakeFiles/muduo_base.dir/Logging.cpp.i

CMakeFiles/muduo_base.dir/Logging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Logging.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Logging.cpp -o CMakeFiles/muduo_base.dir/Logging.cpp.s

CMakeFiles/muduo_base.dir/Logging.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/Logging.cpp.o.requires

CMakeFiles/muduo_base.dir/Logging.cpp.o.provides: CMakeFiles/muduo_base.dir/Logging.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/Logging.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/Logging.cpp.o.provides

CMakeFiles/muduo_base.dir/Logging.cpp.o.provides.build: CMakeFiles/muduo_base.dir/Logging.cpp.o

CMakeFiles/muduo_base.dir/FileUtil.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/FileUtil.cpp.o: FileUtil.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/FileUtil.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/FileUtil.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/FileUtil.cpp

CMakeFiles/muduo_base.dir/FileUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/FileUtil.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/FileUtil.cpp > CMakeFiles/muduo_base.dir/FileUtil.cpp.i

CMakeFiles/muduo_base.dir/FileUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/FileUtil.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/FileUtil.cpp -o CMakeFiles/muduo_base.dir/FileUtil.cpp.s

CMakeFiles/muduo_base.dir/FileUtil.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/FileUtil.cpp.o.requires

CMakeFiles/muduo_base.dir/FileUtil.cpp.o.provides: CMakeFiles/muduo_base.dir/FileUtil.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/FileUtil.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/FileUtil.cpp.o.provides

CMakeFiles/muduo_base.dir/FileUtil.cpp.o.provides.build: CMakeFiles/muduo_base.dir/FileUtil.cpp.o

CMakeFiles/muduo_base.dir/Timestamp.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/Timestamp.cpp.o: Timestamp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/Timestamp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Timestamp.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Timestamp.cpp

CMakeFiles/muduo_base.dir/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Timestamp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Timestamp.cpp > CMakeFiles/muduo_base.dir/Timestamp.cpp.i

CMakeFiles/muduo_base.dir/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Timestamp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Timestamp.cpp -o CMakeFiles/muduo_base.dir/Timestamp.cpp.s

CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires

CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides: CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides

CMakeFiles/muduo_base.dir/Timestamp.cpp.o.provides.build: CMakeFiles/muduo_base.dir/Timestamp.cpp.o

CMakeFiles/muduo_base.dir/Condition.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/Condition.cpp.o: Condition.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/Condition.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Condition.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Condition.cpp

CMakeFiles/muduo_base.dir/Condition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Condition.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Condition.cpp > CMakeFiles/muduo_base.dir/Condition.cpp.i

CMakeFiles/muduo_base.dir/Condition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Condition.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Condition.cpp -o CMakeFiles/muduo_base.dir/Condition.cpp.s

CMakeFiles/muduo_base.dir/Condition.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/Condition.cpp.o.requires

CMakeFiles/muduo_base.dir/Condition.cpp.o.provides: CMakeFiles/muduo_base.dir/Condition.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/Condition.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/Condition.cpp.o.provides

CMakeFiles/muduo_base.dir/Condition.cpp.o.provides.build: CMakeFiles/muduo_base.dir/Condition.cpp.o

CMakeFiles/muduo_base.dir/Exception.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/Exception.cpp.o: Exception.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/Exception.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Exception.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Exception.cpp

CMakeFiles/muduo_base.dir/Exception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Exception.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Exception.cpp > CMakeFiles/muduo_base.dir/Exception.cpp.i

CMakeFiles/muduo_base.dir/Exception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Exception.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Exception.cpp -o CMakeFiles/muduo_base.dir/Exception.cpp.s

CMakeFiles/muduo_base.dir/Exception.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/Exception.cpp.o.requires

CMakeFiles/muduo_base.dir/Exception.cpp.o.provides: CMakeFiles/muduo_base.dir/Exception.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/Exception.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/Exception.cpp.o.provides

CMakeFiles/muduo_base.dir/Exception.cpp.o.provides.build: CMakeFiles/muduo_base.dir/Exception.cpp.o

CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o: ProcessInfo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/ProcessInfo.cpp

CMakeFiles/muduo_base.dir/ProcessInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/ProcessInfo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/ProcessInfo.cpp > CMakeFiles/muduo_base.dir/ProcessInfo.cpp.i

CMakeFiles/muduo_base.dir/ProcessInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/ProcessInfo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/ProcessInfo.cpp -o CMakeFiles/muduo_base.dir/ProcessInfo.cpp.s

CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.requires

CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.provides: CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.provides

CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.provides.build: CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o

CMakeFiles/muduo_base.dir/LogFile.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/LogFile.cpp.o: LogFile.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/LogFile.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/LogFile.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/LogFile.cpp

CMakeFiles/muduo_base.dir/LogFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/LogFile.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/LogFile.cpp > CMakeFiles/muduo_base.dir/LogFile.cpp.i

CMakeFiles/muduo_base.dir/LogFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/LogFile.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/LogFile.cpp -o CMakeFiles/muduo_base.dir/LogFile.cpp.s

CMakeFiles/muduo_base.dir/LogFile.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/LogFile.cpp.o.requires

CMakeFiles/muduo_base.dir/LogFile.cpp.o.provides: CMakeFiles/muduo_base.dir/LogFile.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/LogFile.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/LogFile.cpp.o.provides

CMakeFiles/muduo_base.dir/LogFile.cpp.o.provides.build: CMakeFiles/muduo_base.dir/LogFile.cpp.o

CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o: CountDownLatch.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CountDownLatch.cpp

CMakeFiles/muduo_base.dir/CountDownLatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/CountDownLatch.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CountDownLatch.cpp > CMakeFiles/muduo_base.dir/CountDownLatch.cpp.i

CMakeFiles/muduo_base.dir/CountDownLatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/CountDownLatch.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CountDownLatch.cpp -o CMakeFiles/muduo_base.dir/CountDownLatch.cpp.s

CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires

CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides: CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides

CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.provides.build: CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o

CMakeFiles/muduo_base.dir/Thread.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/Thread.cpp.o: Thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/Thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/Thread.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Thread.cpp

CMakeFiles/muduo_base.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Thread.cpp > CMakeFiles/muduo_base.dir/Thread.cpp.i

CMakeFiles/muduo_base.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/Thread.cpp -o CMakeFiles/muduo_base.dir/Thread.cpp.s

CMakeFiles/muduo_base.dir/Thread.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/Thread.cpp.o.requires

CMakeFiles/muduo_base.dir/Thread.cpp.o.provides: CMakeFiles/muduo_base.dir/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/Thread.cpp.o.provides

CMakeFiles/muduo_base.dir/Thread.cpp.o.provides.build: CMakeFiles/muduo_base.dir/Thread.cpp.o

CMakeFiles/muduo_base.dir/ThreadPool.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/ThreadPool.cpp.o: ThreadPool.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/ThreadPool.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/ThreadPool.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/ThreadPool.cpp

CMakeFiles/muduo_base.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/ThreadPool.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/ThreadPool.cpp > CMakeFiles/muduo_base.dir/ThreadPool.cpp.i

CMakeFiles/muduo_base.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/ThreadPool.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/ThreadPool.cpp -o CMakeFiles/muduo_base.dir/ThreadPool.cpp.s

CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.requires

CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.provides: CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.provides

CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.provides.build: CMakeFiles/muduo_base.dir/ThreadPool.cpp.o

CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o: AsyncLogging.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o -c /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/AsyncLogging.cpp

CMakeFiles/muduo_base.dir/AsyncLogging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/AsyncLogging.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/AsyncLogging.cpp > CMakeFiles/muduo_base.dir/AsyncLogging.cpp.i

CMakeFiles/muduo_base.dir/AsyncLogging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/AsyncLogging.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/AsyncLogging.cpp -o CMakeFiles/muduo_base.dir/AsyncLogging.cpp.s

CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.requires:
.PHONY : CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.requires

CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.provides: CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.provides

CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.provides.build: CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o

# Object files for target muduo_base
muduo_base_OBJECTS = \
"CMakeFiles/muduo_base.dir/Date.cc.o" \
"CMakeFiles/muduo_base.dir/TimeZone.cpp.o" \
"CMakeFiles/muduo_base.dir/LogStream.cc.o" \
"CMakeFiles/muduo_base.dir/CurrentThread.cpp.o" \
"CMakeFiles/muduo_base.dir/Logging.cpp.o" \
"CMakeFiles/muduo_base.dir/FileUtil.cpp.o" \
"CMakeFiles/muduo_base.dir/Timestamp.cpp.o" \
"CMakeFiles/muduo_base.dir/Condition.cpp.o" \
"CMakeFiles/muduo_base.dir/Exception.cpp.o" \
"CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o" \
"CMakeFiles/muduo_base.dir/LogFile.cpp.o" \
"CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o" \
"CMakeFiles/muduo_base.dir/Thread.cpp.o" \
"CMakeFiles/muduo_base.dir/ThreadPool.cpp.o" \
"CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o"

# External object files for target muduo_base
muduo_base_EXTERNAL_OBJECTS =

libmuduo_base.a: CMakeFiles/muduo_base.dir/Date.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/TimeZone.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/LogStream.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/CurrentThread.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/Logging.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/FileUtil.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/Timestamp.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/Condition.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/Exception.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/LogFile.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/Thread.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/ThreadPool.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/build.make
libmuduo_base.a: CMakeFiles/muduo_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libmuduo_base.a"
	$(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/muduo_base.dir/build: libmuduo_base.a
.PHONY : CMakeFiles/muduo_base.dir/build

CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/Date.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/TimeZone.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/LogStream.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/CurrentThread.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/Logging.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/FileUtil.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/Timestamp.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/Condition.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/Exception.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/ProcessInfo.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/LogFile.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/CountDownLatch.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/Thread.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/ThreadPool.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/AsyncLogging.cpp.o.requires
.PHONY : CMakeFiles/muduo_base.dir/requires

CMakeFiles/muduo_base.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean.cmake
.PHONY : CMakeFiles/muduo_base.dir/clean

CMakeFiles/muduo_base.dir/depend:
	cd /home/gugw/linuxStudy_VsCode/51muduoBaseStudy && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gugw/linuxStudy_VsCode/51muduoBaseStudy /home/gugw/linuxStudy_VsCode/51muduoBaseStudy /home/gugw/linuxStudy_VsCode/51muduoBaseStudy /home/gugw/linuxStudy_VsCode/51muduoBaseStudy /home/gugw/linuxStudy_VsCode/51muduoBaseStudy/CMakeFiles/muduo_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/muduo_base.dir/depend
