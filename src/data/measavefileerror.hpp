// SPDX-FileCopyrightText: 2025 Trần Nam Tuấn <tuantran1632001@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MEASAVEFILEERROR_H
#define MEASAVEFILEERROR_H

#include <QMetaType>
#include <QtQmlIntegration/qqmlintegration.h>

class MEASaveFileError
{
    Q_GADGET
    QML_VALUE_TYPE(meaSaveFileReadError)
    Q_PROPERTY(MEASaveFileError::Error error READ error CONSTANT FINAL)
    Q_PROPERTY(QString errorString READ errorString CONSTANT FINAL)
public:
    enum Error {
        NoError = 0,
        InvalidPath,
        IOError,
        NotEnoughData,
        TooMuchData,
        InvalidSignature,
        UnsupportedVersion,
        ChecksumMismatch,
    };

    MEASaveFileError(Error error = NoError, QStringView errorString = {});

    operator QString() const;
    bool operator==(const MEASaveFileError &other);

    Error error() const;
    QString errorString() const;

private:
    Error m_error;
    QString m_errorString;
};

Q_DECLARE_METATYPE(MEASaveFileError)

#endif // MEASAVEFILEERROR_H
