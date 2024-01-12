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

find_library(modbuslib modbus PATHS ${SYSTEM_LOCAL})
find_library(pigpiolib pigpio PATHS ${SYSTEM_LOCAL})

set(meteo_src_files 
    sources/bucket.cpp
    sources/cwt_modbus.cpp
    sources/http_comm.cpp
    sources/meteoman.cpp
    sources/logic.cpp
    sources/timer.cpp
    sources/tick.cpp
    sources/traffic_light.cpp
)

target_sources(meteoman_app PRIVATE ${meteo_src_files})
target_include_directories(meteoman_app PRIVATE extern)
target_link_libraries(  meteoman_app PRIVATE
                                            stdc++
                                            pthread
                                            rt
                                            curl
                                            ${modbuslib}
                                            ${pigpiolib}
                                            fmt)