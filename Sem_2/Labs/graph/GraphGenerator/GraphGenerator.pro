QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addedge.cpp \
    deleteedge.cpp \
    deletenode.cpp \
    graph.cpp \
    main.cpp \
    graphgenerator.cpp \
    searchmenu.cpp \
    tsp.cpp

HEADERS += \
    addedge.h \
    deleteedge.h \
    deletenode.h \
    graph.h \
    graphgenerator.h \
    searchmenu.h \
    tsp.h

FORMS += \
    addedge.ui \
    deleteedge.ui \
    deletenode.ui \
    graphgenerator.ui \
    searchmenu.ui \
    tsp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
