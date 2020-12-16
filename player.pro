TEMPLATE = app
TARGET = player

QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets \
      sql

HEADERS = \
    player.h \
    playercontrols.h \
    playlistmodel.h \
    videowidget.h \
    playlistdelegate.h \
    playlistitem.h \
    absolutesetstyle.h \
    library.h \
    videogridmodel.h \
    videogriddelegate.h \
    database.h \
    videoitem.h \
    addvideo.h

SOURCES = main.cpp \
    player.cpp \
    playercontrols.cpp \
    playlistmodel.cpp \
    videowidget.cpp \
    playlistdelegate.cpp \
    library.cpp \
    videogridmodel.cpp \
    videogriddelegate.cpp \
    database.cpp \
    videoitem.cpp \
    addvideo.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
INSTALLS += target

RESOURCES += \
    img/img.qrc
