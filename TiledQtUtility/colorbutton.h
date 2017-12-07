/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QToolButton>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT ColorButton final : public QToolButton
{
	Q_OBJECT

public:
	explicit ColorButton(QWidget *parent = nullptr);
	~ColorButton() override = default;

	ColorButton(ColorButton&&) = delete;
	ColorButton(const ColorButton&) = delete;

	ColorButton& operator=(ColorButton&&) = delete;
	ColorButton& operator=(const ColorButton&) = delete;

	const QColor& color() const;
	void setColor(const QColor &color);

signals:
	void colorChanged(const QColor &color);

protected:
	void changeEvent(QEvent *event) override;

private:
	void pickColor();
	void updateIcon();

private:
	QColor mColor;
};
/*-----------------------------------------------------------------------------------------------------------*/
