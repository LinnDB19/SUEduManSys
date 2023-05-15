QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AppendStudentRowDig.cpp \
    LoginDialog.cpp \
    LoginedAccountSingle.cpp \
    StudentFaceWidget.cpp \
    TableOperaWidget.cpp \
    labelWithPbtn.cpp \
    main.cpp \
    StaffFaceWidget.cpp \
    theDB.cpp \
    theQSS.cpp

HEADERS += \
    AppendStudentRowDig.h \
    LoginDialog.h \
    LoginedAccountSingle.h \
    StaffFaceWidget.h \
    StudentFaceWidget.h \
    TableOperaWidget.h \
    labelWithPbtn.h \
    theDB.h \
    theQSS.h

FORMS += \
    AppendStudentRowDig.ui \
    LoginDialog.ui \
    StaffFaceWidget.ui \
    StudentFaceWidget.ui \
    TableOperaWidget.ui

TRANSLATIONS += \
    SUEduManSys_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
