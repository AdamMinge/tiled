/*-----------------------------------------------------------------------------------------------------------*/
#include "zoomable.h"
/*-----------------------------------------------------------------------------------------------------------*/
Zoomable::Zoomable(QObject* parent) : 
	QObject(parent),
	mScale(1)
{
	mZoomFactors = QVector<qreal>
	{
		0.015625,
		0.03125,
		0.0625,
		0.125,
		0.25,
		0.33,
		0.5,
		0.75,
		1.0,
		1.5,
		2.0,
		3.0,
		4.0,
		5.5,
		8.0,
		11.0,
		16.0,
		23.0,
		32.0,
		45.0,
		64.0,
		90.0,
		128.0,
		180.0,
		256.0
	};
}
/*-----------------------------------------------------------------------------------------------------------*/
void Zoomable::setScale(qreal scale) 
{
	if (scale == mScale) return;

	mScale = scale;
	emit scaleChanged(mScale);
}
/*-----------------------------------------------------------------------------------------------------------*/
qreal Zoomable::scale() const 
{
	return mScale;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Zoomable::canZoomIn() const 
{
	return mScale < mZoomFactors.last();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool Zoomable::canZoomOut() const 
{
	return mScale > mZoomFactors.first();
}
/*-----------------------------------------------------------------------------------------------------------*/
void Zoomable::handleWheelDelta(int delta) 
{
	if (delta <= -120) zoomOut();
	else if (delta >= 120) zoomIn();
	else 
	{
		auto factor = 1 + 0.3 * qAbs(qreal(delta) / 8 / 15);
		if (delta < 0) factor = 1 / factor;

		const auto scale = qBound(
			mZoomFactors.first(),
			mScale * factor,
			mZoomFactors.last());

		setScale(std::floor(scale * 10000 + 0.5) / 10000);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void Zoomable::setZoomFactors(const QVector<qreal>& factors) 
{
	mZoomFactors = factors;
}
/*-----------------------------------------------------------------------------------------------------------*/
void Zoomable::zoomIn() 
{
	for (auto iter = mZoomFactors.begin(); iter < mZoomFactors.end(); ++iter)
	{
		if (*iter > mScale)
		{
			setScale(*iter);
			break;
		}
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void Zoomable::zoomOut() 
{
	for(auto iter = mZoomFactors.rbegin(); iter < mZoomFactors.rend(); ++iter)
	{
		if(*iter < mScale)
		{
			setScale(*iter);
			break;
		}
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void Zoomable::resetZoom() 
{
	setScale(1);
}
/*-----------------------------------------------------------------------------------------------------------*/