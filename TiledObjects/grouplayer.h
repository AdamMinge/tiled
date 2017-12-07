/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "layer.h"
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT GroupLayer final : public Layer
{
public:
	explicit GroupLayer(const QString& name);
	~GroupLayer() override;

	const QList<Layer*>& layers() const;
	const Layer* layer(int index) const;
	Layer* layer(int index);

	int layerCount() const;
	int layerIndex(const Layer* layer) const;

	void addLayer(Layer* layer);
	void addLayer(Layer* layer, int index);

	void removeLayer(int index);
	Layer* takeLayer(int index);

	bool isEmpty() const override;
    QList<Tileset*> usedTilesets() const override;
	bool referencesTileset(const Tileset *tileset) const override;

	bool canMergeWith(Layer* layer) const override;
	Layer* mergeWith(Layer* layer) const override;

	QList<Layer*>::iterator begin();
	QList<Layer*>::const_iterator begin() const;

	QList<Layer*>::iterator end();
	QList<Layer*>::const_iterator end() const;

	GroupLayer* clone() const override;

private:
	GroupLayer* initializeClone(GroupLayer* clone) const;

private:
	QList<Layer*> mLayers;
};
/*-----------------------------------------------------------------------------------------------------------*/