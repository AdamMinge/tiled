/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDockWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class QToolBar;
class QMenu;
class MapDocument;
class LayerView;
class LayerTreeModel;
class Layer;
/*-----------------------------------------------------------------------------------------------------------*/
class LayerDock final : public QDockWidget
{
	Q_OBJECT

public:
	explicit LayerDock(QWidget* parent = nullptr);
	~LayerDock() override = default;

	LayerDock(LayerDock&&) = delete;
	LayerDock(const LayerDock&) = delete;

	LayerDock& operator=(LayerDock&&) = delete;
	LayerDock& operator=(const LayerDock&) = delete;

	void setMapDocument(MapDocument* document);

protected:
	void changeEvent(QEvent* event) override;

private:
	void buildToolBar();
	void retranslateUi();

private:
	MapDocument* mMapDocument;

	LayerView* mLayerView;

	QToolBar* mToolBar;
	QMenu* mNewLayerMenu;
};
/*-----------------------------------------------------------------------------------------------------------*/