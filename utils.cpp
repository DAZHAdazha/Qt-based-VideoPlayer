#include "utils.h"

#include <QImageReader>

QPixmap loadThumbnail(const QString &path) {
    auto thumbPath = path.left(path.length() - 4) + ".png";

    if (!QFile(thumbPath).exists()) {
        qDebug() << "warning: I couldn't find thumbnail " << thumbPath << endl;
        return QPixmap();
    }
    return QPixmap(thumbPath);
}