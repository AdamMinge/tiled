/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QImage>
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT ImageReference final
{
public:
	explicit ImageReference(const QString& source = QString(), const QColor& transparentColor = QColor());
	~ImageReference() = default;

	ImageReference(ImageReference&&) = default;
	ImageReference(const ImageReference&) = default;

	ImageReference& operator=(ImageReference&&) = default;
	ImageReference& operator=(const ImageReference&) = default;

	bool operator==(const ImageReference& other);
	bool operator!=(const ImageReference& other);

	const QString& source() const;
	const QColor& transparentColor() const;

	void setSource(const QString& source);
	void setTransparentColor(const QColor& transparentColor);

	bool hasImage() const;
	bool hasTransparent() const;

	QImage createImage() const;

private:
	QString mSource;
	QColor mTransparentColor;
};
/*-----------------------------------------------------------------------------------------------------------*/
