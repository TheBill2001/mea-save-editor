// SPDX-FileCopyrightText: 2025 Trần Nam Tuấn <tuantran1632001@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import QtQuick.Dialogs

import org.kde.kirigami as Kirigami
// import org.kde.kirigamiaddons.formcard as FormCard
import org.kde.kirigamiaddons.components as KAComponents
import org.kde.kirigamiaddons.statefulapp as StatefulApp

import thebill2001.measaveeditor

StatefulApp.StatefulWindow {
    id: root

    title: MEASaveFileManager.fileName
    windowName: "MEASaveEditor"

    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    application: MEASaveEditorApplication {
        id: meaSaveEditorApp
    }

    globalDrawer: Kirigami.GlobalDrawer {
        isMenu: true
        actions: [
            Kirigami.Action {
                fromQAction: meaSaveEditorApp.action(MEASaveEditorApplication.Open)
            },
            Kirigami.Action {
                fromQAction: meaSaveEditorApp.action(MEASaveEditorApplication.Save)
            },
            Kirigami.Action {
                fromQAction: meaSaveEditorApp.action(MEASaveEditorApplication.SaveAs)
            },
            Kirigami.Action {
                fromQAction: meaSaveEditorApp.action(MEASaveEditorApplication.Revert)
            },
            Kirigami.Action {
                separator: true
            },
            Kirigami.Action {
                fromQAction: meaSaveEditorApp.action("options_configure_keybinding")
            },
            Kirigami.Action {
                separator: true
            },
            Kirigami.Action {
                id: aboutAction
                fromQAction: meaSaveEditorApp.action("open_about_page")
            },
            Kirigami.Action {
                fromQAction: meaSaveEditorApp.action("file_quit")
            }
        ]
    }

    pageStack.initialPage: landingPageComponent

    Kirigami.Action {
        fromQAction: meaSaveEditorApp.action("open_kcommand_bar")
    }

    Connections {
        target: meaSaveEditorApp

        function onOpen() {
            let fileDialog = fileDialogComponent.createObject(root) as FileDialog

            fileDialog.title = i18nc("@title File dialog", "Open Save File")
            fileDialog.options = FileDialog.ReadOnly
            fileDialog.fileMode = FileDialog.OpenFile
            fileDialog.currentFolder = MEASaveEditorConfig.lastOpenDirUrl
            fileDialog.nameFilters = [
                i18nc("@label:listbox File dialog filter", "Mass Effect: Andromeda Save Files (%1)", "Career*"),
                i18nc("@label:listbox File dialog filter", "All Files (%1)", "*")
            ]
            fileDialog.accepted.connect(() => MEASaveFileManager.loadSaveFile(fileDialog.selectedFile))
            fileDialog.open()
        }

        function onSaveAs() {
            let fileDialog = fileDialogComponent.createObject(root) as FileDialog

            fileDialog.title = i18nc("@title File dialog", "Save Save File")
            fileDialog.fileMode = FileDialog.SaveFile
            fileDialog.currentFolder = MEASaveEditorConfig.lastOpenDirUrl
            fileDialog.nameFilters = [
                i18nc("@label:listbox File dialog filter", "Mass Effect: Andromeda Save Files (%1)", "Career*"),
                i18nc("@label:listbox File dialog filter", "All Files (%1)", "*")
            ]
            fileDialog.accepted.connect(() => MEASaveFileManager.save(fileDialog.selectedFile, true))
            fileDialog.open()
        }
    }

    Component {
        id: landingPageComponent

        Kirigami.Page {

            title: i18nc("@title", "Mass Effect: Andromeda Save Editor")

            ColumnLayout {
                anchors.centerIn: parent

                Kirigami.Icon {
                    source: "applications-development"
                    implicitWidth: Math.round(Kirigami.Units.iconSizes.huge * 1.5)
                    implicitHeight: Math.round(Kirigami.Units.iconSizes.huge * 1.5)

                    Layout.alignment: Qt.AlignHCenter
                    Layout.bottomMargin: Kirigami.Units.largeSpacing * 4
                }

                QQC2.Label {
                    text: i18n("Open a Save to begin")

                    Layout.alignment: Qt.AlignHCenter
                }

                QQC2.Button {
                    action: Kirigami.Action {
                        fromQAction: meaSaveEditorApp.action(MEASaveEditorApplication.Open)
                    }

                    Layout.alignment: Qt.AlignHCenter
                    Layout.topMargin: Kirigami.Units.largeSpacing
                }
            }
        }
    }

    Component {
        id: fileDialogComponent

        FileDialog {
            onVisibleChanged: {
                if (!visible) {
                    destroy()
                }
            }
        }
    }

    Component {
        id: errorDialogComponent

        KAComponents.MessageDialog {
            id: errorDialog

            property string errorMessage;

            dialogType: KAComponents.MessageDialog.Error
            standardButtons: KAComponents.MessageDialog.Close
            closePolicy: KAComponents.MessageDialog.CloseOnEscape

            QQC2.Label {
                text: errorDialog.errorMessage
            }

            onClosed: destroy()
            onRejected: close()
        }
    }

    Connections {
        target: MEASaveFileManager

        function onLoadErrorOccurred(error: meaSaveFileReadError) {
            let errorDialog = errorDialogComponent.createObject(root)

            errorDialog.title = i18nc("@title", "Cannot load save file")
            errorDialog.errorMessage = error.errorString

            errorDialog.open()
            root.alert(1000)
        }

        function onSaveErrorOccurred(error: meaSaveFileReadError) {
            let errorDialog = errorDialogComponent.createObject(root)

            errorDialog.title = i18nc("@title", "Cannot save save file")
            errorDialog.errorMessage = error.errorString

            errorDialog.open()
            root.alert(1000)
        }
    }
}
