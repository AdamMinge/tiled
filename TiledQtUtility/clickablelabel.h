/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QLabel>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT ClickableLabel final : public QLabel
{
	Q_OBJECT

public:
	explicit ClickableLabel(QWidget *parent = nullptr);
	~ClickableLabel() override = default;

	ClickableLabel(ClickableLabel&&) = delete;
	ClickableLabel(const ClickableLabel&) = delete;

	ClickableLabel& operator=(ClickableLabel&&) = delete;
	ClickableLabel& operator=(const ClickableLabel&) = delete;

signals:
	void mouseMoved(QMouseEvent* event);
	void mousePressed(QMouseEvent* event);
	void mouseReleased(QMouseEvent* event);

protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
};
/*-----------------------------------------------------------------------------------------------------------*/