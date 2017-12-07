/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QWidget>
/*-----------------------------------------------------------------------------------------------------------*/
namespace Ui { class NoEditorWidgetClass; }
/*-----------------------------------------------------------------------------------------------------------*/
class NoEditorWidget final : public QWidget
{
	Q_OBJECT

public:
	explicit NoEditorWidget(QWidget *parent = nullptr);
	~NoEditorWidget() override;

	NoEditorWidget(NoEditorWidget&&) = delete;
	NoEditorWidget(const NoEditorWidget&) = delete;

	NoEditorWidget& operator=(NoEditorWidget&&) = delete;
	NoEditorWidget& operator=(const NoEditorWidget&) = delete;

private slots:
	void newMap();

private:
	Ui::NoEditorWidgetClass* mUi;
};
/*-----------------------------------------------------------------------------------------------------------*/
