
DEFINES += GIT_VERSION=\\\"$$system(git describe --tags > $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git rev-list --all --count >> $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git branch >> $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git log -1 >> $$PWD/program_version.txt)\\\"

CONFIG += c++11 console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += ../../yaprogramversion.cpp \
    ../../yaimagemagick7test.cpp \
    ../../yaopenmpthread.cpp
RESOURCES += \
    ../../resources.qrc

HEADERS += \
    ../../yaprogramversion.h \
    ../../yaimagemagick7test.h \
    ../../yaopenmpthread.h
