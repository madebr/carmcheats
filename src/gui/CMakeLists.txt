set(GUI_QTVERSION "6" CACHE STRING "Qt version to use")
find_package(Qt${GUI_QTVERSION} REQUIRED COMPONENTS Core Widgets)

add_library(carmgui_utils STATIC
    gui_utils.cpp
    gui_utils.h
)
target_link_libraries(carmgui_utils
    PRIVATE
        carm::cheathashlib
        Qt${GUI_QTVERSION}::Core
)

add_executable(carmcheathashgui
    carmhashgui.cpp
    carmhashgui.h
    carmhashgui.ui
    carmhashgui.qrc
)
set_target_properties(carmcheathashgui
    PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
)
target_link_libraries(carmcheathashgui
    PRIVATE
        carmgui_utils
        Qt${GUI_QTVERSION}::Widgets
)

add_executable(carm2cheatpatchergui
    carm2cheatpatchergui.cpp
    carm2cheatpatchergui.h
    carm2cheatpatchergui.ui
    carm2cheatpatchergui.qrc
)
set_target_properties(carm2cheatpatchergui
    PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
)
target_link_libraries(carm2cheatpatchergui
    PRIVATE
        carm::cheatpatchlib
        Qt${GUI_QTVERSION}::Widgets
)
