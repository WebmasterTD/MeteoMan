set(CMAKE_SYSTEM_NAME               Linux)
set(CMAKE_SYSTEM_PROCESSOR          armv6l)

set(CMAKE_SYSROOT                   /Users/akosmelczer/raspberry-sysroot/new)
set(CLANG_TARGET_TRIPLE             armv6l-linux-gnueabihf)

set(CMAKE_C_COMPILER                /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_C_COMPILER_TARGET         ${CLANG_TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER              /opt/homebrew/opt/llvm/bin/clang++)
set(CMAKE_CXX_COMPILER_TARGET       ${CLANG_TARGET_TRIPLE})


set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES    ${CMAKE_SYSROOT}/usr/local/include)

set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES  ${CMAKE_SYSROOT}/usr/local/include
                                            ${CMAKE_SYSROOT}/usr/include/c++/10
                                            ${CMAKE_SYSROOT}/usr/include/arm-linux-gnueabihf/c++/10
                                            )

set(SYSTEM_LOCAL                   ${CMAKE_SYSROOT}/usr/local/lib ${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf)

add_link_options( 					-fuse-ld=lld)
add_compile_options(                -march=armv6 -mfpu=vfp -mfloat-abi=hard)

# Don't run the linker on compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)