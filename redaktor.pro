QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += C:/OpenSSL-Win64/include

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = DownloadHttp

TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.

abc = C:/OpenSSL-Win64

CONFIG(release, debug|release): openssl.path = $$OUT_PWD/release
else:CONFIG(debug, debug|release): openssl.path = $$OUT_PWD/debug
openssl.files += abc/*.dll abc/lib/*.dll

INSTALLS += openssl
