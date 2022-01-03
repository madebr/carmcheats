add_library(carmutil
    carmutil.c
    carmutil.h
)
add_library(carm::util ALIAS carmutil)

add_library(carmcheathash
    carmhash.c
    carmhash.h
)
add_library(carm::cheathashlib ALIAS carmcheathash)
target_include_directories(carmcheathash
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(carmcheathash
    PROPERTIES
        PUBLIC_HEADER
            "${CMAKE_CURRENT_SOURCE_DIR}/carmhash.h"
)

add_library(carmcheatpatch
    carmcheatrawdata.c
    carmcheatrawdata.h
    carm2cheatrawdata.c
    carm2cheatrawdata.h
)
add_library(carm::cheatpatchlib ALIAS carmcheatpatch)
target_include_directories(carmcheatpatch
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_libraries(carmcheatpatch
    PRIVATE
        carm::cheathashlib
)
set_target_properties(carmcheatpatch
    PROPERTIES
        PUBLIC_HEADER
            "${CMAKE_CURRENT_SOURCE_DIR}/carmcheatpatch.h;${CMAKE_CURRENT_SOURCE_DIR}/carm2cheatrawdata.h"
)
