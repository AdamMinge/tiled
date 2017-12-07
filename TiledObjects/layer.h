/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "object.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class Map;
class GroupLayer;
class Tileset;
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT Layer : public Object
{
	friend class GroupLayer;

public:
	enum LayerType
	{
		TileLayerType,
		GroupLayerType
	};

public:
	explicit Layer(LayerType type, const QString& name);
	virtual ~Layer() override = default;

	Layer(Layer&&) = delete;
	Layer(const Layer&) = delete;

	Layer& operator=(Layer&&) = delete;
	Layer& operator=(const Layer&) = delete;

	LayerType layerType() const;

	const QString& name() const;
	void setName(const QString& name);

	float opacity() const;
	void setOpacity(float opacity);

	bool isVisible() const;
	bool isHidden() const;
	void setVisible(bool visible);

	bool isLocked() const;
	bool isUnlocked() const;
	void setLocked(bool locked);

	GroupLayer* parent() const;

	int siblingIndex() const;
	QList<Layer*> siblings() const;

	virtual bool isEmpty() const = 0;
	virtual QList<Tileset*> usedTilesets() const = 0;
	virtual bool referencesTileset(const Tileset *tileset) const = 0;

	virtual bool canMergeWith(Layer* layer) const = 0;
	virtual Layer* mergeWith(Layer* layer) const = 0;

	virtual Layer* clone() const = 0;

protected:
	void setParent(GroupLayer* layer);
	Layer* initializeClone(Layer* clone) const;

private:
	QString mName;
	LayerType mType;
	float mOpacity;

	GroupLayer* mParentLayer;

	bool mVisible;
	bool mLocked;
};
/*-----------------------------------------------------------------------------------------------------------*/
