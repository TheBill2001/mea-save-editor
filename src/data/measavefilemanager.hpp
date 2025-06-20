#ifndef MEASAVEFILEMANAGER_HPP
#define MEASAVEFILEMANAGER_HPP

#include "measavefileerror.hpp"

#include <QObject>
#include <QUrl>

class QQmlEngine;
class QJSEngine;
class MEASaveFile;
class MEASaveFileManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(MEASaveFile *saveFile READ saveFile WRITE setSaveFile NOTIFY saveFileChanged FINAL)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged FINAL)
private:
    friend class MEASaveFileManagerStatic;
    MEASaveFileManager() = default;

public:
    static MEASaveFileManager *instance();
    static MEASaveFileManager *create(QQmlEngine *, QJSEngine *);

    MEASaveFileError error() const;
    MEASaveFile *saveFile() const;

    QString fileName() const;

public Q_SLOTS:
    void loadSaveFile(const QUrl &url);
    void reload();
    void save(const QUrl &url = {}, bool overwrite = false);

Q_SIGNALS:
    void loadErrorOccurred(const MEASaveFileError &error);
    void saveErrorOccurred(const MEASaveFileError &error);
    void saveFileChanged(MEASaveFile *saveFile);
    void fileNameChanged();

private:
    MEASaveFile *m_saveFile = nullptr;

    QUrl m_lastOpenFile;

    void emitLoadError(const MEASaveFileError &error);
    void emitSaveError(const MEASaveFileError &error);
    void setSaveFile(MEASaveFile *saveFile);

    bool doBackup(const QString &filePath);

    void setLastOpenFile(const QUrl &url);
};

#endif // MEASAVEFILEMANAGER_HPP
