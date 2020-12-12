#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDir>

#include "player.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Player Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt MultiMedia Player Example");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", "The URL to open.");
    parser.process(app);

    Player player;

    if (!parser.positionalArguments().isEmpty() && player.isPlayerAvailable()) {
        QList<QUrl> urls;
        foreach (const QString &a, parser.positionalArguments())
            urls.append(QUrl::fromUserInput(a, QDir::currentPath(), QUrl::AssumeLocalFile));
        player.addToPlaylist(urls);
    }

#if defined(Q_WS_SIMULATOR)
    player.setAttribute(Qt::WA_LockLandscapeOrientation);
    player.showMaximized();
#else
    player.show();
#endif
    return app.exec();
}
