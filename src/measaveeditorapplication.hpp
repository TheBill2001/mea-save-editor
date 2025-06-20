// SPDX-FileCopyrightText: 2025 Trần Nam Tuấn <tuantran1632001@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MEASAVEEDITORAPPLICATION_HPP
#define MEASAVEEDITORAPPLICATION_HPP

#include <AbstractKirigamiApplication>
#include <KStandardActions>
#include <QtQmlIntegration/qqmlintegration.h>

using namespace Qt::StringLiterals;

class MEASaveEditorApplication : public AbstractKirigamiApplication
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Action {
        Open = KStandardActions::Open,
        Save = KStandardActions::Save,
        SaveAs = KStandardActions::SaveAs,
        Revert = KStandardActions::Revert
    };
    Q_ENUM(Action)

    explicit MEASaveEditorApplication(QObject *parent = nullptr);

    Q_INVOKABLE QAction *action(const QString &actionName);
    Q_INVOKABLE QAction *action(Action action);

Q_SIGNALS:
    void open();
    void saveAs();

private:
    void setupActions() override;
};

#endif // MEASAVEEDITORAPPLICATION_HPP
