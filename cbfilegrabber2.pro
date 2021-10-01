TEMPLATE = app
CONFIG += console use_c_linker
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CFLAGS_DEBUG += -std=c11 -Wall -Wextra -g -O0
QMAKE_CFLAGS_RELEASE += -std=c11 -s -O3 -Wall -Wextra






SOURCES += \
    src/cb_compress.c \
    src/cb_file.c \
    src/cbfilegrabber2.c \
    src/data/list.c \
    src/miniz/miniz.c

HEADERS += \
    src/cb_compress.h \
    src/cb_file.h \
    src/cbfilegrabber2.h \
    src/data/list.h \
    src/miniz/miniz.h
