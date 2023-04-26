cmake_minimum_required(VERSION 3.18)

project(MeteoMan)

include(FetchContent)

add_executable(meteoman_app)



configure_file(config/config.ini ${CMAKE_BINARY_DIR}/ COPYONLY)

FetchContent_Declare(external-fmt
    GIT_REPOSITORY  https://github.com/fmtlib/fmt
    GIT_TAG         9.1.0
)
FetchContent_MakeAvailable(external-fmt)

add_subdirectory(sources)