cmake_minimum_required(VERSION 3.0)
project(DicionaryGenerator CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

add_executable(DictionaryGenerator
    main.cpp
)
set_target_properties(DictionaryGenerator
    PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

include(GNUInstallDirs)
install(TARGETS DictionaryGenerator
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

set_directory_properties(
    PROPERTIES
        VS_STARTUP_PROJECT
            DictionaryGenerator
)
