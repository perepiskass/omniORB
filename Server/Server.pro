TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = server
SOURCES += server.cpp \
           ../echoSK.cpp

LIBS += -lomnithread -lomniORB4 -lncurses

INCLUDEPATH += /usr/local/include \
               /usr/include/ncursesw

HEADERS += \
    ../echo.h
