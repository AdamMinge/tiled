/*-----------------------------------------------------------------------------------------------------------*/
#include <QUrl>
#include "utils.h"
#include "variantpropertymanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
VariantPropertyManager::VariantPropertyManager(QObject* parent) :
	QtVariantPropertyManager(parent)
{
	
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant VariantPropertyManager::value(const QtProperty* property) const
{
	if (mFileIdValues.contains(property)) return mFileIdValues[property].value;
	else return QtVariantPropertyManager::value(property);
}
/*-----------------------------------------------------------------------------------------------------------*/
int VariantPropertyManager::valueType(int propertyType) const
{
	if (propertyType == QVariant::Url) return QVariant::Url;
	else return QtVariantPropertyManager::valueType(propertyType);
}
/*-----------------------------------------------------------------------------------------------------------*/
bool VariantPropertyManager::isPropertyTypeSupported(int propertyType) const
{
	if (propertyType == QVariant::Url) return true;
	else return QtVariantPropertyManager::valueType(propertyType);
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList VariantPropertyManager::attributes(int propertyType) const
{
	if(propertyType == QVariant::Url) return QStringList{ QStringLiteral("filter") };
	else return QtVariantPropertyManager::attributes(propertyType);
}
/*-----------------------------------------------------------------------------------------------------------*/
int VariantPropertyManager::attributeType(int propertyType, const QString& attribute) const
{
	if(propertyType == QVariant::Url)
	{
		if (attribute == QLatin1String("filter")) return QVariant::String;
		else return 0;
	}
	else return QtVariantPropertyManager::attributeType(propertyType, attribute);
}
/*-----------------------------------------------------------------------------------------------------------*/
QVariant VariantPropertyManager::attributeValue(const QtProperty* property, const QString& attribute) const
{
	if(mFileIdValues.contains(property))
	{
		if (attribute == QLatin1String("filter")) return mFileIdValues[property].filter;
		else return QVariant();
	}
	else return QtVariantPropertyManager::attributeValue(property, attribute);
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantPropertyManager::setValue(QtProperty* property, const QVariant& value)
{
	if(mFileIdValues.contains(property))
	{
		auto data = mFileIdValues[property];
		if (data.value == value) return;

		data.value = value;
		mFileIdValues[property] = data;

		emit propertyChanged(property);
		emit valueChanged(property, value);
	}
	else QtVariantPropertyManager::setValue(property, value);
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantPropertyManager::setAttribute(QtProperty* property, const QString& attribute, const QVariant& value)
{
	if(mFileIdValues.contains(property))
	{
		if(attribute == QLatin1String("filter"))
		{
			const auto filter = value.toString();
			auto data = mFileIdValues[property];

			if (data.filter == filter) return;

			data.filter = filter;
			mFileIdValues[property] = data;

			emit attributeChanged(property, attribute, value);
		}
	}
	else QtVariantPropertyManager::setAttribute(property, attribute, value);
}
/*-----------------------------------------------------------------------------------------------------------*/
QString VariantPropertyManager::valueText(const QtProperty* property) const
{
	if(mFileIdValues.contains(property))
	{
		auto value = mFileIdValues[property].value;
		auto fileName = value.toUrl().toLocalFile();

		return fileName;
	}
	else return QtVariantPropertyManager::valueText(property);
}
/*-----------------------------------------------------------------------------------------------------------*/
QIcon VariantPropertyManager::valueIcon(const QtProperty* property) const
{
	if(mFileIdValues.contains(property))
	{
		auto value = mFileIdValues[property].value;
		auto filePath = value.toUrl().toLocalFile();

		if (filePath.isEmpty() || !QFile::exists(filePath))
			return makeIcon(QLatin1String(":/Tiled/images/%1/image-missing.png"), { QSize(16,16) });
		else 
			return mIconProvider.icon(QFileInfo(filePath));
	}
	else return QtVariantPropertyManager::valueIcon(property);
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantPropertyManager::initializeProperty(QtProperty* property)
{
	const auto type = propertyType(property);

	if (type == QVariant::Url) mFileIdValues[property] = FileIdData();
	QtVariantPropertyManager::initializeProperty(property);
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantPropertyManager::uninitializeProperty(QtProperty* property)
{
	mFileIdValues.remove(property);
	QtVariantPropertyManager::uninitializeProperty(property);
}
/*-----------------------------------------------------------------------------------------------------------*/