/*-----------------------------------------------------------------------------------------------------------*/
#include <QGuiApplication>
#include <QImageReader>
#include <QImageWriter>
#include <QFileInfo>
#include <QScreen>
#include <QSet>
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
static QString toImageFileFilter(const QList<QByteArray> &formats)
{
	auto filter(QCoreApplication::translate("Utils", "Image files"));
	filter += QLatin1String(" (");
	auto first = true;
	for (decltype(auto) format : formats) 
	{
		if (!first) filter += QLatin1Char(' ');
		first = false;
		filter += QLatin1String("*.");
		filter += QString::fromLatin1(format.toLower());
	}
	filter += QLatin1Char(')');
	return filter;
}
/*-----------------------------------------------------------------------------------------------------------*/
QString readableImageFormatsFilter()
{
	return toImageFileFilter(QImageReader::supportedImageFormats());
}
/*-----------------------------------------------------------------------------------------------------------*/
QString writableImageFormatsFilter()
{
	return toImageFileFilter(QImageWriter::supportedImageFormats());
}
/*-----------------------------------------------------------------------------------------------------------*/
qreal defaultDpiScale()
{
	static qreal scale = []() 
	{
		if (const QScreen *screen = QGuiApplication::primaryScreen()) return screen->logicalDotsPerInchX() / 96.0;
		else return 1.0;
	}();
	return scale;
}
/*-----------------------------------------------------------------------------------------------------------*/
qreal dpiScaled(qreal value)
{
	return value * defaultDpiScale();
}
/*-----------------------------------------------------------------------------------------------------------*/
QSize dpiScaled(QSize value)
{
	return QSize(qRound(dpiScaled(value.width())),
		qRound(dpiScaled(value.height())));
}
/*-----------------------------------------------------------------------------------------------------------*/
QPoint dpiScaled(QPoint value)
{
	return QPoint(qRound(dpiScaled(value.x())),
		qRound(dpiScaled(value.y())));
}
/*-----------------------------------------------------------------------------------------------------------*/
QRectF dpiScaled(QRectF value)
{
	return QRectF(dpiScaled(value.x()),
		dpiScaled(value.y()),
		dpiScaled(value.width()),
		dpiScaled(value.height()));
}
/*-----------------------------------------------------------------------------------------------------------*/
QSize iconSize(IconSize iconSize)
{
	switch(iconSize)
	{
	case IconSize::Small:
		return dpiScaled(QSize(16, 16));
	case IconSize::Medium:
		return dpiScaled(QSize(32, 32));
	case IconSize::Large:
		return dpiScaled(QSize(48, 48));
	default:
		return QSize();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
QString typeToName(int type)
{
	switch(type)
	{
	case QVariant::String:
		return QStringLiteral("string");
	case QVariant::Url:
		return QStringLiteral("file");
	case QVariant::Double:
		return QStringLiteral("float");
	case QVariant::Color:
		return QStringLiteral("color");
	default:
		return QVariant::typeToName(type);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
int nameToType(const QString& name)
{
	if(name == QLatin1String("string")) return QVariant::String;
	else if(name == QLatin1String("file")) return QVariant::Url;
	else if(name == QLatin1String("float")) return QVariant::Double;
	else if (name == QLatin1String("color")) return QVariant::Color;
	else return QVariant::nameToType(name.toLatin1().constData());
}
/*-----------------------------------------------------------------------------------------------------------*/
QIcon makeIcon(const QString& fileWithArgSize, const QList<QSize>& sizes)
{
	QIcon icon;
	for (decltype(auto) size : sizes)
	{
		auto stringSize = QString("%1x%2").arg(size.width()).arg(size.height());

		Q_ASSERT(QFileInfo::exists(fileWithArgSize.arg(stringSize)));
		icon.addFile(fileWithArgSize.arg(stringSize));
	}

	return icon;
}
/*-----------------------------------------------------------------------------------------------------------*/
