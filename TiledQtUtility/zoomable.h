/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
#include <QVector>
/*-----------------------------------------------------------------------------------------------------------*/
class Zoomable final : public QObject
{
	Q_OBJECT

public:
	explicit Zoomable(QObject *parent = nullptr);
	~Zoomable() override = default;

	Zoomable(Zoomable&&) = default;
	Zoomable(const Zoomable&) = default;

	Zoomable& operator=(Zoomable&&) = default;
	Zoomable& operator=(const Zoomable&) = default;

	void setScale(qreal scale);
	qreal scale() const;

	bool canZoomIn() const;
	bool canZoomOut() const;

	void handleWheelDelta(int delta);

	void setZoomFactors(const QVector<qreal>& factors);

public slots:
	void zoomIn();
	void zoomOut();
	void resetZoom();

signals:
	void scaleChanged(qreal scale);

private:
	qreal mScale;
	QVector<qreal> mZoomFactors;
};
/*-----------------------------------------------------------------------------------------------------------*/
