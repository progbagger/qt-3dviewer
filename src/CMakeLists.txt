cmake_minimum_required(VERSION 3.5)

project(Viewer2 VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)

include_directories("view" "model" "controller")

include_directories("external/QtGifImage/src/gifimage" "external/QtGifImage/src/3rdParty/giflib")

set(PROJECT_SOURCES
    main.cc
	
    view/view.cc
    view/view.h
    view/view.ui
    view/openglwidget.h
    view/openglwidget.cc
    view/incorrect_file_dialog_window.h
    view/incorrect_file_dialog_window.cc
    view/incorrect_file_dialog_window.ui
    view/opening_file_dialog_window.h
    view/opening_file_dialog_window.cc
    view/opening_file_dialog_window.ui

    model/figure.h
    model/figure.cc
    model/model.h
    model/model.cc
    model/parser.h
    model/parser.cc
    model/square_matrix.h
    model/square_matrix.cc
    model/transformation_matrix4d.h
    model/transformation_matrix4d.cc
    model/point3d.h
    model/point3d.cc
    view/settings_saver.h
    view/settings_saver.cc

    controller/controller.h
    controller/controller.cc

    external/QtGifImage/src/gifimage/qgifimage.h
    external/QtGifImage/src/gifimage/qgifimage.cpp
    external/QtGifImage/src/gifimage/qgifglobal.h
    external/QtGifImage/src/gifimage/qgifimage_p.h

    external/QtGifImage/src/3rdParty/giflib/gif_lib.h
    external/QtGifImage/src/3rdParty/giflib/gif_hash.h
    external/QtGifImage/src/3rdParty/giflib/gif_lib_private.h

    external/QtGifImage/src/3rdParty/giflib/dgif_lib.c
    external/QtGifImage/src/3rdParty/giflib/egif_lib.c
    external/QtGifImage/src/3rdParty/giflib/gifalloc.c
    external/QtGifImage/src/3rdParty/giflib/gif_err.c
    external/QtGifImage/src/3rdParty/giflib/gif_font.c
    external/QtGifImage/src/3rdParty/giflib/gif_hash.c
    external/QtGifImage/src/3rdParty/giflib/quantize.c
)

qt_add_resources(PROJECT_SOURCES resources.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Viewer2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Viewer2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Viewer2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Viewer2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Viewer2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::OpenGLWidgets)

set_target_properties(Viewer2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Viewer2)
endif()
