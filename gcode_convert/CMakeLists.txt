add_executable(gcode_convert main.cpp)

find_package(docopt REQUIRED)
find_package(spdlog REQUIRED)

target_compile_options(gcode_convert
        PRIVATE
            -fPIC)

target_link_libraries(gcode_convert
        PRIVATE
        gcodeinterpreter
        project_options
            project_warnings)

target_link_libraries(gcode_convert
        PRIVATE
        gcodeinterpreter
        spdlog::spdlog
            docopt::docopt
        )

target_include_directories(gcode_convert
        PRIVATE
            spdlog::spdlog
            docopt::docopt
        )

