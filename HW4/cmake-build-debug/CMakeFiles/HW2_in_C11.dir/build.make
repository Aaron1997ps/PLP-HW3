# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\HW2_in_C11.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\HW2_in_C11.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\HW2_in_C11.dir\flags.make

CMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.obj: CMakeFiles\HW2_in_C11.dir\flags.make
CMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.obj: ..\checkdatatype.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW2_in_C11.dir/checkdatatype.cpp.obj"
	C:\PROGRA~2\MICROS~4\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.obj /FdCMakeFiles\HW2_in_C11.dir\ /FS -c "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\checkdatatype.cpp"
<<

CMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW2_in_C11.dir/checkdatatype.cpp.i"
	C:\PROGRA~2\MICROS~4\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe > CMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\checkdatatype.cpp"
<<

CMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW2_in_C11.dir/checkdatatype.cpp.s"
	C:\PROGRA~2\MICROS~4\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.s /c "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\checkdatatype.cpp"
<<

# Object files for target HW2_in_C11
HW2_in_C11_OBJECTS = \
"CMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.obj"

# External object files for target HW2_in_C11
HW2_in_C11_EXTERNAL_OBJECTS =

HW2_in_C11.exe: CMakeFiles\HW2_in_C11.dir\checkdatatype.cpp.obj
HW2_in_C11.exe: CMakeFiles\HW2_in_C11.dir\build.make
HW2_in_C11.exe: CMakeFiles\HW2_in_C11.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HW2_in_C11.exe"
	"C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\HW2_in_C11.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100171~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100171~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~4\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\HW2_in_C11.dir\objects1.rsp @<<
 /out:HW2_in_C11.exe /implib:HW2_in_C11.lib /pdb:"E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\cmake-build-debug\HW2_in_C11.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\HW2_in_C11.dir\build: HW2_in_C11.exe

.PHONY : CMakeFiles\HW2_in_C11.dir\build

CMakeFiles\HW2_in_C11.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW2_in_C11.dir\cmake_clean.cmake
.PHONY : CMakeFiles\HW2_in_C11.dir\clean

CMakeFiles\HW2_in_C11.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11" "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11" "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\cmake-build-debug" "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\cmake-build-debug" "E:\Google Drive\University of Houston\Programming Languages and Paradigm\Assignments\HW2 in C11\cmake-build-debug\CMakeFiles\HW2_in_C11.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\HW2_in_C11.dir\depend
