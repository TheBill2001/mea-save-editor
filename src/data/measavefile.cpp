#include "measavefile.hpp"

#include "measavefileheader.hpp"
#include "p_measavefileutils.hpp"
#include "utils/number.hpp"

#include <zlib.h>

#include <KLocalizedString>

namespace
{

constexpr auto crc32HashSeed = 0x12345678;
constexpr quint64 signature = Utils::Number::swapEndian(0x46424348554E4B53); // "FBCHUNKS" in big endian
constexpr auto fileHeaderSize = 18;

}

MEASaveFile::MEASaveFile(QObject *parent)
    : QObject{parent}
{
}

quint16 MEASaveFile::version() const
{
    return m_version;
}

void MEASaveFile::setVersion(quint16 newVersion)
{
    if (m_version == newVersion) {
        return;
    }
    m_version = newVersion;
    Q_EMIT versionChanged(newVersion);
}

MEASaveFileHeader *MEASaveFile::header() const
{
    return m_header;
}

MEASaveFile *MEASaveFile::fromData(const QByteArray &data, MEASaveFileError *p_error)
{
    MEASAVEFILE_FROMDATA_DECLARE(MEASaveFile, result, stream, data)

    if (data.length() < fileHeaderSize) {
        RET_ERR(p_error, NotEnoughData)
    }

    {
        quint64 magic;
        stream >> magic;

        if (magic != signature) {
            RET_ERR(p_error, InvalidSignature)
        }
    }

    stream >> result->m_version;
    if (result->m_version != 1) {
        RET_ERR(p_error, UnsupportedVersion)
    }

    quint32 headerSize;
    stream >> headerSize;

    quint32 dataSize;
    stream >> dataSize;

    if (fileHeaderSize + headerSize + dataSize < data.length()) {
        RET_ERR(p_error, NotEnoughData)
    }

    {
        QByteArray headerBytes(headerSize, Qt::Uninitialized);
        stream.readRawData(headerBytes.data(), headerBytes.size());

        QDataStream headerStream(headerBytes);
        headerStream.setByteOrder(QDataStream::LittleEndian);

        quint32 headerHash;
        headerStream >> headerHash;

        QByteArray headerData(headerSize - 4, Qt::Uninitialized);
        headerStream.readRawData(headerData.data(), headerData.size());

        quint32 computedHash = crc32(crc32HashSeed, reinterpret_cast<const quint8 *>(headerData.constData()), headerData.size());
        if (headerHash != computedHash) {
            RET_ERR_MSG(p_error, ChecksumMismatch, i18nc("MEASaveFileReadError", "Header checksum mismatch"))
        }

        RET_ERR_READ_OBJ(MEASaveFileHeader, result, m_header, headerData, p_error)
    }

    {
        auto dataBytes = QByteArray(dataSize, Qt::Uninitialized);
        stream.readRawData(dataBytes.data(), dataBytes.size());

        QDataStream dataStream(dataBytes);
        dataStream.setByteOrder(QDataStream::LittleEndian);

        quint32 dataHash;
        dataStream >> dataHash;

        QByteArray data(dataSize - 4, Qt::Uninitialized);
        dataStream.readRawData(data.data(), data.size());

        quint32 computedHash = crc32(crc32HashSeed, reinterpret_cast<const quint8 *>(data.constData()), data.size());
        if (dataHash != computedHash) {
            RET_ERR_MSG(p_error, ChecksumMismatch, i18nc("MEASaveFileReadError", "Data checksum mismatch"))
        }

        result->m_data = data;
    }

    return result.release();
}

QByteArray MEASaveFile::toData(MEASaveFileError *p_error) const
{
    MEASAVEFILE_TODATA_DELCARE(data, stream)

    stream << signature;
    stream << m_version;

    const auto headerData = m_header->toData();

    WRITE_DATA(stream, headerData.length() + 4, quint32, p_error, i18nc("MEASaveFileError", "Save header is too large"))
    WRITE_DATA(stream, m_data.length() + 4, quint32, p_error, i18nc("MEASaveFileError", "Save data is too large"))

    quint32 computedHash = crc32(crc32HashSeed, reinterpret_cast<const quint8 *>(headerData.constData()), headerData.size());
    stream << computedHash;
    stream.writeRawData(headerData.data(), headerData.length());

    computedHash = crc32(crc32HashSeed, reinterpret_cast<const quint8 *>(m_data.constData()), m_data.size());
    stream << computedHash;
    stream.writeRawData(m_data.data(), m_data.length());

    return data;
}
