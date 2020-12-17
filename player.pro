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
    videowidget.h \
    utils.h \
    database.h \
    absolutesetstyle.h \
    playlist/playlistdelegate.h \
    playlist/playlistmodel.h \
    playlist/playlistitem.h \
    library/library.h \
    library/videogridmodel.h \
    library/videogriddelegate.h \
    library/videoitem.h \
    library/addvideo.h \
    library/taglistmodel.h

SOURCES = main.cpp \
    player.cpp \
    playercontrols.cpp \
    utils.cpp \
    database.cpp \
    videowidget.cpp \
    playlist/playlistmodel.cpp \
    playlist/playlistdelegate.cpp \
    library/library.cpp \
    library/videogridmodel.cpp \
    library/videogriddelegate.cpp \
    library/videoitem.cpp \
    library/addvideo.cpp \
    library/taglistmodel.cpp
    
target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
INSTALLS += target

RESOURCES += \
    img/img.qrc
