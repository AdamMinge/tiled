/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include <QDirIterator>
#include <QTranslator>
#include <QLibraryInfo>
#include "languagemanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
LanguageManager* LanguageManager::mInstance = nullptr;
/*-----------------------------------------------------------------------------------------------------------*/
LanguageManager* LanguageManager::instance()
{
	if (!mInstance)
		mInstance = new LanguageManager();

	Q_ASSERT(mInstance);
	return mInstance;
}
/*-----------------------------------------------------------------------------------------------------------*/
void LanguageManager::deleteInstance()
{
	Q_ASSERT(mInstance);
	delete mInstance;
	mInstance = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList LanguageManager::availableLanguages() const
{
	Q_ASSERT(!mTranslationsPrefix.isEmpty());
	Q_ASSERT(!mAppTranslationsDir.isEmpty());

	return loadAvailableLanguages(mAppTranslationsDir, mTranslationsPrefix);
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& LanguageManager::language() const
{
	return mLanguage;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& LanguageManager::translationsDir() const
{
	return mAppTranslationsDir;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& LanguageManager::translationsPrefix() const
{
	return mTranslationsPrefix;
}
/*-----------------------------------------------------------------------------------------------------------*/
void LanguageManager::setLanguage(const QString& language)
{
	mLanguage = language;

	Q_ASSERT(!mLanguage.isEmpty());

	if (mQtTranslator) delete mQtTranslator;
	if (mAppTranslator) delete mAppTranslator;

	mQtTranslator = new QTranslator;
	mAppTranslator = new QTranslator;

	if (mQtTranslator->load(QLatin1String("qt_") + language,
		QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
	{
		QCoreApplication::installTranslator(mQtTranslator);
	}
	else
	{
		delete mQtTranslator;
		mQtTranslator = nullptr;
	}

	if (mAppTranslator->load(mTranslationsPrefix + language,
		mAppTranslationsDir))
	{
		QCoreApplication::installTranslator(mAppTranslator);
	}
	else
	{
		delete mAppTranslator;
		mAppTranslator = nullptr;
	}

	emit languageChanged(mLanguage);
}
/*-----------------------------------------------------------------------------------------------------------*/
void LanguageManager::setTranslationsDir(const QString& translationsDir)
{
	if (mAppTranslationsDir == translationsDir) return;

	mAppTranslationsDir = translationsDir;
	emit translationsDirChanged(mAppTranslationsDir);
}
/*-----------------------------------------------------------------------------------------------------------*/
void LanguageManager::setTranslationsPrefix(const QString& translationsPrefix)
{
	if (mTranslationsPrefix == translationsPrefix) return;

	mTranslationsPrefix = translationsPrefix;
	emit translationsPrefixChanged(mTranslationsPrefix);
}
/*-----------------------------------------------------------------------------------------------------------*/
LanguageManager::LanguageManager() :
	mQtTranslator(nullptr),
	mAppTranslator(nullptr)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
LanguageManager::~LanguageManager()
{
	if (mQtTranslator) delete mQtTranslator;
	if (mAppTranslator) delete mAppTranslator;
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList LanguageManager::loadAvailableLanguages(const QString& dir, const QString& prefix)
{
	QStringList languages;

	QStringList nameFilters;
	nameFilters.append(prefix + QLatin1String("*.qm"));

	QDirIterator iterator(dir, nameFilters, QDir::Files | QDir::Readable);
	while(iterator.hasNext())
	{
		iterator.next();
		auto baseName = iterator.fileInfo().completeBaseName();

		languages.append(baseName.mid(prefix.count()));
	}

	return languages;
}
/*-----------------------------------------------------------------------------------------------------------*/
