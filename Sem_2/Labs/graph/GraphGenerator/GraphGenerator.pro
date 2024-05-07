QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addnewedgewindow.cpp \
    deleteedgewindow.cpp \
    deletenodewindow.cpp \
    graph.cpp \
    main.cpp \
    graphgenerator.cpp

HEADERS += \
    addnewedgewindow.h \
    deleteedgewindow.h \
    deletenodewindow.h \
    graph.h \
    graphgenerator.h

FORMS += \
    addnewedgewindow.ui \
    deleteedgewindow.ui \
    deletenodewindow.ui \
    graphgenerator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target