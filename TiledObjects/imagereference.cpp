/*-----------------------------------------------------------------------------------------------------------*/
#include "imagereference.h"
/*-----------------------------------------------------------------------------------------------------------*/
ImageReference::ImageReference(const QString& source, const QColor& transparentColor) :
	mSource(source),
	mTransparentColor(transparentColor)
{
	
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ImageReference::operator==(const ImageReference& other) 
{
	if (mSource == other.mSource && mTransparentColor == other.mTransparentColor) return true;
	else return false;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ImageReference::operator!=(const ImageReference& other) 
{
	return !(*this == other);
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& ImageReference::source() const
{
	return mSource;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QColor& ImageReference::transparentColor() const
{
	return mTransparentColor;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ImageReference::setSource(const QString& source) 
{
	mSource = source;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ImageReference::setTransparentColor(const QColor& transparentColor) 
{
	mTransparentColor = transparentColor;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ImageReference::hasImage() const 
{
	return !mSource.isEmpty();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ImageReference::hasTransparent() const
{
	return mTransparentColor.isValid();
}
/*-----------------------------------------------------------------------------------------------------------*/
QImage ImageReference::createImage() const
{
	if (hasImage()) return QImage(mSource);
	else return QImage();
}
/*-----------------------------------------------------------------------------------------------------------*/
