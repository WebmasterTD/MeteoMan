cmake_minimum_required(VERSION 3.18)

project(MeteoMan
    VERSION 0.0.1
)

include(GNUInstallDirs)

add_compile_options(
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -pedantic

    # -Wold-style-cast
    # -Wcast-align
    # -Wunused
    # -Woverloaded-virtual
    # -Wpedantic
    # -Wconversion
    # -Wsign-conversion
    # -Wmisleading-indentation
    # -Wnull-dereference
    # -Wdouble-promotion
    # -Wformat=2
    # -Wimplicit-fallthrough
)

install(FILES config/meteoman_conf.ini
        DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(FetchContent)
FetchContent_Declare(external-fmt
    GIT_REPOSITORY  https://github.com/fmtlib/fmt
    GIT_TAG         10.2.1
)
FetchContent_MakeAvailable(external-fmt)

find_library(modbuslib modbus PATHS ${SYSTEM_LOCAL})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(meteo_src_files 
    sources/bucket.cpp
    sources/cwt_modbus.cpp
    sources/http_comm.cpp
    sources/meteoman.cpp
    sources/logic.cpp
    sources/tick.cpp
    sources/traffic_light.cpp
)

add_executable(meteoman_app)
target_sources(meteoman_app PRIVATE ${meteo_src_files})

target_link_directories(meteoman_app PRIVATE ${CMAKE_SYSROOT}/lib/gcc/arm-linux-gnueabihf)
target_link_libraries(  meteoman_app PRIVATE
    Threads::Threads
    stdc++
    pthread
    curl
    ${modbuslib}
    gpiodcxx
    fmt
)

add_custom_command(TARGET meteoman_app
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

install(TARGETS meteoman_app RUNTIME)

# set(CPACK_GENERATOR "DEB")
# set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "armhf")
# set(CPACK_DEBIAN_PACKAGE_NAME "MeteoMan")
# set(CPACK_DEBIAN_PACKAGE_MAINTAINER "akos")
# set(CPACK_DEBIAN_PACKAGE_DEPENDS "gpiod,libcurl4,libmodbus5")
# include(CPack)
