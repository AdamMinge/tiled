/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <gmock/gmock.h>
#include "tileset.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetMock : public Tileset
{
public:
	TilesetMock(const QString& name, const ImageReference& imageReference,
		const QSize& tileSize, int spacing, int margin) : Tileset(name, imageReference, tileSize, spacing, margin) {}
};
/*-----------------------------------------------------------------------------------------------------------*/