QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ElectrodePadPair.cpp \
    Victim.cpp \
    VoiceSystem.cpp \
    aed.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AdultElectrode.h \
    AED.h \
    CardiacArrhythmias.h \
    ChildElectrode.h \
    ElectrodePad.h \
    ElectrodePadPair.h \
    NormalSinusRhythm.h \
    VentricularFibrillation.h \
    VentricularTachycardia.h \
    Victim.h \
    VoiceSystem.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
