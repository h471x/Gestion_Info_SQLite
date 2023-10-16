QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/database/dbcategory.cpp \
    sources/database/dbadmin.cpp \
    sources/database/dbinit.cpp \
    sources/database/dbproduct.cpp \
    sources/database/dbprovider.cpp \
    sources/database/dbuser.cpp \
    sources/database/triggerdown.cpp \
    sources/database/triggerup.cpp \
    sources/window/login.cpp \
    sources/window/main.cpp \
    sources/window/mainapp.cpp

HEADERS += \
    headers/database/dbadmin.h \
    headers/database/dbcategory.h \
    headers/database/dbinit.h \
    headers/database/dbproduct.h \
    headers/window/mainapp.h \
    headers/window/login.h \
    headers/database/dbprovider.h \
    headers/database/dbuser.h \
    headers/database/triggerup.h \
    headers/database/triggerdown.h

FORMS += \
    forms/mainapp.ui \
    forms/login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
