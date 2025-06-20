#include "measaveeditorconfig.hpp"

#include <QApplicationStatic>

class MEASaveEditorConfigStatic
{
    Q_DISABLE_COPY_MOVE(MEASaveEditorConfigStatic)
public:
    MEASaveEditorConfig *const instance;

    MEASaveEditorConfigStatic()
        : instance{new MEASaveEditorConfig()}
    {
    }
};

Q_APPLICATION_STATIC(MEASaveEditorConfigStatic, s_static)

MEASaveEditorConfig::~MEASaveEditorConfig()
{
    save();
}

MEASaveEditorConfig *MEASaveEditorConfig::instance()
{
    return s_static->instance;
}

MEASaveEditorConfig *MEASaveEditorConfig::create(QQmlEngine *, QJSEngine *)
{
    return instance();
}

QUrl MEASaveEditorConfig::lastOpenDirUrl() const
{
    return QUrl::fromLocalFile(lastOpenDir());
}

void MEASaveEditorConfig::setLastOpenDirUrl(const QUrl &url)
{
    setLastOpenDir(url.toLocalFile());
}
