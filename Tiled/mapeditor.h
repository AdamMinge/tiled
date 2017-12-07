/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QScopedPointer>
#include "editor.h"
/*-----------------------------------------------------------------------------------------------------------*/
class QMainWindow;
class MapDocument;
class UndoDock;
class LayerDock;
class TilesetDock;
class TilesetsDock;
class PropertiesDock;
class AnimationCreatorDialog;
/*-----------------------------------------------------------------------------------------------------------*/
class MapEditor final : public Editor
{
	Q_OBJECT

public:
	explicit MapEditor();
	~MapEditor() override = default;

	void setCurrentDocument(Document* document) override;
	Document* currentDocument() const override;

	QWidget *editorWidget() const override;

	void saveState() override;
	void restoreState() override;

	QList<QDockWidget*> dockWidgets() const override;
	QList<DialogWithToggleView*> dialogWidgets() const override;

private:
	MapDocument* mCurrentMapDocument;
	QScopedPointer<QMainWindow> mMainWindow;

	UndoDock* mUndoDock;
	TilesetDock* mTilesetDock;
	TilesetsDock* mTilesetsDock;
	PropertiesDock* mPropertiesDock;
	LayerDock* mLayerDock;

	AnimationCreatorDialog* mAnimationCreator;
};
/*-----------------------------------------------------------------------------------------------------------*/
