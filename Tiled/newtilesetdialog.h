/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDialog>
#include "tileset.h"
/*-----------------------------------------------------------------------------------------------------------*/
namespace Ui { class NewTilesetDialogClass; }
/*-----------------------------------------------------------------------------------------------------------*/
class NewTilesetDialog final : public QDialog
{
	Q_OBJECT

public:
	explicit NewTilesetDialog(QWidget* parent = nullptr);
	~NewTilesetDialog() override;

	NewTilesetDialog(NewTilesetDialog&&) = delete;
	NewTilesetDialog(const NewTilesetDialog&) = delete;

	NewTilesetDialog& operator=(NewTilesetDialog&&) = delete;
	NewTilesetDialog& operator=(const NewTilesetDialog&) = delete;

	void setImagePath(const QString& path);
	
	Tileset* createTileset();

protected:
	void changeEvent(QEvent* event) override;

private slots:
	void browse();
	void nameEdited(const QString &name);
	void updateOkButton();
	void updateColorPickerButton();
	void tryAccept();
	void pickColorFromImage();
	void colorSelected(const QColor& color);

private:
	Ui::NewTilesetDialogClass* mUi;
	QString mPath;
	bool mNameWasEdited;
	Tileset* mNewTileset;
};
/*-----------------------------------------------------------------------------------------------------------*/
