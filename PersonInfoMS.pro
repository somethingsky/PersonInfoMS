QT -= gui
QT += core network concurrent xml sql
CONFIG += c++11
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include( $$PWD/library/JQLibrary/JQLibrary.pri )
include($$PWD/library/log4qt/log4qtlib.pri)
INCLUDEPATH += $$PWD/t_person
include($$PWD/t_person/t_person.pri)
INCLUDEPATH += $$PWD/library/CJson
include($$PWD/library/CJson/cJson.pri)

SOURCES += \
        main.cpp \
    sqliteoperator.cpp \
    jsontools.cpp \
    configfile.cpp \
    filetools.cpp \
    requesthandle.cpp

HEADERS += \
    sqliteoperator.h \
    jsontools.h \
    configfile.h \
    filetools.h \
    requesthandle.h \
    requestfactory.h

DISTFILES += \
    $$PWD/resources/config.ini \
    $$PWD/resources/config.xml \
    $$PWD/resources/config.json \
    $$PWD/resources/personInfo.sql
