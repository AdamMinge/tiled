/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QProxyStyle>
/*-----------------------------------------------------------------------------------------------------------*/
class MapEitorProxyStyle final : public QProxyStyle
{
public:
	explicit MapEitorProxyStyle(QStyle* parent = nullptr);
	~MapEitorProxyStyle() override = default;

	MapEitorProxyStyle(const MapEitorProxyStyle&) = delete;
	MapEitorProxyStyle(MapEitorProxyStyle&&) = delete;

	MapEitorProxyStyle& operator=(const MapEitorProxyStyle&) = delete;
	MapEitorProxyStyle& operator=(MapEitorProxyStyle&&) = delete;

	void drawPrimitive(PrimitiveElement element, const QStyleOption * option,
		QPainter * painter, const QWidget * widget = nullptr) const override;
};
/*-----------------------------------------------------------------------------------------------------------*/