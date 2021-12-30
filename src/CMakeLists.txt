cmake_minimum_required(VERSION 3.0)
project(carmcheats C CXX)

add_compile_options(
    $<$<C_COMPILER_ID:AppleClang,Clang,GNU>:-Wall$<SEMICOLON>-Wextra$<SEMICOLON>-Werror>
    $<$<C_COMPILER_ID:MSVC>:/W4$<SEMICOLON>/WX>
)

add_library(carmhash
    carmhash.c
    carmhash.h
)

add_executable(carmhashcli
    carmhashcli.c
)

target_link_libraries(carmhashcli
    PRIVATE
        carmhash
)

include(GNUInstallDirs)
install(TARGETS carmhash carmhashcli
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
