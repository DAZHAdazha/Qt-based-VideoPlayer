#include <QApplication>

#include "library/library.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Tomeo");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QFontDatabase::addApplicationFont("qrc:///resources:/font/Eczar-Regular.ttf");
    QFontDatabase::addApplicationFont("qrc:///resources:/font/RobotoCondensed-Regular.ttf");
    QFontDatabase::addApplicationFont("qrc:///resources:/font/WorkSans-Bold.ttf");
    Library library;
    library.show();

    return app.exec();
}
