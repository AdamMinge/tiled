﻿/*-----------------------------------------------------------------------------------------------------------*/
#include "clickablelabel.h"
/*-----------------------------------------------------------------------------------------------------------*/
ClickableLabel::ClickableLabel(QWidget *parent) :
	QLabel(parent)
{

}
/*-----------------------------------------------------------------------------------------------------------*/
void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
{
	emit mouseMoved(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
	emit mousePressed(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
	emit mouseReleased(event);
}
/*-----------------------------------------------------------------------------------------------------------*/