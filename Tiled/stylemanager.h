/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
#include <QMap>
#include <functional>
/*-----------------------------------------------------------------------------------------------------------*/
class QStyle;
/*-----------------------------------------------------------------------------------------------------------*/
class StyleManager final : public QObject
{
	Q_OBJECT

public:
	using styleCreatorFun = std::function<QStyle*()>;

public:
	static StyleManager* instance();
	static void deleteInstance();

	StyleManager(StyleManager&&) = delete;
	StyleManager(const StyleManager&) = delete;

	StyleManager& operator=(StyleManager&&) = delete;
	StyleManager& operator=(const StyleManager&) = delete;

	QStringList availableStyles() const;

	void registerStyle(styleCreatorFun creator, const QString& name);
	void unregisterStyle(const QString& name);

	const QString& style() const;

public slots:
	void setStyle(const QString& name);
	
signals:
	void styleChanged(const QString& name);
	void styleRegistered(const QString& name);
	void styleUnregistered(const QString& name);

private:
	explicit StyleManager() = default;
	~StyleManager() override = default;

private:
	static StyleManager* mInstance;

	QString mStyleName;
	QMap<QString, styleCreatorFun> mNameToStyle;
};
/*-----------------------------------------------------------------------------------------------------------*/