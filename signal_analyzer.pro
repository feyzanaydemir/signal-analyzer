QT += core gui widgets charts

CONFIG += c++17

LIBS += -lfftw3

INCLUDEPATH += /usr/include/c++/9
INCLUDEPATH += /usr/include/x86_64-linux-gnu
INCLUDEPATH += /usr/include/x86_64-linux-gnu/c++/9
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/QtCore
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/QtGui
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/QtWidgets
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/QtCharts

LIBS += -L/usr/lib
LIBS += -L/usr/lib/x86_64-linux-gnu

SOURCES += \
    src/MainWindow.cpp \
    src/Signal.cpp \
    src/signalGeneration.cpp \
    src/windowing.cpp \

HEADERS += \
    include/MainWindow.h \
    include/Signal.h \
    include/signalGeneration.h \
    include/windowing.h \

OBJECTS_DIR = build/objects

DESTDIR = build/bin

DISTFILES += signal_analyzer.desktop

RESOURCES += resources.qrc
