#include "measavefilemanager.hpp"

#include "measaveeditorconfig.hpp"
#include "measavefile.hpp"

#include <stack>

#include <QApplicationStatic>
#include <QDir>

#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

namespace
{

constexpr auto maxBackupFileCount = 999;

QString getBackupFilePath(const QString &fileName, quint16 index)
{
    return fileName + u".bak%1"_s.arg(index, 3, 10, '0'_L1);
}

}

class MEASaveFileManagerStatic
{
    Q_DISABLE_COPY_MOVE(MEASaveFileManagerStatic)
public:
    MEASaveFileManager *const instance;

    MEASaveFileManagerStatic()
        : instance{new MEASaveFileManager()}
    {
    }
};

Q_APPLICATION_STATIC(MEASaveFileManagerStatic, s_static)

MEASaveFileManager *MEASaveFileManager::instance()
{
    return s_static->instance;
}

MEASaveFileManager *MEASaveFileManager::create(QQmlEngine *, QJSEngine *)
{
    return instance();
}

MEASaveFile *MEASaveFileManager::saveFile() const
{
    return m_saveFile;
}

QString MEASaveFileManager::fileName() const
{
    if (m_lastOpenFile.isEmpty() || !m_lastOpenFile.isValid() || !m_lastOpenFile.isLocalFile()) {
        return {};
    }

    QFileInfo fileInfo(m_lastOpenFile.toLocalFile());
    return fileInfo.fileName();
}

void MEASaveFileManager::loadSaveFile(const QUrl &url)
{
    if (!url.isLocalFile()) {
        return emitLoadError({MEASaveFileError::InvalidPath, i18nc("MEASaveFileError", "File path is not local")});
    }

    const auto filePath = url.toLocalFile();
    qInfo().noquote() << u"Read save file '%1'"_s.arg(filePath);

    {
        QFileInfo fileInfo(filePath);
        fileInfo.refresh();

        if (!fileInfo.exists()) {
            return emitLoadError({MEASaveFileError::InvalidPath, i18nc("MEASaveFileError", "Path does not exist")});
        }

        if (fileInfo.isDir()) {
            return emitLoadError({MEASaveFileError::InvalidPath, i18nc("MEASaveFileError", "Path is a directory")});
        }

        if (!fileInfo.isFile()) {
            return emitLoadError({MEASaveFileError::InvalidPath});
        }

        if (!fileInfo.isReadable()) {
            return emitLoadError({MEASaveFileError::IOError, i18nc("MEASaveFileError", "File is not readable")});
        }

        MEASaveEditorConfig::instance()->setLastOpenDir(fileInfo.path());
    }

    QFile file(filePath);
    if (!file.open(QFile::ReadOnly)) {
        return emitLoadError({MEASaveFileError::IOError, i18nc("MEASaveFileError", "Failed to open file: %1", file.errorString())});
    }

    MEASaveFileError error;
    std::unique_ptr<MEASaveFile> saveFile(MEASaveFile::fromData(file.readAll(), &error));

    if (error.error() != MEASaveFileError::NoError) {
        return emitLoadError(error);
    }

    setSaveFile(saveFile.release());
    setLastOpenFile(url);
}

void MEASaveFileManager::reload()
{
    loadSaveFile(MEASaveEditorConfig::instance()->lastOpenDirUrl());
}

void MEASaveFileManager::save(const QUrl &a_url, bool overwrite)
{
    if (!m_saveFile) {
        return;
    }

    const QUrl url = a_url.isEmpty() ? m_lastOpenFile : a_url;

    if (!url.isValid()) {
        return emitSaveError({MEASaveFileError::InvalidPath});
    }

    if (!url.isLocalFile()) {
        return emitSaveError({MEASaveFileError::InvalidPath, i18nc("MEASaveFileError", "File path is not local")});
    }

    const auto filePath = url.toLocalFile();
    qInfo().noquote() << u"Write save file '%1'"_s.arg(filePath);

    QFileInfo fileInfo(filePath);
    fileInfo.refresh();

    if (fileInfo.isDir()) {
        return emitSaveError({MEASaveFileError::InvalidPath, i18nc("MEASaveFileError", "Path is a directory")});
    }

    if (fileInfo.isFile()) {
        if (!fileInfo.isWritable()) {
            return emitSaveError({MEASaveFileError::IOError, i18nc("MEASaveFileError", "File is not writable")});
        }

        if (!overwrite) {
            if (!doBackup(fileInfo.filePath())) {
                return;
            }
        }
    }

    MEASaveFileError error;
    const auto data = m_saveFile->toData(&error);

    if (error.error() != MEASaveFileError::NoError) {
        return emitSaveError(error);
    }

    QFile file(fileInfo.filePath());
    if (!file.open(QFile::WriteOnly)) {
        return emitSaveError({MEASaveFileError::IOError, i18nc("MEASaveFileError", "Cannot open file for writing: %1", file.errorString())});
    }

    file.write(data);
    setLastOpenFile(url);
}

void MEASaveFileManager::emitLoadError(const MEASaveFileError &error)
{
    Q_EMIT loadErrorOccurred(error);
}

void MEASaveFileManager::emitSaveError(const MEASaveFileError &error)
{
    Q_EMIT saveErrorOccurred(error);
}

void MEASaveFileManager::setSaveFile(MEASaveFile *saveFile)
{
    if (m_saveFile == saveFile) {
        return;
    }

    if (m_saveFile && (!m_saveFile->parent() || m_saveFile->parent() == this)) {
        delete m_saveFile;
    }

    m_saveFile = saveFile;

    if (m_saveFile) {
        m_saveFile->moveToThread(this->thread());
        m_saveFile->setParent(this);
    }

    Q_EMIT saveFileChanged(saveFile);
}

bool MEASaveFileManager::doBackup(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    std::stack<std::tuple<QString, quint16, QString>> stack;
    stack.emplace(fileInfo.filePath(), 0, getBackupFilePath(fileInfo.filePath(), 0));

    while (!stack.empty()) {
        const auto current = stack.top();
        const auto currentFilePath = std::get<0>(current);
        const auto backupIndex = std::get<1>(current);
        const auto backupFilePath = std::get<2>(current);

        {
            QFile backupFile(backupFilePath);
            if (backupFile.exists()) {
                if (backupIndex == maxBackupFileCount) {
                    if (!backupFile.remove()) {
                        emitSaveError({MEASaveFileError::IOError, u"Cannot remove backup file '%1': %2"_s.arg(backupFilePath, backupFile.errorString())});
                        return false;
                    }
                } else {
                    const auto nextBackupIndex = backupIndex + 1;
                    stack.emplace(backupFilePath, nextBackupIndex, getBackupFilePath(fileInfo.filePath(), nextBackupIndex));
                    continue;
                }
            }
        }

        {
            QFile file(currentFilePath);
            if (!file.rename(backupFilePath)) {
                emitSaveError({MEASaveFileError::IOError, u"Cannot backup file '%1' to '%2': %3"_s.arg(currentFilePath, backupFilePath, file.errorString())});
                return false;
            }
        }

        stack.pop();
    }

    return true;
}

void MEASaveFileManager::setLastOpenFile(const QUrl &url)
{
    if (m_lastOpenFile == url) {
        return;
    }
    m_lastOpenFile = url;
    Q_EMIT fileNameChanged();
}
