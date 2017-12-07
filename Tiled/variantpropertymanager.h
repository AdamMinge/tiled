/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QtVariantPropertyManager>
#include <QFileIconProvider>
/*-----------------------------------------------------------------------------------------------------------*/
class VariantPropertyManager final : public QtVariantPropertyManager
{
	Q_OBJECT

public:
	explicit VariantPropertyManager(QObject* parent = nullptr);
	~VariantPropertyManager() override = default;

	VariantPropertyManager(VariantPropertyManager&&) = delete;
	VariantPropertyManager(const VariantPropertyManager&) = delete;

	VariantPropertyManager& operator=(VariantPropertyManager&&) = delete;
	VariantPropertyManager& operator=(const VariantPropertyManager&) = delete;

	QVariant value(const QtProperty *property) const override;
	int valueType(int propertyType) const override;
	bool isPropertyTypeSupported(int propertyType) const override;

	QStringList attributes(int propertyType) const override;
	int attributeType(int propertyType, const QString &attribute) const override;
	QVariant attributeValue(const QtProperty *property, const QString &attribute) const override;

public slots:
	void setValue(QtProperty *property, const QVariant &value) override;
	void setAttribute(QtProperty *property, const QString &attribute, const QVariant &value) override;

protected:
	QString valueText(const QtProperty *property) const override;
	QIcon valueIcon(const QtProperty *property) const override;
	void initializeProperty(QtProperty *property) override;
	void uninitializeProperty(QtProperty *property) override;

private:
	struct FileIdData;
	
private:
	QMap<const QtProperty*, FileIdData> mFileIdValues;

	QFileIconProvider mIconProvider;
};
/*-----------------------------------------------------------------------------------------------------------*/
struct VariantPropertyManager::FileIdData
{
	QVariant value;
	QString filter;
};
/*-----------------------------------------------------------------------------------------------------------*/