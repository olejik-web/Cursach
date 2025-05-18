QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CalculateThread.cpp \
    Calculator.cpp \
    EditParametersDialog.cpp \
    Grammar.cpp \
    GraphDrawer.cpp \
    LL1Analyser.cpp \
    MainWindow.cpp \
    Node.cpp \
    ParametersTableDelegate.cpp \
    Solver.cpp \
    Tester.cpp \
    main.cpp \
    qcustomplot.cpp

HEADERS += \
    CalculateThread.h \
    Calculator.h \
    EditParametersDialog.h \
    Grammar.h \
    GraphDrawer.h \
    LL1Analyser.h \
    MainWindow.h \
    Node.h \
    ParametersTableDelegate.h \
    Solver.h \
    Tester.h \
    qcustomplot.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    EditParametersDialog.ui \
    MainWindow.ui
