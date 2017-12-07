/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDialog>
#include "map.h"
/*-----------------------------------------------------------------------------------------------------------*/
namespace Ui { class NewMapDialogClass; }
/*-----------------------------------------------------------------------------------------------------------*/
class NewMapDialog final : public QDialog
{
	Q_OBJECT

public:
	explicit NewMapDialog(QWidget* parent = nullptr);
	~NewMapDialog() override;

	NewMapDialog(NewMapDialog&&) = delete;
	NewMapDialog(const NewMapDialog&) = delete;

	NewMapDialog& operator=(NewMapDialog&&) = delete;
	NewMapDialog& operator=(const NewMapDialog&) = delete;

	Map* createMap();

protected:
	void changeEvent(QEvent* event) override;

private slots:
	void tryAccept();
	void updatePixelSize();

private:
	Ui::NewMapDialogClass* mUi;
	Map* mNewMap;
};
/*-----------------------------------------------------------------------------------------------------------*/