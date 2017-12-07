/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QVariant>
#include "command.h"
/*-----------------------------------------------------------------------------------------------------------*/
class MapDocument;
class Layer;
/*-----------------------------------------------------------------------------------------------------------*/
class ChangeLayerProperty final : public Command
{
public:
	enum class BoolProperty;

public:
	explicit ChangeLayerProperty(MapDocument* mapDocument, Layer* layer,
		const QString& newName, Command* parent = nullptr);
	explicit ChangeLayerProperty(MapDocument* mapDocument, Layer* layer,
		float opacity, Command* parent = nullptr);
	explicit ChangeLayerProperty(MapDocument* mapDocument, Layer* layer,
		bool value, BoolProperty property, Command* parent = nullptr);

	ChangeLayerProperty(ChangeLayerProperty&&) = delete;
	ChangeLayerProperty(const ChangeLayerProperty&) = delete;

	ChangeLayerProperty& operator=(ChangeLayerProperty&&) = delete;
	ChangeLayerProperty& operator=(const ChangeLayerProperty&) = delete;

	void undo() override;
	void redo() override;

	int id() const override;

	bool canMergeWith(const Command* other) const override;
	void mergeWith(const Command* other) override;

private:
	void setValue(const QVariant& value);

private:
	MapDocument* mMapDocument;
	Layer* mLayer;
	int mProperty;
	QVariant mNewValue;
	QVariant mPreviousValue;
};
/*-----------------------------------------------------------------------------------------------------------*/
enum class ChangeLayerProperty::BoolProperty
{
	Visible,
	Locked
};
/*-----------------------------------------------------------------------------------------------------------*/