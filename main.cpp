#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDir>

#include "player.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Tomeo");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QCommandLineParser parser;
    parser.setApplicationDescription("Tomeo Video Player");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("dir", "The directory to open.");
    parser.process(app);

    Player player;

    if (!parser.positionalArguments().isEmpty() && player.isPlayerAvailable()) {
        QList<QUrl> urls;
        foreach (const QString &a, parser.positionalArguments())
            urls.append(QUrl::fromUserInput(a, QDir::currentPath(), QUrl::AssumeLocalFile));
        //        player.addToPlaylist(urls);
    }

    player.show();
    return app.exec();
}
