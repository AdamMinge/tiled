/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "dialogwithtoggleview.h"
/*-----------------------------------------------------------------------------------------------------------*/
namespace Ui { class AnimationCreatorClass; }
class FrameListModel;
class TilesetTableModel;
class Tile;
class Tileset;
class TilesetDocument;
class QToolBar;
/*-----------------------------------------------------------------------------------------------------------*/
class AnimationCreatorDialog final : public DialogWithToggleView
{
	Q_OBJECT

public:
	explicit AnimationCreatorDialog(QWidget *parent = nullptr);
	~AnimationCreatorDialog() override;

	AnimationCreatorDialog(AnimationCreatorDialog&&) = delete;
	AnimationCreatorDialog(const AnimationCreatorDialog&) = delete;

	AnimationCreatorDialog& operator=(AnimationCreatorDialog&&) = delete;
	AnimationCreatorDialog& operator=(const AnimationCreatorDialog&) = delete;

	void setTilesetDocument(TilesetDocument* tilesetDocument);

protected:
	void changeEvent(QEvent* event) override;

private slots:
	void setTile(Tile* tile);
	void addFrameForTileAt(const QModelIndex &index);

	void frameUp();
	void frameDown();
	void framesRemove();

	void updateActions();

private:
	void buildToolBar();
	void retranslateUi();

private:
	Ui::AnimationCreatorClass* mUi;

	QToolBar* mToolBar;
	QAction* mFrameUp;
	QAction* mFrameDown;
	QAction* mFrameRemove;
	
	Tile* mTile;
	TilesetDocument* mTilesetDocument;
	FrameListModel* mFrameListModel;
	TilesetTableModel* mTilesetModel;
};
/*-----------------------------------------------------------------------------------------------------------*/
