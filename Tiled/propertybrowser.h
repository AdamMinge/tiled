/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtTreePropertyBrowser>
#include <QtGroupPropertyManager>
#include <QtVariantProperty>
/*-----------------------------------------------------------------------------------------------------------*/
class Document;
class QtVariantPropertyManager;
class Object;
class Map;
class Tile;
class Tileset;
class MapDocument;
class TilesetDocument;
/*-----------------------------------------------------------------------------------------------------------*/
class PropertyBrowser final : public QtTreePropertyBrowser
{
	Q_OBJECT

public:
	explicit PropertyBrowser(QWidget *parent = nullptr);
	~PropertyBrowser() override = default;

	PropertyBrowser(PropertyBrowser&&) = delete;
	PropertyBrowser(const PropertyBrowser&) = delete;

	PropertyBrowser& operator=(PropertyBrowser&&) = delete;
	PropertyBrowser& operator=(const PropertyBrowser&) = delete;

	void setDocument(Document* document);
	void setObject(Object *object);

	bool isCustomPropertyItem(const QtBrowserItem* item) const;
	bool allCustomPropertyItem(const QList<QtBrowserItem*>& items) const;

protected:
	bool event(QEvent *event) override;

private slots:
	void propertyAdded(Object *object, const QString &name);
	void propertyRemoved(Object *object, const QString &name);
	void propertyChanged(Object *object, const QString &name);

	void valueChanged(QtProperty *property, const QVariant &val);

private:
	void removeProperties();
	void addProperties();

	void updateProperties();
	void updateCustomProperties();

	void addMapProperties();
	void addTilesetProperties();
	void addTileProperties();
	void addLayerProperties();
	void addCustomProperties();

	void updateMapProperties();
	void updateTilesetProperties();
	void updateTileProperties();
	void updateLayerProperties();

	void applyMapValue(const QString& id, const QVariant& value);
	void applyTilesetValue(const QString& id, const QVariant& value);
	void applyTileValue(const QString& id, const QVariant& value);
	void applyLayerValue(const QString& id, const QVariant& value);

	void objectChanged(Object* object);

	void retranslateUi();

private:
	QtVariantProperty* createProperty(const QString& id, int type, const QString& name);
	QtVariantProperty* createCustomProperty(const QString& id, int type, const QString& name);
	QtVariantProperty* addProperty(const QString& id, int type, const QString& name, QtProperty* parent);

	void deleteCustomProperty(QtVariantProperty* property);

private:
	Document* mDocument;
	MapDocument* mMapDocument;
	TilesetDocument* mTilesetDocument;
	Object *mObject;

	QtVariantPropertyManager *mVariantManager;
	QtGroupPropertyManager *mGroupManager;
	QtProperty *mCustomPropertiesGroup;

	QHash<QString, QtVariantProperty*> mIdToProperty;

	QStringList mOrientationNames;
	QStringList mRenderOrderNames;
	QStringList mLayerTypeNames;

	bool mUpdating;
};
/*-----------------------------------------------------------------------------------------------------------*/
