cmake_minimum_required(VERSION 3.0)
project(carmcheats C)

add_executable(carmhash
    carmhash.c
)

include(GNUInstallDirs)
install(TARGETS carmhash
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
