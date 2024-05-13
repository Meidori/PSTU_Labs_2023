QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorization.cpp \
    chiefdesk.cpp \
    createreport.cpp \
    employeedesk.cpp \
    employeesview.cpp \
    getreport.cpp \
    loginwindow.cpp \
    main.cpp \
    profile.cpp \
    registrationwindow.cpp \
    resourcesview.cpp \
    tasksview.cpp \
    tasksviewforemployee.cpp

HEADERS += \
    authorization.h \
    chiefdesk.h \
    createreport.h \
    employeedesk.h \
    employeesview.h \
    getreport.h \
    loginwindow.h \
    profile.h \
    registrationwindow.h \
    resourcesview.h \
    tasksview.h \
    tasksviewforemployee.h

FORMS += \
    authorization.ui \
    chiefdesk.ui \
    createreport.ui \
    employeedesk.ui \
    employeesview.ui \
    getreport.ui \
    loginwindow.ui \
    profile.ui \
    registrationwindow.ui \
    resourcesview.ui \
    tasksview.ui \
    tasksviewforemployee.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
