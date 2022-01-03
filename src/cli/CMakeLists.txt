add_executable(carmcheathashcli
    carmhashcli.c
)
target_link_libraries(carmcheathashcli
    PRIVATE
        carm::cheathashlib
)

add_executable(carm2cheatpatchercli
    carm2cheatpatchercli.c
)
target_link_libraries(carm2cheatpatchercli
    PRIVATE
        carm::util
        carm::cheathashlib
        carm::cheatpatchlib
)
