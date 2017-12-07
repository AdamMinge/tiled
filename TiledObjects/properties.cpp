/*-----------------------------------------------------------------------------------------------------------*/
#include <QJsonArray>
#include <QJsonObject>
#include "properties.h"
/*-----------------------------------------------------------------------------------------------------------*/
QJsonArray Properties::toJson(const Properties& properties)
{
	QJsonArray json;

	for(auto iter = properties.begin(); iter != properties.end(); ++iter)
	{
		const auto& name = iter.key();
		const auto value = QJsonValue::fromVariant(iter.value());
		const auto type = QString(QVariant::typeToName(iter.value().userType()));

		QJsonObject propertyObject;
		propertyObject.insert(QLatin1String("name"), name);
		propertyObject.insert(QLatin1String("value"), value);
		propertyObject.insert(QLatin1String("type"), type);

		json.append(propertyObject);
	}

	return json;
}
/*-----------------------------------------------------------------------------------------------------------*/
Properties Properties::fromJson(const QJsonArray& json)
{
	Properties properties;

	for(const auto& property : json)
	{
		const auto propertyObject = property.toObject();
		const auto name = propertyObject.value(QLatin1String("name")).toString();
		const auto value = propertyObject.value(QLatin1String("value")).toVariant();
		const auto type = propertyObject.value(QLatin1String("type")).toString();

		properties.insert(name, value);
	}

	return properties;
}
/*-----------------------------------------------------------------------------------------------------------*/
