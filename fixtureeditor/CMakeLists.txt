set(fixeditor_src
    addchannelsdialog.cpp
    app.cpp
    capabilitywizard.cpp
    editchannel.cpp
    edithead.cpp
    editmode.cpp
    editphysical.cpp
    fixtureeditor.cpp
    main.cpp
    aboutbox.cpp
    docbrowser.cpp
    apputil.cpp
) 

include_directories(
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Script_INCLUDE_DIRS}
    ${Qt5Multimedia_INCLUDE_DIRS}
    ${Qt5MultimediaWidgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/engine
    ${CMAKE_SOURCE_DIR}/engine/src/
)

add_executable(qlcplus-fixtureeditor 
    ${fixeditor_src}
    qlcui.qrc
)

target_link_libraries(qlcplus-fixtureeditor
    qlcplusengine
)

install(TARGETS qlcplus-fixtureeditor DESTINATION "${APPROOT}/bin")
