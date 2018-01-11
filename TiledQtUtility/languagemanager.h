/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
/*-----------------------------------------------------------------------------------------------------------*/
class QTranslator;
/*-----------------------------------------------------------------------------------------------------------*/
class LanguageManager final : public QObject
{
	Q_OBJECT

public:
	static LanguageManager* instance();
	static void deleteInstance();

	LanguageManager(LanguageManager&&) = delete;
	LanguageManager(const LanguageManager&) = delete;

	LanguageManager& operator=(LanguageManager&&) = delete;
	LanguageManager& operator=(const LanguageManager&) = delete;

	QStringList availableLanguages() const;
	const QString& language() const;
	const QString& translationsDir() const;
	const QString& translationsPrefix() const;
	
public slots:
	void setLanguage(const QString& language);
	void setTranslationsDir(const QString& translationsDir);
	void setTranslationsPrefix(const QString& translationsPrefix);

signals:
	void languageChanged(const QString& language);
	void translationsDirChanged(const QString& translationsDir);
	void translationsPrefixChanged(const QString& translationsPrefix);

private:
	explicit LanguageManager();
	~LanguageManager() override;

	static QStringList loadAvailableLanguages(const QString& dir, const QString& prefix);

private:
	static LanguageManager* mInstance;

	QTranslator* mQtTranslator;
	QTranslator* mAppTranslator;

	QString mLanguage;
	QString mTranslationsPrefix;
	QString mAppTranslationsDir;
};
/*-----------------------------------------------------------------------------------------------------------*/