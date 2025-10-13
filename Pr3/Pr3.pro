TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        admin.cpp \
        cajero.cpp \
        codificador.cpp \
        main.cpp\
        decodificador.cpp\
        usuario.cpp

HEADERS += \
    cajero.h\
    usuario.h
