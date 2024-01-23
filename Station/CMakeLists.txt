cmake_minimum_required(VERSION 3.18)

project(MeteoMan
    VERSION 0.0.1
)

include(GNUInstallDirs)
include(FetchContent)

add_compile_options(-Wall -Wextra -pedantic)

FetchContent_Declare(external-fmt
    GIT_REPOSITORY  https://github.com/fmtlib/fmt
    GIT_TAG         10.2.1
)
FetchContent_MakeAvailable(external-fmt)

find_library(modbuslib modbus PATHS ${SYSTEM_LOCAL})


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
target_include_directories(meteoman_app PRIVATE extern)
target_link_directories(meteoman_app PRIVATE ${CMAKE_SYSROOT}/lib/gcc/arm-linux-gnueabihf)
target_link_libraries(  meteoman_app PRIVATE
                                            stdc++
                                            pthread
                                            rt
                                            curl
                                            ${modbuslib}
                                            gpiodcxx
                                            fmt
)

set_property(TARGET meteoman_app PROPERTY CXX_STANDARD 20)

install(FILES config/meteoman_conf.ini TYPE SYSCONF)

install(TARGETS meteoman_app)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "armhf")
set(CPACK_DEBIAN_PACKAGE_NAME "MeteoMan")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "akos")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "gpiod,libcurl4,libmodbus5")
include(CPack)