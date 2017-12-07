/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVariant>
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Properties final : public QMap<QString, QVariant>
{
public:
	Properties() = default;
	~Properties() = default;

	Properties(Properties&&) = default;
	Properties(const Properties&) = default;

	Properties& operator=(Properties&&) = default;
	Properties& operator=(const Properties&) = default;

	static QJsonArray toJson(const Properties& properties);
	static Properties fromJson(const QJsonArray &json);
};
/*-----------------------------------------------------------------------------------------------------------*/
