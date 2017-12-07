/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtVariantEditorFactory>
/*-----------------------------------------------------------------------------------------------------------*/	
class FileEdit;
/*-----------------------------------------------------------------------------------------------------------*/
class VariantEditorFactory final : public QtVariantEditorFactory
{
	Q_OBJECT

public:
	explicit VariantEditorFactory(QObject* parent = nullptr);
	~VariantEditorFactory() override;

	VariantEditorFactory(VariantEditorFactory&&) = delete;
	VariantEditorFactory(const VariantEditorFactory&) = delete;

	VariantEditorFactory& operator=(VariantEditorFactory&&) = delete;
	VariantEditorFactory& operator=(const VariantEditorFactory&) = delete;

protected:
	void connectPropertyManager(QtVariantPropertyManager* manager) override;
	QWidget *createEditor(QtVariantPropertyManager* manager, QtProperty* property, QWidget* parent) override;
	void disconnectPropertyManager(QtVariantPropertyManager* manager) override;

private slots:
	void propertyChanged(QtProperty* property, const QVariant &value);
	void propertyAttributeChanged(QtProperty* property, const QString &attribute, const QVariant &value);
	void slotEditorDestroyed(QObject* object);

	void fileEditFileUrlChanged(const QUrl &value);
	void resetProperty(QtProperty* property);

private:
	QMap<QtProperty*, QList<FileEdit*> > mCreatedFileEdits;
	QMap<FileEdit*, QtProperty*> mFileEditToProperty;
};
/*-----------------------------------------------------------------------------------------------------------*/
