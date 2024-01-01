cmake_minimum_required(VERSION 3.18)

set(meteo_src_files 
    bucket.cpp
    cwt_modbus.cpp
    http_comm.cpp
    meteoman.cpp
    logic.cpp
    timer.cpp
    traffic_light.cpp
)

target_sources(meteoman_app PRIVATE ${meteo_src_files})

find_library(modbuslib modbus PATHS ${SYSTEM_LOCAL})
find_library(pigpiolib pigpio PATHS ${SYSTEM_LOCAL})

target_link_libraries(  meteoman_app PRIVATE
                                            stdc++
                                            pthread
                                            rt
                                            curl
                                            ${modbuslib}
                                            ${pigpiolib}
                                            fmt
                    )