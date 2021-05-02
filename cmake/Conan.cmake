macro(run_conan)
    # Download automatically, you can also just copy the conan.cmake file
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote(
            NAME
            bincrafters
            URL
            https://api.bintray.com/conan/bincrafters/public-conan)
    conan_add_remote(
            NAME
            conan-center
            URL
            https://conan.bintray.com)
    conan_add_remote(
            NAME
            FFF
            URL
            https://api.bintray.com/conan/jellespijker/FantasticFuckinFusion)

    conan_cmake_run(
            REQUIRES
                ${CONAN_EXTRA_REQUIRES}
                fmt/7.1.3
                spdlog/1.8.5
            OPTIONS
                ${CONAN_EXTRA_OPTIONS}
            BASIC_SETUP
                CMAKE_TARGETS # individual targets to link to
            GENERATORS
                cmake_find_package
                cmake_paths
            SETTINGS
                compiler.cppstd=20
                build_type=Release
            BUILD
                missing)
    include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
endmacro()
