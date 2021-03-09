TEMPLATE = app
HEADERS = includes/tutil.h includes/widget.h includes/AndroidFileDialog.h 
SOURCES = src/widget.cpp src/main.cpp src/engine.cpp src/AndroidFileDialog.cpp
RESOURCES = main.qrc
QT += core gui widgets quick quickwidgets androidextras texttospeech
TARGET = main

INCLUDEPATH += includes

OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
