QT -= gui

TARGET = IM7Test

DEFINES += GIT_VERSION=\\\"$$system(git describe --tags > $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git rev-list --all --count >> $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git branch >> $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git log -1 >> $$PWD/program_version.txt)\\\"


CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp
RESOURCES += \
    resources.qrc

HEADERS +=