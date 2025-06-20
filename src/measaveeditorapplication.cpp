// SPDX-FileCopyrightText: 2025 Trần Nam Tuấn <tuantran1632001@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include "measaveeditorapplication.hpp"

#include "measavefilemanager.hpp"

#include <KLocalizedString>

using namespace Qt::StringLiterals;

MEASaveEditorApplication::MEASaveEditorApplication(QObject *parent)
    : AbstractKirigamiApplication(parent)
{
    MEASaveEditorApplication::setupActions();
}

QAction *MEASaveEditorApplication::action(const QString &actionName)
{
    return AbstractKirigamiApplication::action(actionName);
}

QAction *MEASaveEditorApplication::action(Action action)
{
    return AbstractKirigamiApplication::action(KStandardActions::name(static_cast<KStandardActions::StandardAction>(action)));
}

void MEASaveEditorApplication::setupActions()
{
    AbstractKirigamiApplication::setupActions();

    auto openAction = KStandardActions::open(this, &MEASaveEditorApplication::open, this);
    mainCollection()->addAction(KStandardActions::name(KStandardActions::Open), openAction);

    auto saveAction = KStandardActions::save(
        MEASaveFileManager::instance(),
        []() {
            MEASaveFileManager::instance()->save();
        },
        this);
    saveAction->setDisabled(true);
    mainCollection()->addAction(KStandardActions::name(KStandardActions::Save), saveAction);

    auto saveAsAction = KStandardActions::saveAs(this, &MEASaveEditorApplication::saveAs, this);
    saveAsAction->setDisabled(true);
    mainCollection()->addAction(KStandardActions::name(KStandardActions::SaveAs), saveAsAction);

    auto revertAction = KStandardActions::revert(MEASaveFileManager::instance(), &MEASaveFileManager::reload, this);
    revertAction->setDisabled(true);
    revertAction->setShortcut({Qt::CTRL | Qt::Key_F5});
    mainCollection()->addAction(KStandardActions::name(KStandardActions::Revert), revertAction);

    connect(MEASaveFileManager::instance(), &MEASaveFileManager::saveFileChanged, this, [saveAction, saveAsAction, revertAction](MEASaveFile *saveFile) {
        bool disable = !saveFile;
        saveAction->setDisabled(disable);
        saveAsAction->setDisabled(disable);
        revertAction->setDisabled(disable);
    });

    readSettings();
}
