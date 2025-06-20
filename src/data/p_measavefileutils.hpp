#ifndef MEASAVEFILECOMMON_HPP
#define MEASAVEFILECOMMON_HPP

#define RET_ERR(p_error, err)                                                                                                                                  \
    if (p_error != nullptr) {                                                                                                                                  \
        *p_error = MEASaveFileError(MEASaveFileError::err);                                                                                                    \
    }                                                                                                                                                          \
    return {};

#define RET_ERR_MSG(p_error, err, message)                                                                                                                     \
    if (p_error != nullptr) {                                                                                                                                  \
        *p_error = MEASaveFileError(MEASaveFileError::err, message);                                                                                           \
    }                                                                                                                                                          \
    return {};

#define RET_ERR_READ_OBJ(TYPE, dest, member, data, p_error)                                                                                                    \
    {                                                                                                                                                          \
        auto ret = TYPE::fromData(data, p_error);                                                                                                              \
        if (!ret) {                                                                                                                                            \
            return {};                                                                                                                                         \
        }                                                                                                                                                      \
        dest->member = ret;                                                                                                                                    \
        dest->member->setParent(dest.get());                                                                                                                   \
    }

#define MEASAVEFILE_FROMDATA_DECLARE(TYPE, result, stream, data)                                                                                               \
    std::unique_ptr<TYPE> result(new TYPE());                                                                                                                  \
                                                                                                                                                               \
    QDataStream stream(data);                                                                                                                                  \
    stream.setByteOrder(QDataStream::LittleEndian);

#define MEASAVEFILE_TODATA_DELCARE(data, stream)                                                                                                               \
    QByteArray data;                                                                                                                                           \
    QDataStream stream(&data, QDataStream::WriteOnly);                                                                                                         \
    stream.setByteOrder(QDataStream::LittleEndian);

#define WRITE_STRING(stream, string, sizeT, p_error, message)                                                                                                  \
    {                                                                                                                                                          \
        const auto stringBytes = (string).toUtf8();                                                                                                            \
        if (stringBytes.length() > std::numeric_limits<sizeT>::max()) {                                                                                        \
            RET_ERR_MSG(p_error, TooMuchData, message)                                                                                                         \
        }                                                                                                                                                      \
        stream << sizeT(stringBytes.length());                                                                                                                 \
        stream.writeRawData(stringBytes.constData(), stringBytes.length());                                                                                    \
    }

#define WRITE_DATA(stream, value, type, p_error, message)                                                                                                      \
    {                                                                                                                                                          \
        const auto _value = value;                                                                                                                             \
        if (_value > std::numeric_limits<type>::max() || _value < std::numeric_limits<type>::min()) {                                                          \
            RET_ERR_MSG(p_error, TooMuchData, message)                                                                                                         \
        }                                                                                                                                                      \
        stream << type(_value);                                                                                                                                \
    }

#endif // MEASAVEFILECOMMON_HPP
