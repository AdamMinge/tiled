/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "properties.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Object abstract
{
public:
	enum ObjectType
	{
		TilesetType,
		TileType,
		MapType,
		LayerType
	};

public:
	explicit Object(ObjectType type);
	virtual ~Object() = default;

	Object(Object&&) = default;
	Object(const Object&) = default;

	Object& operator=(Object&&) = default;
	Object& operator=(const Object&) = default;

	const Properties& properties() const;
	void setProperties(const Properties& properties);

	QVariant property(const QString& name) const;
	bool hasProperty(const QString& name) const;

	void setProperty(const QString& name, const QVariant& value);
	void removeProperty(const QString& name);

	ObjectType type() const;

private:
	Properties mProperties;
	const ObjectType mType;
};
/*-----------------------------------------------------------------------------------------------------------*/