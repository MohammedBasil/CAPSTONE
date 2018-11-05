TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    professor.cpp \
    student.cpp \
    administrator.cpp \
    course.cpp \
    fdp.cpp \
    seminar.cpp \
    degree.cpp \
    usermanager.cpp \
    resourcemanager.cpp

HEADERS += \
    universitymember.h \
    resource.h \
    commons.h \
    professor.h \
    student.h \
    administrator.h \
    course.h \
    fdp.h \
    seminar.h \
    degree.h \
    usermanager.h \
    resourcemanager.h
