/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QTreeView>
/*-----------------------------------------------------------------------------------------------------------*/
class ReversingProxyModel;
class MapDocument;
class Layer;
/*-----------------------------------------------------------------------------------------------------------*/
class LayerView final : public QTreeView
{
	Q_OBJECT

public:
	explicit LayerView(QWidget* parent = nullptr);
	~LayerView() = default;

	LayerView(const LayerView&) = delete;
	LayerView(LayerView&&) = delete;

	LayerView& operator=(const LayerView&) = delete;
	LayerView& operator=(LayerView&&) = delete;

	void setMapDocument(MapDocument* mapDocument);

protected:
	void contextMenuEvent(QContextMenuEvent *event) override;

private slots: 
	void currentLayerChanged(Layer* layer);
	void indexPressed(const QModelIndex& index);
	void currentChanged();

private:
	ReversingProxyModel* mProxyModel;
	MapDocument *mMapDocument;
};
/*-----------------------------------------------------------------------------------------------------------*/