// SPDX-FileCopyrightText: 2025 Trần Nam Tuấn <tuantran1632001@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include "measaveeditor-version.hpp"
#include "measavefileerror.hpp"

#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QUrl>

#include <KAboutData>
#include <KIconTheme>
#include <KLocalizedQmlContext>
#include <KLocalizedString>

#ifdef Q_OS_WINDOWS
#include <QFont>

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

    KIconTheme::initTheme();
    QIcon::setFallbackThemeName("breeze"_L1);
    QApplication app(argc, argv);

    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(u"org.kde.desktop"_s);
    }

#ifdef Q_OS_WINDOWS
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    QApplication::setStyle(QStringLiteral("breeze"));
    auto font = app.font();
    font.setPointSize(10);
    app.setFont(font);
#endif

    QMetaType::registerConverter<MEASaveFileError, QString>();

    KLocalizedString::setApplicationDomain("MEASaveEditor");
    QCoreApplication::setOrganizationName(u"KDE"_s);

    KAboutData aboutData(u"MEASaveEditor"_s,
                         i18nc("@title", "Mass Effect: Andromeda Save Editor"),
                         QStringLiteral(MEASAVEEDITOR_VERSION_STRING),
                         i18n("Mass Effect: Andromeda Save Editor"),
                         KAboutLicense::GPL_V3,
                         i18n("(c) 2025, Trần Nam Tuấn"));
    aboutData.addAuthor(i18nc("@info:credit", "Trần Nam Tuấn"),
                        i18nc("@info:credit", "Maintainer"),
                        u"tuantran1632001@gmail.com"_s,
                        u"https://github.com/TheBill2001"_s);
    aboutData.setTranslator(i18nc("NAME OF TRANSLATORS", "Trần Nam Tuấn"), i18nc("EMAIL OF TRANSLATORS", "tuantran1632001@gmail.com"));
    aboutData.setDesktopFileName(u"thebill2001.mea-save-editor"_s);
    aboutData.setBugAddress("https://github.com/TheBill2001/mea-save-editor/issues");
    aboutData.setHomepage(u"https://github.com/TheBill2001/mea-save-editor"_s);
    KAboutData::setApplicationData(aboutData);
    QGuiApplication::setWindowIcon(QIcon::fromTheme(u"applications-developmen"_s));

    QQmlApplicationEngine engine;

    KLocalization::setupLocalizedContext(&engine);
    engine.loadFromModule("thebill2001.measaveeditor", u"Main"_s);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
