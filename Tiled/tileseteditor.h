/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include "editor.h"
/*-----------------------------------------------------------------------------------------------------------*/
class QMainWindow;
class UndoDock;
class PropertiesDock;
class TilesetDocument;
class AnimationCreatorDialog;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetEditor final : public Editor
{
public:
	explicit TilesetEditor();
	~TilesetEditor() override = default;

	void setCurrentDocument(Document* document) override;
	Document* currentDocument() const override;

	QWidget *editorWidget() const override;

	void saveState() override;
	void restoreState() override;

	QList<QDockWidget*> dockWidgets() const override;
	QList<DialogWithToggleView*> dialogWidgets() const override;

private:
	TilesetDocument * mCurrentTilesetDocument;
	QScopedPointer<QMainWindow> mMainWindow;

	UndoDock* mUndoDock;
	PropertiesDock* mPropertiesDock;

	AnimationCreatorDialog* mAnimationCreator;
};
/*-----------------------------------------------------------------------------------------------------------*/