/*-----------------------------------------------------------------------------------------------------------*/
#include <QString>
#include "tiledutils.h"
/*-----------------------------------------------------------------------------------------------------------*/
int chunkSize()
{
	return 16;
}
/*-----------------------------------------------------------------------------------------------------------*/
int chunkMask()
{
	return chunkSize() - 1;
}
/*-----------------------------------------------------------------------------------------------------------*/
QPoint operator&(const QPoint& point, const QPoint& mask)
{
	return QPoint(point.x() & mask.x(), point.y() & mask.y());
}
/*-----------------------------------------------------------------------------------------------------------*/
QPoint operator&(const QPoint& point, int mask)
{
	return QPoint(point.x() & mask, point.y() & mask);
}
/*-----------------------------------------------------------------------------------------------------------*/
QString mimeType(MimeTypes type)
{
	switch(type)
	{
	case MimeTypes::Frames:
		return QLatin1String("application/frame.list");
	case MimeTypes::Tiles:
		return QLatin1String("application/tile.list");
	case MimeTypes::Layers:
		return QLatin1String("application/layer.list");
	default: 
		return QString();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
