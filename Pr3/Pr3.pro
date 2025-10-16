TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        administrador.cpp \
        cajero.cpp \
        codificador.cpp \
        main.cpp\
        decodificador.cpp\
        usuario.cpp \
        verificaciones.cpp

HEADERS += \
    administrador.h \
    cajero.h\
    usuario.h
