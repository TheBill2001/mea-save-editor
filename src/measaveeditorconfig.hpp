#ifndef MEASAVEEDITORCONFIG_HPP
#define MEASAVEEDITORCONFIG_HPP

#include "measaveeditorconfigbase.hpp"

class QQmlEngine;
class QJSEngine;
class MEASaveEditorConfig : public MEASaveEditorConfigBase
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QUrl lastOpenDirUrl READ lastOpenDirUrl WRITE setLastOpenDirUrl NOTIFY LastOpenDirChanged FINAL)
private:
    friend class MEASaveEditorConfigStatic;
    MEASaveEditorConfig() = default;

public:
    ~MEASaveEditorConfig() override;

    static MEASaveEditorConfig *instance();
    static MEASaveEditorConfig *create(QQmlEngine *, QJSEngine *);

    QUrl lastOpenDirUrl() const;
    void setLastOpenDirUrl(const QUrl &url);
};

#endif // MEASAVEEDITORCONFIG_HPP
