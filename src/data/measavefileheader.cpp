#include "measavefileheader.hpp"

#include "p_measavefileutils.hpp"
#include "utils/datetime.hpp"
#include "utils/number.hpp"

#include <QMetaEnum>

#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

namespace
{

constexpr quint64 signature = Utils::Number::swapEndian(0x4642484541444552); // "FBHEADER" in big endian

}

quint16 MEASaveFileHeader::version() const
{
    return m_version;
}

void MEASaveFileHeader::setVersion(quint16 version)
{
    if (m_version == version) {
        return;
    }
    m_version = version;
    Q_EMIT versionChanged(version);
}

QString MEASaveFileHeader::areaNameStringId() const
{
    return m_areaNameStringId;
}

void MEASaveFileHeader::setAreaNameStringId(const QString &areaNameStringId)
{
    if (m_areaNameStringId == areaNameStringId) {
        return;
    }
    m_areaNameStringId = areaNameStringId;
    Q_EMIT areaNameStringIdChanged(areaNameStringId);
}

QString MEASaveFileHeader::areaThumbnailTextureId() const
{
    return m_areaThumbnailTextureId;
}

void MEASaveFileHeader::setAreaThumbnailTextureId(const QString &areaThumbnailTextureId)
{
    if (m_areaThumbnailTextureId == areaThumbnailTextureId) {
        return;
    }
    m_areaThumbnailTextureId = areaThumbnailTextureId;
    Q_EMIT areaThumbnailTextureIdChanged(areaThumbnailTextureId);
}

QString MEASaveFileHeader::gameVersion() const
{
    return m_gameVersion;
}

void MEASaveFileHeader::setGameVersion(const QString &gameVersion)
{
    if (m_gameVersion == gameVersion) {
        return;
    }
    m_gameVersion = gameVersion;
    Q_EMIT gameVersionChanged(gameVersion);
}

QString MEASaveFileHeader::requiredDLC() const
{
    return m_requiredDLC;
}

void MEASaveFileHeader::setRequiredDLC(const QString &requiredDLC)
{
    if (m_requiredDLC == requiredDLC) {
        return;
    }
    m_requiredDLC = requiredDLC;
    Q_EMIT requiredDLCChanged(requiredDLC);
}

QString MEASaveFileHeader::requiredInstallGroup() const
{
    return m_requiredInstallGroup;
}

void MEASaveFileHeader::setRequiredInstallGroup(const QString &requiredInstallGroup)
{
    if (m_requiredInstallGroup == requiredInstallGroup) {
        return;
    }
    m_requiredInstallGroup = requiredInstallGroup;
    Q_EMIT requiredInstallGroupChanged(requiredInstallGroup);
}

QString MEASaveFileHeader::profileName() const
{
    return m_profileName;
}

void MEASaveFileHeader::setProfileName(const QString &profileName)
{
    if (m_profileName == profileName) {
        return;
    }
    m_profileName = profileName;
    Q_EMIT profileNameChanged(profileName);
}

QString MEASaveFileHeader::profileUniqueName() const
{
    return m_profileUniqueName;
}

void MEASaveFileHeader::setProfileUniqueName(const QString &profileUniqueName)
{
    if (m_profileUniqueName == profileUniqueName) {
        return;
    }
    m_profileUniqueName = profileUniqueName;
    Q_EMIT profileUniqueNameChanged(profileUniqueName);
}

QString MEASaveFileHeader::profileId() const
{
    return m_profileId;
}

void MEASaveFileHeader::setProfileId(const QString &profileId)
{
    if (m_profileId == profileId) {
        return;
    }
    m_profileId = profileId;
    Q_EMIT profileIdChanged(profileId);
}

QString MEASaveFileHeader::levelId() const
{
    return m_levelId;
}

void MEASaveFileHeader::setLevelId(const QString &levelId)
{
    if (m_levelId == levelId) {
        return;
    }
    m_levelId = levelId;
    Q_EMIT levelIdChanged(levelId);
}

QString MEASaveFileHeader::playerLevel() const
{
    return m_playerLevel;
}

void MEASaveFileHeader::setPlayerLevel(const QString &playerLevel)
{
    if (m_playerLevel == playerLevel) {
        return;
    }
    m_playerLevel = playerLevel;
    Q_EMIT playerLevelChanged(playerLevel);
}

bool MEASaveFileHeader::gameCompleted() const
{
    return m_gameCompleted;
}

void MEASaveFileHeader::setGameCompleted(bool gameCompleted)
{
    if (m_gameCompleted == gameCompleted) {
        return;
    }
    m_gameCompleted = gameCompleted;
    Q_EMIT gameCompletedChanged(gameCompleted);
}

bool MEASaveFileHeader::trialMode() const
{
    return m_trialMode;
}

void MEASaveFileHeader::setTrialMode(bool trialMode)
{
    if (m_trialMode == trialMode) {
        return;
    }
    m_trialMode = trialMode;
    Q_EMIT trialModeChanged(trialMode);
}

double MEASaveFileHeader::completionPercentage() const
{
    return m_completionPercentage;
}

void MEASaveFileHeader::setCompletionPercentage(double completionPercentage)
{
    if (m_completionPercentage == completionPercentage) {
        return;
    }
    m_completionPercentage = completionPercentage;
    Q_EMIT completionPercentageChanged(completionPercentage);
}

QDateTime MEASaveFileHeader::dateTime() const
{
    return m_dateTime;
}

void MEASaveFileHeader::setDateTime(const QDateTime &dateTime)
{
    if (m_dateTime == dateTime) {
        return;
    }
    m_dateTime = dateTime;
    Q_EMIT dateTimeChanged(dateTime);
}

QString MEASaveFileHeader::levelTitleId() const
{
    return m_levelTitleId;
}

void MEASaveFileHeader::setLevelTitleId(const QString &levelTitleId)
{
    if (m_levelTitleId == levelTitleId) {
        return;
    }
    m_levelTitleId = levelTitleId;
    Q_EMIT levelTitleIdChanged(levelTitleId);
}

QString MEASaveFileHeader::levelFloorId() const
{
    return m_levelFloorId;
}

void MEASaveFileHeader::setLevelFloorId(const QString &levelFloorId)
{
    if (m_levelFloorId == levelFloorId) {
        return;
    }
    m_levelFloorId = levelFloorId;
    Q_EMIT levelFloorIdChanged(levelFloorId);
}

QString MEASaveFileHeader::levelRegionId() const
{
    return m_levelRegionId;
}

void MEASaveFileHeader::setLevelRegionId(const QString &levelRegionId)
{
    if (m_levelRegionId == levelRegionId) {
        return;
    }
    m_levelRegionId = levelRegionId;
    Q_EMIT levelRegionIdChanged(levelRegionId);
}

quint64 MEASaveFileHeader::totalPlaytime() const
{
    return m_totalPlaytime;
}

void MEASaveFileHeader::setTotalPlaytime(const quint64 &totalPlaytime)
{
    if (m_totalPlaytime == totalPlaytime) {
        return;
    }
    m_totalPlaytime = totalPlaytime;
    Q_EMIT totalPlaytimeChanged(totalPlaytime);
}

QString MEASaveFileHeader::nameOverrideStringId() const
{
    return m_nameOverrideStringId;
}

void MEASaveFileHeader::setNameOverrideStringId(const QString &nameOverrideStringId)
{
    if (m_nameOverrideStringId == nameOverrideStringId) {
        return;
    }
    m_nameOverrideStringId = nameOverrideStringId;
    Q_EMIT nameOverrideStringIdChanged(nameOverrideStringId);
}

MEASaveFileHeader *MEASaveFileHeader::fromData(const QByteArray &data, MEASaveFileError *p_error)
{
    MEASAVEFILE_FROMDATA_DECLARE(MEASaveFileHeader, result, stream, data)

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

    quint32 count;
    stream >> count;

    for (quint32 i = 0; i < count; ++i) {
        quint32 keyHash;
        stream >> keyHash;

        quint16 valueSize;
        stream >> valueSize;

        QByteArray buffer(valueSize, Qt::Uninitialized);
        stream.readRawData(buffer.data(), buffer.size());
        QString value = QString::fromUtf8(buffer);

        switch (keyHash) {
        case AreaNameStringId:
            result->m_areaNameStringId = value;
            break;
        case AreaThumbnailTextureId:
            result->m_areaThumbnailTextureId = value;
            break;
        case GameVersion:
            result->m_gameVersion = value;
            break;
        case RequiredDLC:
            result->m_requiredDLC = value;
            break;
        case RequiredInstallGroup:
            result->m_requiredInstallGroup = value;
            break;
        case ProfileName:
            result->m_profileName = value;
            break;
        case ProfileUniqueName:
            result->m_profileUniqueName = value;
            break;
        case ProfileId:
            result->m_profileId = value;
            break;
        case LevelID:
            result->m_levelId = value;
            break;
        case PlayerLevel:
            result->m_playerLevel = value;
            break;
        case GameCompleted:
            result->m_gameCompleted = value == u"true"_s;
            break;
        case TrialMode:
            result->m_trialMode = value == u"true"_s;
            break;
        case CompletionPercentage:
            result->m_completionPercentage = value.toDouble();
            break;
        case DateTime:
            result->m_dateTime = Utils::DateTime::fromJulianSeconds(value.toULongLong());
            break;
        case LevelTitleID:
            result->m_levelTitleId = value;
            break;
        case LevelFloorID:
            result->m_levelFloorId = value;
            break;
        case LevelRegionID:
            result->m_levelRegionId = value;
            break;
        case TotalPlaytime:
            result->m_totalPlaytime = value.toDouble() * 1000;
            break;
        case NameOverrideStringId:
            result->m_nameOverrideStringId = value;
            break;
        default:
            result->m_leftOver.insert(keyHash, value);
            break;
        }
    }

    return result.release();
}

QByteArray MEASaveFileHeader::toData(MEASaveFileError *p_error) const
{
    MEASAVEFILE_TODATA_DELCARE(data, stream)

    const auto keyMeta = QMetaEnum::fromType<MEASaveFileHeader::Key>();

    stream << signature;
    stream << m_version;
    stream << quint32(keyMeta.keyCount() + m_leftOver.count()); // count

    stream << quint32(AreaNameStringId);
    WRITE_STRING(stream, m_areaNameStringId, quint16, p_error, i18nc("MEASaveFileError", "AreaNameStringId is too large"))

    stream << quint32(AreaThumbnailTextureId);
    WRITE_STRING(stream, m_areaThumbnailTextureId, quint16, p_error, i18nc("MEASaveFileError", "AreaThumbnailTextureId is too large"))

    stream << quint32(GameVersion);
    WRITE_STRING(stream, m_gameVersion, quint16, p_error, i18nc("MEASaveFileError", "GameVersion is too large"))

    stream << quint32(RequiredDLC);
    WRITE_STRING(stream, m_requiredDLC, quint16, p_error, i18nc("MEASaveFileError", "RequiredDLC is too large"))

    stream << quint32(RequiredInstallGroup);
    WRITE_STRING(stream, m_requiredInstallGroup, quint16, p_error, i18nc("MEASaveFileError", "RequiredInstallGroup is too large"))

    stream << quint32(ProfileName);
    WRITE_STRING(stream, m_profileName, quint16, p_error, i18nc("MEASaveFileError", "ProfileName is too large"))

    stream << quint32(ProfileUniqueName);
    WRITE_STRING(stream, m_profileUniqueName, quint16, p_error, i18nc("MEASaveFileError", "ProfileUniqueName is too large"))

    stream << quint32(ProfileId);
    WRITE_STRING(stream, m_profileId, quint16, p_error, i18nc("MEASaveFileError", "ProfileId is too large"))

    stream << quint32(LevelID);
    WRITE_STRING(stream, m_levelId, quint16, p_error, i18nc("MEASaveFileError", "LevelID is too large"))

    stream << quint32(PlayerLevel);
    WRITE_STRING(stream, m_playerLevel, quint16, p_error, i18nc("MEASaveFileError", "PlayerLevel is too large"))

    stream << quint32(GameCompleted);
    WRITE_STRING(stream, m_gameCompleted ? u"true"_s : u"false"_s, quint16, p_error, i18nc("MEASaveFileError", "GameCompleted is too large"))

    stream << quint32(TrialMode);
    WRITE_STRING(stream, m_trialMode ? u"true"_s : u"false"_s, quint16, p_error, i18nc("MEASaveFileError", "TrialMode is too large"))

    stream << quint32(CompletionPercentage);
    WRITE_STRING(stream, QString::number(m_completionPercentage, 'f', 7), quint16, p_error, i18nc("MEASaveFileError", "CompletionPercentage is too large"))

    stream << quint32(DateTime);
    WRITE_STRING(stream, QString::number(Utils::DateTime::toJulianSeconds(m_dateTime)), quint16, p_error, i18nc("MEASaveFileError", "DateTime is too large"))

    stream << quint32(LevelTitleID);
    WRITE_STRING(stream, m_levelTitleId, quint16, p_error, i18nc("MEASaveFileError", "LevelTitleID is too large"))

    stream << quint32(LevelFloorID);
    WRITE_STRING(stream, m_levelFloorId, quint16, p_error, i18nc("MEASaveFileError", "LevelFloorID is too large"))

    stream << quint32(LevelRegionID);
    WRITE_STRING(stream, m_levelRegionId, quint16, p_error, i18nc("MEASaveFileError", "LevelRegionID is too large"))

    stream << quint32(TotalPlaytime);
    WRITE_STRING(stream, QString::number(double(m_totalPlaytime) / 1000.0, 'f', 3), quint16, p_error, i18nc("MEASaveFileError", "TotalPlaytime is too large"))

    stream << quint32(NameOverrideStringId);
    WRITE_STRING(stream, m_nameOverrideStringId, quint16, p_error, i18nc("MEASaveFileError", "NameOverrideStringId is too large"))

    for (auto it = m_leftOver.begin(); it != m_leftOver.end(); ++it) {
        stream << quint32(it.key());
        WRITE_STRING(stream, it.value(), quint16, p_error, i18nc("MEASaveFileError", "Header key '%1' is too large", QString::number(it.key())))
    }

    return data;
}
