/*-----------------------------------------------------------------------------------------------------------*/
#include <QStyleOption>
#include "mapditorproxystyle.h"
/*-----------------------------------------------------------------------------------------------------------*/
MapEitorProxyStyle::MapEitorProxyStyle(QStyle* parent) :
	QProxyStyle(parent)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void MapEitorProxyStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option,
	QPainter* painter, const QWidget* widget) const
{
	if (element == QStyle::PE_IndicatorItemViewItemDrop && !option->rect.isNull())
	{
		auto opt(*option);
		opt.rect.setLeft(0);
		if (widget) opt.rect.setRight(widget->width());
		QProxyStyle::drawPrimitive(element, &opt, painter, widget);
	}
	else QProxyStyle::drawPrimitive(element, option, painter, widget);
}
/*-----------------------------------------------------------------------------------------------------------*/