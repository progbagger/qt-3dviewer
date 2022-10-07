QT       += core gui openglwidgets quick opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32 {
    LIBS += -lglu32 -lopengl32
}

linux {
    LIBS += -lGLU -lOpenGL
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    ../obj_parcer.c \
    ../list.c \
    ../affine.c \
    qglview.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    ../obj_parcer.h \
    ../list.h \
    ../affine.h \
    qglview.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(../Qtgifimage/gifimage/qtgifimage.pri)
