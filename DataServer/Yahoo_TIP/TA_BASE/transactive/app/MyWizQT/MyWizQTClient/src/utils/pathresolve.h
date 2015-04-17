#ifndef UTILS_PATHRESOLVE_H
#define UTILS_PATHRESOLVE_H

class QString;

namespace Utils {

class PathResolve
{
public:
    static QString appPath();
    static QString resourcesPath();
    static QString themePath(const QString& strThemeName);
    static QString skinResourcesPath(const QString& strSkinName);
    static QString builtinTemplatePath();
    static QString downloadedTemplatesPath();
    static QString pluginsPath();
    static QString dataStorePath();
	static QString currentPath();
    static QString cachePath();
    static QString avatarPath();
    static QString tempPath();
    static QString tempDocumentFolder(const QString& strGuid);
    static QString upgradePath();
    static QString logFile();
    static QString globalSettingsFile();
    static QString userSettingsFile(const QString strUserId);
    static QString qtLocaleFileName(const QString& strLocale);
    static QString localeFileName(const QString& strLocale);

    // helpers
    static void addBackslash(QString& strPath);
    static void ensurePathExists(const QString& path);

private:
    static QString logFilePath();
};

} // namespace Utils

#endif // UTILS_PATHRESOLVE_H
