#ifndef MEASAVEFILE_HPP
#define MEASAVEFILE_HPP

#include "measavefileerror.hpp"

#include <QObject>

class MEASaveFileHeader;
class MEASaveFile : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Created by MEASaveFileManager")
    Q_PROPERTY(quint16 version READ version WRITE setVersion NOTIFY versionChanged FINAL)
    Q_PROPERTY(MEASaveFileHeader *header READ header CONSTANT FINAL)
public:
    explicit MEASaveFile(QObject *parent = nullptr);

    quint16 version() const;
    void setVersion(quint16 newVersion);

    MEASaveFileHeader *header() const;

    static MEASaveFile *fromData(const QByteArray &data, MEASaveFileError *p_error);
    QByteArray toData(MEASaveFileError *p_error = nullptr) const;

Q_SIGNALS:
    void versionChanged(quint16 version);

private:
    quint16 m_version;
    MEASaveFileHeader *m_header;
    QByteArray m_data;
    // SaveFileData *m_data;
};

Q_MOC_INCLUDE("measavefileheader.hpp")

#endif // MEASAVEFILE_HPP
