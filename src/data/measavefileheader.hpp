#ifndef MEASAVEFILEHEADER_HPP
#define MEASAVEFILEHEADER_HPP

#include "measavefileerror.hpp"
#include "utils/hashing/djb.hpp"

#include <QDateTime>
#include <QObject>

class MEASaveFileHeader : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Created by MEASaveFileManager")
    Q_PROPERTY(quint16 version READ version WRITE setVersion NOTIFY versionChanged FINAL)
    Q_PROPERTY(QString areaNameStringId READ areaNameStringId WRITE setAreaNameStringId NOTIFY areaNameStringIdChanged FINAL)
    Q_PROPERTY(QString areaThumbnailTextureId READ areaThumbnailTextureId WRITE setAreaThumbnailTextureId NOTIFY areaThumbnailTextureIdChanged FINAL)
    Q_PROPERTY(QString gameVersion READ gameVersion WRITE setGameVersion NOTIFY gameVersionChanged FINAL)
    Q_PROPERTY(QString requiredDLC READ requiredDLC WRITE setRequiredDLC NOTIFY requiredDLCChanged FINAL)
    Q_PROPERTY(QString requiredInstallGroup READ requiredInstallGroup WRITE setRequiredInstallGroup NOTIFY requiredInstallGroupChanged FINAL)
    Q_PROPERTY(QString profileName READ profileName WRITE setProfileName NOTIFY profileNameChanged FINAL)
    Q_PROPERTY(QString profileUniqueName READ profileUniqueName WRITE setProfileUniqueName NOTIFY profileUniqueNameChanged FINAL)
    Q_PROPERTY(QString profileId READ profileId WRITE setProfileId NOTIFY profileIdChanged FINAL)
    Q_PROPERTY(QString levelId READ levelId WRITE setLevelId NOTIFY levelIdChanged FINAL)
    Q_PROPERTY(QString playerLevel READ playerLevel WRITE setPlayerLevel NOTIFY playerLevelChanged FINAL)
    Q_PROPERTY(bool gameCompleted READ gameCompleted WRITE setGameCompleted NOTIFY gameCompletedChanged FINAL)
    Q_PROPERTY(bool trialMode READ trialMode WRITE setTrialMode NOTIFY trialModeChanged FINAL)
    Q_PROPERTY(double completionPercentage READ completionPercentage WRITE setCompletionPercentage NOTIFY completionPercentageChanged FINAL)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged FINAL)
    Q_PROPERTY(QString levelTitleId READ levelTitleId WRITE setLevelTitleId NOTIFY levelTitleIdChanged FINAL)
    Q_PROPERTY(QString levelFloorId READ levelFloorId WRITE setLevelFloorId NOTIFY levelFloorIdChanged FINAL)
    Q_PROPERTY(QString levelRegionId READ levelRegionId WRITE setLevelRegionId NOTIFY levelRegionIdChanged FINAL)
    Q_PROPERTY(quint64 totalPlaytime READ totalPlaytime WRITE setTotalPlaytime NOTIFY totalPlaytimeChanged FINAL)
    Q_PROPERTY(QString nameOverrideStringId READ nameOverrideStringId WRITE setNameOverrideStringId NOTIFY nameOverrideStringIdChanged FINAL)
private:
    explicit MEASaveFileHeader() = default;

public:
    enum Key : quint32 {
        AreaNameStringId = Utils::Hashing::djbHash("AreaNameStringId"),
        AreaThumbnailTextureId = Utils::Hashing::djbHash("AreaThumbnailTextureId"),
        GameVersion = Utils::Hashing::djbHash("GameVersion"),
        RequiredDLC = Utils::Hashing::djbHash("RequiredDLC"),
        RequiredInstallGroup = Utils::Hashing::djbHash("RequiredInstallGroup"),
        ProfileName = Utils::Hashing::djbHash("ProfileName"),
        ProfileUniqueName = Utils::Hashing::djbHash("ProfileUniqueName"),
        ProfileId = Utils::Hashing::djbHash("ProfileId"),
        LevelID = Utils::Hashing::djbHash("LevelID"),
        PlayerLevel = Utils::Hashing::djbHash("PlayerLevel"),
        GameCompleted = Utils::Hashing::djbHash("GameCompleted"),
        TrialMode = Utils::Hashing::djbHash("TrialMode"),
        CompletionPercentage = Utils::Hashing::djbHash("CompletionPercentage"),
        DateTime = Utils::Hashing::djbHash("DateTime"),
        LevelTitleID = Utils::Hashing::djbHash("LevelTitleID"),
        LevelFloorID = Utils::Hashing::djbHash("LevelFloorID"),
        LevelRegionID = Utils::Hashing::djbHash("LevelRegionID"),
        TotalPlaytime = Utils::Hashing::djbHash("TotalPlaytime"),
        NameOverrideStringId = Utils::Hashing::djbHash("NameOverrideStringId"),
    };
    Q_ENUM(Key)

    ~MEASaveFileHeader() override = default;

    quint16 version() const;
    void setVersion(quint16 version);
    QString areaNameStringId() const;
    void setAreaNameStringId(const QString &areaNameStringId);
    QString areaThumbnailTextureId() const;
    void setAreaThumbnailTextureId(const QString &areaThumbnailTextureId);
    QString gameVersion() const;
    void setGameVersion(const QString &gameVersion);
    QString requiredDLC() const;
    void setRequiredDLC(const QString &requiredDLC);
    QString requiredInstallGroup() const;
    void setRequiredInstallGroup(const QString &requiredInstallGroup);
    QString profileName() const;
    void setProfileName(const QString &profileName);
    QString profileUniqueName() const;
    void setProfileUniqueName(const QString &profileUniqueName);
    QString profileId() const;
    void setProfileId(const QString &profileId);
    QString levelId() const;
    void setLevelId(const QString &levelId);
    QString playerLevel() const;
    void setPlayerLevel(const QString &playerLevel);
    bool gameCompleted() const;
    void setGameCompleted(bool gameCompleted);
    bool trialMode() const;
    void setTrialMode(bool trialMode);
    double completionPercentage() const;
    void setCompletionPercentage(double completionPercentage);
    QDateTime dateTime() const;
    void setDateTime(const QDateTime &dateTime);
    QString levelTitleId() const;
    void setLevelTitleId(const QString &levelTitleId);
    QString levelFloorId() const;
    void setLevelFloorId(const QString &levelFloorId);
    QString levelRegionId() const;
    void setLevelRegionId(const QString &levelRegionId);
    quint64 totalPlaytime() const;
    void setTotalPlaytime(const quint64 &totalPlaytime);
    QString nameOverrideStringId() const;
    void setNameOverrideStringId(const QString &nameOverrideStringId);

    static MEASaveFileHeader *fromData(const QByteArray &data, MEASaveFileError *p_error = nullptr);
    QByteArray toData(MEASaveFileError *p_error = nullptr) const;

Q_SIGNALS:
    void versionChanged(quint16 version);
    void areaNameStringIdChanged(const QString &areaNameStringId);
    void areaThumbnailTextureIdChanged(const QString &areaThumbnailTextureId);
    void gameVersionChanged(const QString &gameVersion);
    void requiredDLCChanged(const QString &requiredDLC);
    void requiredInstallGroupChanged(const QString &requiredInstallGroup);
    void profileNameChanged(const QString &profileName);
    void profileUniqueNameChanged(const QString &profileUniqueName);
    void profileIdChanged(const QString &profileId);
    void levelIdChanged(const QString &levelId);
    void playerLevelChanged(const QString &playerLevel);
    void gameCompletedChanged(bool gameCompleted);
    void trialModeChanged(bool trialMode);
    void completionPercentageChanged(double completionPercentage);
    void dateTimeChanged(const QDateTime &dateTime);
    void levelTitleIdChanged(const QString &levelTitleId);
    void levelFloorIdChanged(const QString &levelFloorId);
    void levelRegionIdChanged(const QString &levelRegionId);
    void totalPlaytimeChanged(const quint64 &totalPlaytime);
    void nameOverrideStringIdChanged(const QString &nameOverrideStringId);

private:
    quint16 m_version = 0;
    QString m_areaNameStringId;
    QString m_areaThumbnailTextureId;
    QString m_gameVersion;
    QString m_requiredDLC;
    QString m_requiredInstallGroup;
    QString m_profileName;
    QString m_profileUniqueName;
    QString m_profileId;
    QString m_levelId;
    QString m_playerLevel;
    bool m_gameCompleted = false;
    bool m_trialMode = false;
    double m_completionPercentage = 0;
    QDateTime m_dateTime;
    QString m_levelTitleId;
    QString m_levelFloorId;
    QString m_levelRegionId;
    quint64 m_totalPlaytime;
    QString m_nameOverrideStringId;

    QHash<quint32, QString> m_leftOver;
};

#endif // MEASAVEFILEHEADER_HPP
