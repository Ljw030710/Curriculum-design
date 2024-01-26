QT       += core gui \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BubbleSort.cpp \
    BucketSort.cpp \
    CountSort.cpp \
    HeapSort.cpp \
    InsertionSort.cpp \
    MainCanvas.cpp \
    MainUI.cpp \
    MergeSort.cpp \
    QuickSort.cpp \
    RadixSort.cpp \
    SelectionSort.cpp \
    ShellSort.cpp \
    ShowData.cpp \
    SortFactory.cpp \
    SortObject.cpp \
    choosemenu.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BubbleSort.h \
    BucketSort.h \
    CountSort.h \
    HeapSort.h \
    InsertionSort.h \
    MainCanvas.h \
    MainUI.h \
    MergeSort.h \
    QuickSort.h \
    RadixSort.h \
    SelectionSort.h \
    ShellSort.h \
    ShowData.h \
    SortFactory.h \
    SortObject.h \
    choosemenu.h \
    mainwindow.h

FORMS += \
    MainCanvas.ui \
    MainUI.ui \
    ShowData.ui \
    choosemenu.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
