QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        blocks.cpp \
        crypto.cpp \
        dbworker.cpp \
        main.cpp \
        server.cpp \
        worker.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    blocks.h \
    crypto.h \
    dbworker.h \
    server.h \
    worker.h

FORMS +=

win32:INCLUDEPATH += "C:/PostgreSQL/15/include"
unix:INCLUDEPATH += /usr/include/postgresql

win32:LIBS += "C:/PostgreSQL/15/lib/libpq.lib"
unix:LIBS += -L/usr/lib -lpq
