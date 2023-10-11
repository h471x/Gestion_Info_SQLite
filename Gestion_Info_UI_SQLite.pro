QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/dbconfig.cpp \
    sources/dbconnect.cpp \
    sources/loginwindow.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/theme.cpp

HEADERS += \
    header/dbconfig.h \
    header/dbconnect.h \
    header/loginwindow.h \
    header/mainwindow.h \
    header/theme.h

FORMS += \
    forms/loginwindow.ui \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    database/database.db
