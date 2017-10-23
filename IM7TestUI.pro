QT += quick
QT += webview
TARGET = IM7TestUI

DEFINES += GIT_VERSION=\\\"$$system(git describe --tags > $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git rev-list --all --count >> $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git branch >> $$PWD/program_version.txt)\\\"
DEFINES += GIT_VERSION=\\\"$$system(git log -1 >> $$PWD/program_version.txt)\\\"

CONFIG += c++11
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

IM7ANDROID = ../Android_ImageMagick7
android {
    INCLUDEPATH +=$${IM7ANDROID}/jni/ImageMagick-7.0.5-2
#arm64-v8a  armeabi  armeabi-v7a  mips  mips64  x86  x86_64
    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        message("Android/armv7")
        LIBPATHARMV7 +=$${IM7ANDROID}/libs/armeabi-v7a
        LIBS += -L$${LIBPATHARMV7}
        ANDROID_EXTRA_LIBS = \
            $${LIBPATHARMV7}/libMagickCore-7.so \
            $${LIBPATHARMV7}/libMagickWand-7.so
    }
    contains(ANDROID_TARGET_ARCH,x86) {
        message("Android/x86")
        LIBPATHX86 +=$${IM7ANDROID}/libs/x86
        LIBS += -L$${LIBPATHX86}
        ANDROID_EXTRA_LIBS = \
            $${LIBPATHX86}/libMagickCore-7.so \
            $${LIBPATHX86}/libMagickWand-7.so
    }
    contains(ANDROID_TARGET_ARCH,arm64-v8a) {
        message("Android/arm64-v8a")
        LIBPATHARMV8_64 +=$${IM7ANDROID}/libs/arm64_v8a
        LIBS += -L$${LIBPATHARMV8_64}
        ANDROID_EXTRA_LIBS = \
            $${LIBPATHARMV8_64}/libMagickCore-7.so \
            $${LIBPATHARMV8_64}/libMagickWand-7.so
    }
    contains(ANDROID_TARGET_ARCH,x86_64) {
        message("Android/x86_64")
        LIBPATHX86_64 +=$${IM7ANDROID}/libs/x86_64
        LIBS += -L$${LIBPATHX86_64}
        ANDROID_EXTRA_LIBS = \
            $${LIBPATHX86_64}/libMagickCore-7.so \
            $${LIBPATHX86_64}/libMagickWand-7.so
    }
    contains(ANDROID_TARGET_ARCH,armeabi) {
        message("Android/arm")
    }
    contains(ANDROID_TARGET_ARCH,mips) {
        message("Android/mps")
    }
    contains(ANDROID_TARGET_ARCH,mips64) {
        message("Android/mips64")
    }
    LIBS += -lMagickCore-7 -lMagickWand-7
}

linux:!android {
    INCLUDEPATH +=/usr/local/include/ImageMagick-7
    LIBS += -L/usr/local/lib
    LIBS += -lMagickCore-7.Q16HDRI -lMagickWand-7.Q16HDRI
}

SOURCES += main_ui.cpp \
    yaprogramversion.cpp \
    yaimagemagick7test.cpp \
    yaopenmpthread.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    yaprogramversion.h \
    yaimagemagick7test.h \
    yaopenmpthread.h
