QT -= gui
QT += sql
QT += core network
CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += thread
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        blocks.cpp \
        dbworker.cpp \
        main.cpp \
        server.cpp

# Default rules for deployment.



win64:INCLUDEPATH += "C:/Program Files/PostgreSQL/15/include"
unix:INCLUDEPATH += /usr/include/postgresql

win64:LIBS += "C:/Program Files/PostgreSQL/15/lib/libpq.dll"
unix:LIBS += -L/usr/lib -lpq

PLUGIN_CLASS_NAME = QPSQLDriverPlugin

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    blocks.h \
    dbworker.h \
    server.h

FORMS +=
