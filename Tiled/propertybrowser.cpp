/*-----------------------------------------------------------------------------------------------------------*/
#include <QUrl>
#include <QEvent>
#include "object.h"
#include "tileset.h"
#include "layer.h"
#include "tile.h"
#include "propertybrowser.h"
#include "variantpropertymanager.h"
#include "varianteditorfactory.h"
#include "mapdocument.h"
#include "changeproperties.h"
#include "changetilesetproperty.h"
#include "changemapproperty.h"
#include "ChangeLayerProperty.h"
/*-----------------------------------------------------------------------------------------------------------*/
static QString nameToId(const QString& name, bool isCustom)
{
	Q_ASSERT(!name.contains("Custom_"));

	if (!isCustom) return name;
	else return QString("Custom_") + name;
}
/*-----------------------------------------------------------------------------------------------------------*/
PropertyBrowser::PropertyBrowser(QWidget* parent) :
	QtTreePropertyBrowser(parent),
	mDocument(nullptr),
	mMapDocument(nullptr),
	mObject(nullptr),
	mVariantManager(new VariantPropertyManager(this)),
	mGroupManager(new QtGroupPropertyManager(this)),
	mCustomPropertiesGroup(nullptr),
	mUpdating(false)
{
	auto variantEditorFactory = new VariantEditorFactory(this);

	setFactoryForManager(mVariantManager, variantEditorFactory);
	setResizeMode(ResizeToContents);
	setRootIsDecorated(false);
	setPropertiesWithoutValueMarked(true);
	setAllowMultiSelection(true);

	connect(mVariantManager, &QtVariantPropertyManager::valueChanged, this, &PropertyBrowser::valueChanged);

	retranslateUi();
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::setDocument(Document* document)
{
	if (mDocument == document) return;

	if (mDocument)
	{
		mDocument->disconnect(this);
	}

	mDocument = document;
	mMapDocument = qobject_cast<MapDocument*>(document);

	if (mMapDocument)
	{
		connect(mMapDocument, &MapDocument::mapChanged, this, &PropertyBrowser::objectChanged);
		connect(mMapDocument, &MapDocument::tileChanged, this, &PropertyBrowser::objectChanged);
		connect(mMapDocument, &MapDocument::tilesetChanged, this, &PropertyBrowser::objectChanged);
		connect(mMapDocument, &MapDocument::layerChanged, this, &PropertyBrowser::objectChanged);
	}

	if (mDocument)
	{
		connect(mDocument, &Document::propertyAdded, this, &PropertyBrowser::propertyAdded);
		connect(mDocument, &Document::propertyRemoved, this, &PropertyBrowser::propertyRemoved);
		connect(mDocument, &Document::propertyChanged, this, &PropertyBrowser::propertyChanged);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::setObject(Object* object)
{
	if (mObject == object) return;

	mUpdating = true;

	removeProperties();
	mObject = object;
	addProperties();

	mUpdating = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PropertyBrowser::isCustomPropertyItem(const QtBrowserItem* item) const
{
	auto name = nameToId(item->property()->propertyName(), true);
	if (mIdToProperty.contains(name)) return true;
	else return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PropertyBrowser::allCustomPropertyItem(const QList<QtBrowserItem*>& items) const
{
	for (decltype(auto) item : items)
		if (!isCustomPropertyItem(item)) return false;

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PropertyBrowser::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
		retranslateUi();
		break;
	default:
		break;
	}

	return QtTreePropertyBrowser::event(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::propertyAdded(Object* object, const QString& name)
{
	if (object != mObject) return;

	mUpdating = true;

	auto id = nameToId(name, true);
	if (mIdToProperty.contains(id))
	{
		mIdToProperty[id]->setValue(mObject->property(name));
	}
	else
	{
		auto value = mObject->property(name);
		auto property = createCustomProperty(id, value.type(), name);
		property->setValue(value);
	}

	mUpdating = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::propertyRemoved(Object* object, const QString& name)
{
	if (object != mObject) return;

	mUpdating = true;

	auto id = nameToId(name, true);
	deleteCustomProperty(mIdToProperty[id]);

	mUpdating = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::propertyChanged(Object* object, const QString& name)
{
	if (object != mObject) return;

	auto value = object->property(name);
	auto property = mIdToProperty[nameToId(name, true)];

	mUpdating = true;

	if (value.userType() != property->valueType())
	{
		auto propertyName = property->propertyName();
		auto wasCurrent = currentItem() && currentItem()->property() == property;

		deleteCustomProperty(property);
		property = createCustomProperty(nameToId(name, true), value.type(), name);
		property->setValue(value);

		if (wasCurrent) setCurrentItem(items(property).first());
	}
	else
	{
		property->setValue(mObject->property(name));
	}

	mUpdating = false;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::valueChanged(QtProperty* property, const QVariant& val)
{
	if (mUpdating) return;
	if (!mDocument || !mObject) return;

	auto propertyName = property->propertyName();
	auto isProperty = mIdToProperty.contains(nameToId(propertyName, false));
	auto isCustomProperty = mIdToProperty.contains(nameToId(propertyName, true));

	if (!isProperty && !isCustomProperty) return;

	if (isCustomProperty)
	{
		auto undoStack = mDocument->undoStack();
		undoStack->push(new SetProperty(mDocument, mObject,
			propertyName, val));
	}
	else
	{
		switch (mObject->type())
		{
		case Object::MapType:
			applyMapValue(nameToId(propertyName, false), val);
			break;
		case Object::TilesetType:
			applyTilesetValue(nameToId(propertyName, false), val);
			break;
		case Object::TileType:
			applyTileValue(nameToId(propertyName, false), val);
			break;
		case Object::LayerType:
			applyLayerValue(nameToId(propertyName, false), val);
			break;
		}
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::removeProperties()
{
	mVariantManager->clear();
	mGroupManager->clear();
	mIdToProperty.clear();
	mCustomPropertiesGroup = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::addProperties()
{
	if (!mObject) return;

	switch (mObject->type())
	{
	case Object::MapType:
		addMapProperties();
		break;
	case Object::TilesetType:
		addTilesetProperties();
		break;
	case Object::TileType:
		addTileProperties();
		break;
	case Object::LayerType:
		addLayerProperties();
		break;
	}

	addCustomProperties();

	updateProperties();
	updateCustomProperties();
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::updateProperties()
{
	Q_ASSERT(mObject);

	switch (mObject->type())
	{
	case Object::MapType:
		updateMapProperties();
		break;
	case Object::TilesetType:
		updateTilesetProperties();
		break;
	case Object::TileType:
		updateTileProperties();
		break;
	case Object::LayerType:
		updateLayerProperties();
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::updateCustomProperties()
{
	Q_ASSERT(mObject);

	decltype(auto) properties = mObject->properties();
	QMapIterator<QString, QVariant> iter(properties);

	while (iter.hasNext())
	{
		iter.next();
		mIdToProperty[nameToId(iter.key(), true)]->setValue(iter.value());
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::addMapProperties()
{
	auto groupProperty = mGroupManager->addProperty(tr("Map"));

	auto orientationProperty = addProperty(nameToId(tr("Map Orientation"), false),
		QtVariantPropertyManager::enumTypeId(),
		tr("Map Orientation"), groupProperty);
	orientationProperty->setAttribute(QLatin1String("enumNames"), mOrientationNames);

	auto renderOrderProperty = addProperty(nameToId(tr("Tile Render Order"), false),
		QtVariantPropertyManager::enumTypeId(),
		tr("Tile Render Order"), groupProperty);
	renderOrderProperty->setAttribute(QLatin1String("enumNames"), mRenderOrderNames);

	auto widthProperty = addProperty(nameToId(tr("Width"), false), QVariant::Int, tr("Width"), groupProperty);
	auto heightProperty = addProperty(nameToId(tr("Height"), false), QVariant::Int, tr("Height"), groupProperty);
	auto tileWidthProperty = addProperty(nameToId(tr("Tile Width"), false), QVariant::Int, tr("Tile Width"), groupProperty);
	auto tileHeightProperty = addProperty(nameToId(tr("Tile Height"), false), QVariant::Int, tr("Tile Height"), groupProperty);

	widthProperty->setAttribute(QLatin1String("minimum"), 1);
	heightProperty->setAttribute(QLatin1String("minimum"), 1);
	tileWidthProperty->setAttribute(QLatin1String("minimum"), 1);
	tileHeightProperty->setAttribute(QLatin1String("minimum"), 1);

	orientationProperty->setEnabled(true);
	renderOrderProperty->setEnabled(true);
	widthProperty->setEnabled(false);
	heightProperty->setEnabled(false);
	tileWidthProperty->setEnabled(true);
	tileHeightProperty->setEnabled(true);

	QtTreePropertyBrowser::addProperty(groupProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::addTilesetProperties()
{
	auto groupProperty = mGroupManager->addProperty(tr("Tileset"));

	auto nameProperty = addProperty(nameToId(tr("Name"), false), QVariant::String, tr("Name"), groupProperty);
	auto imageSourceProperty = addProperty(nameToId(tr("Source"), false), QVariant::Url, tr("Source"), groupProperty);
	auto tileWidthProperty = addProperty(nameToId(tr("Tile Width"), false), QVariant::Int, tr("Tile Width"), groupProperty);
	auto tileHeightProperty = addProperty(nameToId(tr("Tile Height"), false), QVariant::Int, tr("Tile Height"), groupProperty);
	auto marginProperty = addProperty(nameToId(tr("Margin"), false), QVariant::Int, tr("Margin"), groupProperty);
	auto spacingProperty = addProperty(nameToId(tr("Spacing"), false), QVariant::Int, tr("Spacing"), groupProperty);
	auto colorProperty = addProperty(nameToId(tr("Transparent Color"), false), QVariant::Color, tr("Transparent Color"), groupProperty);

	tileWidthProperty->setAttribute(QLatin1String("minimum"), 1);
	tileHeightProperty->setAttribute(QLatin1String("minimum"), 1);
	marginProperty->setAttribute(QLatin1String("minimum"), 0);
	spacingProperty->setAttribute(QLatin1String("minimum"), 0);

	nameProperty->setEnabled(true);
	imageSourceProperty->setEnabled(false);
	tileWidthProperty->setEnabled(false);
	tileHeightProperty->setEnabled(false);
	marginProperty->setEnabled(false);
	spacingProperty->setEnabled(false);
	colorProperty->setEnabled(false);

	QtTreePropertyBrowser::addProperty(groupProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::addTileProperties()
{
	auto groupProperty = mGroupManager->addProperty(tr("Tile"));

	auto id = addProperty(nameToId(tr("Id"), false), QVariant::Int, tr("Id"), groupProperty);
	auto width = addProperty(nameToId(tr("Width"), false), QVariant::Int, tr("Width"), groupProperty);
	auto height = addProperty(nameToId(tr("Height"), false), QVariant::Int, tr("Height"), groupProperty);
	auto animated = addProperty(nameToId(tr("Animated"), false), QVariant::Bool, tr("Animated"), groupProperty);

	id->setAttribute(QLatin1String("minimum"), 0);
	width->setAttribute(QLatin1String("minimum"), 1);
	height->setAttribute(QLatin1String("minimum"), 1);

	id->setEnabled(false);
	width->setEnabled(false);
	height->setEnabled(false);
	animated->setEnabled(false);

	QtTreePropertyBrowser::addProperty(groupProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::addLayerProperties()
{
	auto groupProperty = mGroupManager->addProperty(tr("Layer"));

	auto name = addProperty(nameToId(tr("Name"), false), QVariant::String, tr("Name"), groupProperty);

	auto type = addProperty(nameToId(tr("Type"), false),
		QtVariantPropertyManager::enumTypeId(),
		tr("Type"), groupProperty);
	type->setAttribute(QLatin1String("enumNames"), mLayerTypeNames);

	auto opacity = addProperty(nameToId(tr("Opacity"), false), QVariant::Double, tr("Opacity"), groupProperty);
	auto isVisible = addProperty(nameToId(tr("Is Visible"), false), QVariant::Bool, tr("Is Visible"), groupProperty);
	auto isLocked = addProperty(nameToId(tr("Is Locked"), false), QVariant::Bool, tr("Is Locked"), groupProperty);

	opacity->setAttribute(QLatin1String("maximum"), 1.0);
	opacity->setAttribute(QLatin1String("minimum"), 0.0);
	opacity->setAttribute(QLatin1String("singleStep"), 0.1);
	opacity->setAttribute(QLatin1String("decimals"), 4);

	name->setEnabled(true);
	type->setEnabled(false);
	opacity->setEnabled(true);
	isVisible->setEnabled(true);
	isLocked->setEnabled(true);

	QtTreePropertyBrowser::addProperty(groupProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::addCustomProperties()
{
	mCustomPropertiesGroup = mGroupManager->addProperty(tr("Custom Properties"));

	decltype(auto) properties = mObject->properties();
	QMapIterator<QString, QVariant> iter(properties);

	while (iter.hasNext())
	{
		iter.next();

		addProperty(nameToId(iter.key(), true),
			iter.value().type(), iter.key(), mCustomPropertiesGroup);
	}

	QtTreePropertyBrowser::addProperty(mCustomPropertiesGroup);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::updateMapProperties()
{
	auto map = dynamic_cast<const Map*>(mObject);
	Q_ASSERT(map);

	mIdToProperty[nameToId(tr("Map Orientation"), false)]->setValue(static_cast<int>(map->orientation()));
	mIdToProperty[nameToId(tr("Tile Render Order"), false)]->setValue(static_cast<int>(map->renderOrder()));
	mIdToProperty[nameToId(tr("Width"), false)]->setValue(map->size().width());
	mIdToProperty[nameToId(tr("Height"), false)]->setValue(map->size().height());
	mIdToProperty[nameToId(tr("Tile Width"), false)]->setValue(map->tileSize().width());
	mIdToProperty[nameToId(tr("Tile Height"), false)]->setValue(map->tileSize().height());
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::updateTilesetProperties()
{
	auto tileset = dynamic_cast<const Tileset*>(mObject);
	Q_ASSERT(tileset);

	mIdToProperty[nameToId(tr("Name"), false)]->setValue(tileset->name());
	mIdToProperty[nameToId(tr("Source"), false)]->setValue(QUrl::fromLocalFile(tileset->imageReference().source()));
	mIdToProperty[nameToId(tr("Tile Width"), false)]->setValue(tileset->tileSize().width());
	mIdToProperty[nameToId(tr("Tile Height"), false)]->setValue(tileset->tileSize().height());
	mIdToProperty[nameToId(tr("Margin"), false)]->setValue(tileset->margin());
	mIdToProperty[nameToId(tr("Spacing"), false)]->setValue(tileset->spacing());
	mIdToProperty[nameToId(tr("Transparent Color"), false)]->setValue(tileset->imageReference().transparentColor());
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::updateTileProperties()
{
	auto tile = dynamic_cast<const Tile*>(mObject);
	Q_ASSERT(tile);

	mIdToProperty[nameToId(tr("Id"), false)]->setValue(tile->id());
	mIdToProperty[nameToId(tr("Width"), false)]->setValue(tile->width());
	mIdToProperty[nameToId(tr("Height"), false)]->setValue(tile->height());
	mIdToProperty[nameToId(tr("Animated"), false)]->setValue(tile->isAnimated());
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::updateLayerProperties()
{
	auto layer = dynamic_cast<const Layer*>(mObject);
	Q_ASSERT(layer);

	mIdToProperty[nameToId(tr("Name"), false)]->setValue(layer->name());
	mIdToProperty[nameToId(tr("Type"), false)]->setValue(layer->layerType());
	mIdToProperty[nameToId(tr("Opacity"), false)]->setValue(layer->opacity());
	mIdToProperty[nameToId(tr("Is Visible"), false)]->setValue(layer->isVisible());
	mIdToProperty[nameToId(tr("Is Locked"), false)]->setValue(layer->isLocked());
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::applyMapValue(const QString& id, const QVariant& value)
{
	if (id == nameToId(tr("Map Orientation"), false))
	{
		auto undoStack = mDocument->undoStack();
		auto map = dynamic_cast<Map*>(mObject);

		Q_ASSERT(mMapDocument);
		Q_ASSERT(map);

		undoStack->push(new ChangeMapProperty(mMapDocument,
			static_cast<Map::Orientation>(value.toInt())));
	}
	else if (id == nameToId(tr("Tile Render Order"), false))
	{
		auto undoStack = mDocument->undoStack();
		auto map = dynamic_cast<Map*>(mObject);

		Q_ASSERT(mMapDocument);
		Q_ASSERT(map);

		undoStack->push(new ChangeMapProperty(mMapDocument,
			static_cast<Map::RenderOrder>(value.toInt())));
	}
	else if (id == nameToId(tr("Tile Width"), false) ||
		id == nameToId(tr("Tile Height"), false))
	{
		auto undoStack = mDocument->undoStack();
		auto map = dynamic_cast<Map*>(mObject);

		Q_ASSERT(mMapDocument);
		Q_ASSERT(map);

		if (id == nameToId(tr("Tile Width"), false))
			undoStack->push(new ChangeMapProperty(mMapDocument,
				QSize(value.toInt(), map->tileSize().height())));
		else
			undoStack->push(new ChangeMapProperty(mMapDocument,
				QSize(map->tileSize().width(), value.toInt())));
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::applyTilesetValue(const QString& id, const QVariant& value)
{
	if (id == nameToId(tr("Name"), false))
	{
		auto undoStack = mDocument->undoStack();
		auto tileset = dynamic_cast<Tileset*>(mObject);

		Q_ASSERT(mMapDocument);
		Q_ASSERT(tileset);

		undoStack->push(new ChangedTilesetProperty(mMapDocument, tileset, value.toString()));
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::applyTileValue(const QString& id, const QVariant& value)
{
	Q_UNUSED(id);
	Q_UNUSED(value);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::applyLayerValue(const QString& id, const QVariant& value)
{
	if (id == nameToId(tr("Name"), false) || id == nameToId(tr("Opacity"), false) ||
		id == nameToId(tr("Is Visible"), false) || id == nameToId(tr("Is Locked"), false))
	{
		auto undoStack = mDocument->undoStack();
		auto layer = dynamic_cast<Layer*>(mObject);

		Q_ASSERT(mMapDocument);
		Q_ASSERT(layer);

		if (id == nameToId(tr("Name"), false))
			undoStack->push(new ChangeLayerProperty(mMapDocument, layer,
				value.toString()));
		else if (id == nameToId(tr("Opacity"), false))
			undoStack->push(new ChangeLayerProperty(mMapDocument, layer,
				value.toFloat()));
		else if (id == nameToId(tr("Is Visible"), false))
			undoStack->push(new ChangeLayerProperty(mMapDocument, layer,
				value.toBool(), ChangeLayerProperty::BoolProperty::Visible));
		else if (id == nameToId(tr("Is Locked"), false))
			undoStack->push(new ChangeLayerProperty(mMapDocument, layer,
				value.toBool(), ChangeLayerProperty::BoolProperty::Locked));
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::objectChanged(Object* object)
{
	if (mObject == object)
	{
		mUpdating = true;
		updateProperties();
		mUpdating = false;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::retranslateUi()
{
	mOrientationNames.clear();
	mRenderOrderNames.clear();
	mLayerTypeNames.clear();

	mOrientationNames.append(tr("Orthogonal"));
	mOrientationNames.append(tr("Isometric"));
	mOrientationNames.append(tr("Hexagonal"));

	mRenderOrderNames.append(tr("Right Down"));
	mRenderOrderNames.append(tr("Right Up"));
	mRenderOrderNames.append(tr("Left Down"));
	mRenderOrderNames.append(tr("Left Up"));

	mLayerTypeNames.append(tr("Tile Layer"));
	mLayerTypeNames.append(tr("Group Layer"));

	auto object = mObject;
	setObject(nullptr);
	setObject(object);
}
/*-----------------------------------------------------------------------------------------------------------*/
QtVariantProperty* PropertyBrowser::createProperty(const QString& id, int type, const QString& name)
{
	auto property = mVariantManager->addProperty(type, name);
	Q_ASSERT(property);

	if (type == QVariant::Bool)
		property->setAttribute(QLatin1String("textVisible"), false);
	else if (type == QVariant::String)
		property->setAttribute(QLatin1String("multiline"), true);
	else if (type == QVariant::Double)
		property->setAttribute(QLatin1String("decimals"), 9);

	mIdToProperty.insert(id, property);

	return property;
}
/*-----------------------------------------------------------------------------------------------------------*/
QtVariantProperty* PropertyBrowser::createCustomProperty(const QString& id, int type, const QString& name)
{
	auto properties = mCustomPropertiesGroup->subProperties();
	QtProperty* precedingProperty = nullptr;

	for (auto i = 0; i < properties.count(); ++i)
	{
		if (properties.at(i)->propertyName() < name)
			precedingProperty = properties.at(i);
		else break;
	}

	auto property = createProperty(id, type, name);

	mCustomPropertiesGroup->insertSubProperty(property, precedingProperty);

	return property;
}
/*-----------------------------------------------------------------------------------------------------------*/
QtVariantProperty* PropertyBrowser::addProperty(const QString& id, int type,
	const QString& name, QtProperty* parent)
{
	auto property = createProperty(id, type, name);
	parent->addSubProperty(property);

	return property;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertyBrowser::deleteCustomProperty(QtVariantProperty* property)
{
	auto id = nameToId(property->propertyName(), true);
	Q_ASSERT(mIdToProperty.contains(id));

	mIdToProperty.remove(id);
	delete property;
}
/*-----------------------------------------------------------------------------------------------------------*/
