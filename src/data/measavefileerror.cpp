#include "measavefileerror.hpp"

#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

MEASaveFileError::MEASaveFileError(Error error, QStringView errorString)
    : m_error{error}
    , m_errorString{errorString}
{
    if (errorString.isEmpty()) {
        switch (error) {
        case NoError:
            this->m_errorString = i18nc("MEASaveFileReadError", "No error");
            break;
        case InvalidPath:
            this->m_errorString = i18nc("MEASaveFileReadError", "Invalid file path");
            break;
        case IOError:
            this->m_errorString = i18nc("MEASaveFileReadError", "File reading error");
            break;
        case NotEnoughData:
            this->m_errorString = i18nc("MEASaveFileReadError", "Not enough data");
            break;
        case InvalidSignature:
            this->m_errorString = i18nc("MEASaveFileReadError", "Invalid signature");
            break;
        case UnsupportedVersion:
            this->m_errorString = i18nc("MEASaveFileReadError", "Unsupported version");
            break;
        case ChecksumMismatch:
            this->m_errorString = i18nc("MEASaveFileReadError", "Mismatched checksum");
            break;
        case TooMuchData:
            this->m_errorString = i18nc("MEASaveFileReadError", "Data is too large");
            break;
        }
    }
}

MEASaveFileError::operator QString() const
{
    return m_errorString;
}

bool MEASaveFileError::operator==(const MEASaveFileError &other)
{
    return m_error == other.m_error && m_errorString == other.m_errorString;
}

MEASaveFileError::Error MEASaveFileError::error() const
{
    return m_error;
}

QString MEASaveFileError::errorString() const
{
    return m_errorString;
}
