/*-----------------------------------------------------------------------------------------------------------*/
#include <QColorDialog>
#include <QEvent>
#include <QPainter>
#include <QStyle>
#include "colorbutton.h"
/*-----------------------------------------------------------------------------------------------------------*/
ColorButton::ColorButton(QWidget *parent)
	: QToolButton(parent)
{
	const auto defaultIconSize = style()->pixelMetric(QStyle::PM_ButtonIconSize);
	setIconSize(QSize(defaultIconSize * 2, defaultIconSize));
	setColor(Qt::white);

	connect(this, &QToolButton::clicked, this, &ColorButton::pickColor);
}
/*-----------------------------------------------------------------------------------------------------------*/
const QColor& ColorButton::color() const
{
	return mColor;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ColorButton::setColor(const QColor &color)
{
	if (mColor == color || !color.isValid()) return;
	mColor = color;

	updateIcon();

	emit colorChanged(color);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ColorButton::changeEvent(QEvent *event)
{
	QToolButton::changeEvent(event);

	switch (event->type()) 
	{
		case QEvent::StyleChange: 
		{
			const auto defaultIconSize = style()->pixelMetric(QStyle::PM_ButtonIconSize);
			setIconSize(QSize(defaultIconSize * 2, defaultIconSize));
			updateIcon();
			break;
		}
		default:
			break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void ColorButton::pickColor()
{
	auto newColor = QColorDialog::getColor(mColor, this);
	if (newColor.isValid()) setColor(newColor);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ColorButton::updateIcon()
{
	auto size(iconSize());
	size.rwidth() -= 2;
	size.rheight() -= 2;

	QPixmap pixmap(size);
	pixmap.fill(mColor);

	QPainter painter(&pixmap);
	QColor border(Qt::black);
	border.setAlpha(128);
	painter.setPen(border);
	painter.drawRect(0, 0, pixmap.width() - 1, pixmap.height() - 1);

	setIcon(QIcon(pixmap));
}
/*-----------------------------------------------------------------------------------------------------------*/