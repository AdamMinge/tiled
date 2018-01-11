/*-----------------------------------------------------------------------------------------------------------*/
#include <QApplication>
#include <QStyle>
#include "stylemanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
StyleManager* StyleManager::mInstance = nullptr;
/*-----------------------------------------------------------------------------------------------------------*/
StyleManager* StyleManager::instance()
{
	if (!mInstance)
		mInstance = new StyleManager();

	Q_ASSERT(mInstance);
	return mInstance;
}
/*-----------------------------------------------------------------------------------------------------------*/
void StyleManager::deleteInstance()
{
	Q_ASSERT(mInstance);
	delete mInstance;
	mInstance = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList StyleManager::availableStyles() const
{
	return mNameToStyle.keys();
}
/*-----------------------------------------------------------------------------------------------------------*/
void StyleManager::registerStyle(StyleCreatorFun creator, const QString& name)
{
	Q_ASSERT(!mNameToStyle.contains(name));
	mNameToStyle[name] = creator;

	emit styleRegistered(name);
}
/*-----------------------------------------------------------------------------------------------------------*/
void StyleManager::unregisterStyle(const QString& name)
{
	Q_ASSERT(mNameToStyle.contains(name));
	mNameToStyle.remove(name);

	emit styleUnregistered(name);
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& StyleManager::style() const
{
	return mStyleName;
}
/*-----------------------------------------------------------------------------------------------------------*/
void StyleManager::setStyle(const QString& name)
{
	Q_ASSERT(mNameToStyle.contains(name));
	mStyleName = name;

	QApplication::setStyle(mNameToStyle[mStyleName]());

	emit styleChanged(mStyleName);
}
/*-----------------------------------------------------------------------------------------------------------*/