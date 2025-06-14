#include "mainwindow.hpp"
#include "utils/version.h"

#include <QApplication>

#ifdef Q_OS_WINDOWS
#include <Windows.h>
#endif

using namespace Qt::Literals::StringLiterals;

int main(int argc, char *argv[])
{
#ifdef QT_DEBUG
    qSetMessagePattern(QStringLiteral("[%{time yyyy-MM-dd h:mm:ss}] [%{type}] [%{file}:%{line}] %{message}"));
#else
    qSetMessagePattern(QStringLiteral("[%{time yyyy-MM-dd h:mm:ss}] [%{type}] %{message}"));
#endif

    QApplication a(argc, argv);

#ifdef Q_OS_WINDOWS
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#endif

    QApplication::setApplicationName(u"mea-save-editor"_s);
    QApplication::setApplicationDisplayName(u"Mass Effect: Andromeda Save Editor"_s);
    QApplication::setApplicationVersion(QStringLiteral(MEA_SAVE_EDITOR_VERSION_STRING));
    QApplication::setOrganizationName(u"thebill2001"_s);

#ifdef Q_OS_LINUX
    QApplication::setWindowIcon(QIcon::fromTheme(u"io.github.thebill2001.mea-save-editor"_s));
    QApplication::setDesktopFileName(u"io.github.thebill2001.mea-save-editor"_s);
#elif defined(Q_OS_WINDOWS)
    // QApplication::setWindowIcon(QIcon::fromTheme(u"io.github.thebill2001.mea-save-editor"_s));
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
