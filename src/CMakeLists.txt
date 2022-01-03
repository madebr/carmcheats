cmake_minimum_required(VERSION 3.19)
project(carmcheats C CXX)

include(GNUInstallDirs)

add_compile_options(
    $<$<C_COMPILER_ID:AppleClang,Clang,GNU>:-Wall$<SEMICOLON>-Wextra$<SEMICOLON>-Werror>
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:AppleClang,Clang,GNU>>:-Wc++-compat>
    $<$<C_COMPILER_ID:MSVC>:/W4$<SEMICOLON>/WX>
)

set(CMAKE_C_STANDARD 99)

add_subdirectory(common)
add_subdirectory(cli)
add_subdirectory(gui)

install(TARGETS carmcheathash carmcheatpatch carmcheathashcli carm2cheatpatchercli carmcheathashgui carm2cheatpatchergui
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
