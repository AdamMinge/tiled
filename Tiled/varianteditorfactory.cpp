/*-----------------------------------------------------------------------------------------------------------*/
#include <QUrl>
#include "varianteditorfactory.h"
#include "resetedit.h"
#include "fileedit.h"
/*-----------------------------------------------------------------------------------------------------------*/
VariantEditorFactory::VariantEditorFactory(QObject* parent) :
	QtVariantEditorFactory(parent)
{
}
/*-----------------------------------------------------------------------------------------------------------*/
VariantEditorFactory::~VariantEditorFactory()
{
	qDeleteAll(mFileEditToProperty.keys());
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantEditorFactory::connectPropertyManager(QtVariantPropertyManager* manager)
{
	connect(manager, &QtVariantPropertyManager::valueChanged, 
		this, &VariantEditorFactory::propertyChanged);
	connect(manager, &QtVariantPropertyManager::attributeChanged, 
		this, &VariantEditorFactory::propertyAttributeChanged);
	QtVariantEditorFactory::connectPropertyManager(manager);
}
/*-----------------------------------------------------------------------------------------------------------*/
QWidget* VariantEditorFactory::createEditor(QtVariantPropertyManager* manager, 
	QtProperty* property, QWidget* parent)
{
	const auto type = manager->propertyType(property);

	if(type == QVariant::Url)
	{
		auto editor = new FileEdit(parent);
		auto filePath = manager->value(property).toUrl();
		auto fileFilter = manager->attributeValue(property, QLatin1String("filter")).toString();

		editor->setFileUrl(filePath);
		editor->setFilter(fileFilter);

		mCreatedFileEdits[property].append(editor);
		mFileEditToProperty[editor] = property;

		connect(editor, &FileEdit::destroyed, this, &VariantEditorFactory::slotEditorDestroyed);
		connect(editor, &FileEdit::fileUrlChanged, this, &VariantEditorFactory::fileEditFileUrlChanged);

		return editor;
	}
	else if(type == QVariant::Color)
	{
		auto editor = new ResetEdit(property,
			QtVariantEditorFactory::createEditor(manager, property, parent), parent);

		connect(editor, &ResetEdit::resetProperty, this, &VariantEditorFactory::resetProperty);

		return editor;
	}
	
	return QtVariantEditorFactory::createEditor(manager, property, parent);
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantEditorFactory::disconnectPropertyManager(QtVariantPropertyManager* manager)
{
	disconnect(manager, &QtVariantPropertyManager::valueChanged,
		this, &VariantEditorFactory::propertyChanged);
	disconnect(manager, &QtVariantPropertyManager::attributeChanged,
		this, &VariantEditorFactory::propertyAttributeChanged);
	QtVariantEditorFactory::disconnectPropertyManager(manager);
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantEditorFactory::propertyChanged(QtProperty* property, const QVariant& value)
{
	if(mCreatedFileEdits.contains(property))
	{
		auto filePath = value.toUrl();
		for(auto edit : mCreatedFileEdits[property]) edit->setFileUrl(filePath);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantEditorFactory::propertyAttributeChanged(QtProperty* property, 
	const QString& attribute, const QVariant& value)
{
	if (mCreatedFileEdits.contains(property))
	{
		if(attribute == QLatin1String("filter"))
		{
			auto fileFilter = value.toString();
			for (auto edit : mCreatedFileEdits[property]) edit->setFilter(fileFilter);
		}
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantEditorFactory::slotEditorDestroyed(QObject* object)
{
	auto fileEdit = static_cast<FileEdit*>(object);

	if(auto property = mFileEditToProperty.value(fileEdit))
	{
		mFileEditToProperty.remove(fileEdit);
		mCreatedFileEdits[property].removeAll(fileEdit);

		if (mCreatedFileEdits[property].isEmpty()) mCreatedFileEdits.remove(property);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantEditorFactory::fileEditFileUrlChanged(const QUrl& value)
{
	auto fileEdit = qobject_cast<FileEdit*>(sender());
	Q_ASSERT(fileEdit);

	if(auto property = mFileEditToProperty.value(fileEdit))
	{
		auto manager = propertyManager(property);
		Q_ASSERT(manager);

		manager->setValue(property, value);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void VariantEditorFactory::resetProperty(QtProperty* property)
{
	auto manager = propertyManager(property);
	Q_ASSERT(manager);

	switch(manager->propertyType(property))
	{
	case QVariant::Color:
		manager->setValue(property, QColor());
		break;
	}	
}
/*-----------------------------------------------------------------------------------------------------------*/
