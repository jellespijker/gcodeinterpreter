cmake_minimum_required(VERSION 3.15)

project(gcode_interpreter CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
if (BUILD_SHARED_LIBS)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif (BUILD_SHARED_LIBS)

option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            project_options
            INTERFACE
            <vector>
            <string>
            <string_view>
            <fstream>
            <ostream>
            <memory>
            <regex>
    )
endif()

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES
        range-v3/0.11.0
        )

set(CONAN_EXTRA_OPTIONS
        )

include(cmake/Conan.cmake)

if(ENABLE_TESTING)
    list(APPEND CONAN_EXTRA_REQUIRES catch2/2.13.6)
endif()

option(ENABLE_CMDLINE_TOOL "Create a standalone instance" ON)
if(ENABLE_CMDLINE_TOOL)
    list(APPEND CONAN_EXTRA_REQUIRES docopt.cpp/0.6.2)
endif()

run_conan()

find_package(spdlog REQUIRED)
find_package(range-v3 REQUIRED)

if(ENABLE_TESTING)
    enable_testing()
    message("Building Tests. Be sure to check out test/constexpr_tests for constexpr testing")
    add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
    message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
    add_subdirectory(fuzz_test)
endif()

if(ENABLE_CMDLINE_TOOL)
    message("Building gcode_convert commandline program")
    add_subdirectory(gcode_convert)
endif()

# DEFINE BINARY AND LIBS PATHS ACCORDING TO GNU STANDARDS
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(SRC_FILES
        src/Token.cpp
        src/Lexer.cpp
        src/Parser.cpp
        src/ElementFactory.cpp
        src/AST/Element.cpp
        src/AST/MachineElement.cpp
        src/AST/ToolElement.cpp
        src/AST/ChangeElement.cpp
        src/AST/MotionElement.cpp
        src/AST/CoordinateElement.cpp
        src/AST/CommentElement.cpp
        src/AST/NumericElement.cpp
        src/AST/TextElement.cpp
        )

set(HDR_FILES
        include/gcode/Token.h
        include/gcode/Lexer.h
        include/gcode/Parser.h
        include/gcode/ElementFactory.h
        include/gcode/AST/Element.h
        include/gcode/AST/MachineElement.h
        include/gcode/AST/ToolElement.h
        include/gcode/AST/ChangeElement.h
        include/gcode/AST/MotionElement.h
        include/gcode/AST/CoordinateElement.h
        include/gcode/AST/CommentElement.h
        include/gcode/AST/NumericElement.h
        include/gcode/AST/TextElement.h
        )

add_library(gcodeinterpreter STATIC ${SRC_FILES} ${HDR_FILES})

target_link_libraries(gcodeinterpreter
        PRIVATE
        project_options
        project_warnings)

target_compile_options(gcodeinterpreter
        PRIVATE
        -fPIC)

target_link_libraries(gcodeinterpreter
        PRIVATE
        spdlog::spdlog
        range-v3::range-v3
        )

target_include_directories(gcodeinterpreter
        PRIVATE
        spdlog::spdlog
        range-v3::range-v3
        )

target_include_directories(gcodeinterpreter PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
