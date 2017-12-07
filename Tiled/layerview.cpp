/*-----------------------------------------------------------------------------------------------------------*/
#include <QMenu>
#include <QHeaderView>
#include <QContextMenuEvent>
#include "utils.h"
#include "layer.h"
#include "layerview.h"
#include "mapdocument.h"
#include "layertreemodel.h"
#include "iconcheckdelegate.h"
#include "reversingproxymodel.h"
#include "commitonchangeddelegate.h"
#include "mapdocumentactionhandler.h"
/*-----------------------------------------------------------------------------------------------------------*/
LayerView::LayerView(QWidget* parent) :
	QTreeView(parent),
	mProxyModel(new ReversingProxyModel(this)),
	mMapDocument(nullptr)
{
	QList<QSize> sizes = { { QSize(14,14), QSize(16,16), QSize(24,24) } };

	auto lockedIcon = makeIcon(QLatin1String(":/Tiled/images/%1/locked.png"), sizes);
	auto unLockedIcon = makeIcon(QLatin1String(":/Tiled/images/%1/unlocked.png"), sizes);

	auto visibleIcon = makeIcon(QLatin1String(":/Tiled/images/%1/visible.png"), sizes);
	auto hiddenIcon = makeIcon(QLatin1String(":/Tiled/images/%1/hidden.png"), sizes);

	setItemDelegateForColumn(0, new CommitOnChangedDelegate(this));
	setItemDelegateForColumn(1, new IconCheckDelegate(visibleIcon, hiddenIcon, this));
	setItemDelegateForColumn(2, new IconCheckDelegate(lockedIcon, unLockedIcon, this));

	setHeaderHidden(true);
	QTreeView::setModel(mProxyModel);

	connect(this, &LayerView::pressed, this, &LayerView::indexPressed);
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerView::setMapDocument(MapDocument* mapDocument)
{
	if (mMapDocument == mapDocument) return;

	if(mMapDocument)
	{
		mMapDocument->disconnect(this);
		selectionModel()->disconnect(this);
	}

	mMapDocument = mapDocument;

	if(mMapDocument)
	{
		mProxyModel->setSourceModel(mMapDocument->layerModel());

		connect(mMapDocument, &MapDocument::currentLayerChanged,
			this, &LayerView::currentLayerChanged);
		connect(selectionModel(), &QItemSelectionModel::currentChanged,
			this, &LayerView::currentChanged);

		currentLayerChanged(mMapDocument->currentLayer());

		header()->setStretchLastSection(false);
		header()->setSectionResizeMode(0, QHeaderView::Stretch);
		header()->setSectionResizeMode(1, QHeaderView::Fixed);
		header()->setSectionResizeMode(2, QHeaderView::Fixed);
		header()->resizeSection(1, dpiScaled(22));
		header()->resizeSection(2, dpiScaled(22));
	}
	else
	{
		mProxyModel->setSourceModel(nullptr);
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerView::contextMenuEvent(QContextMenuEvent* event)
{
	if (!model()) return;

	auto index = indexAt(event->pos());
	QMenu menu;

	auto newLayerMenu = menu.addMenu(tr("New"));
	newLayerMenu->addAction(MapDocumentActionHandler::instance()->actionNewTileLayer());
	newLayerMenu->addAction(MapDocumentActionHandler::instance()->actionNewGroupLayer());

	if(index.isValid())
	{
		auto groupLayerMenu = menu.addMenu(tr("Group"));

		groupLayerMenu->addAction(MapDocumentActionHandler::instance()->actionGroupLayer());
		groupLayerMenu->addAction(MapDocumentActionHandler::instance()->actionUngroupLayer());

		menu.addAction(MapDocumentActionHandler::instance()->actionDuplicateLayer());
		menu.addAction(MapDocumentActionHandler::instance()->actionMergeLayerUp());
		menu.addAction(MapDocumentActionHandler::instance()->actionMergeLayerDown());
		menu.addAction(MapDocumentActionHandler::instance()->actionRemoveLayer());
		menu.addSeparator();
		menu.addAction(MapDocumentActionHandler::instance()->actionSelectNextLayer());
		menu.addAction(MapDocumentActionHandler::instance()->actionSelectPreviousLayer());
		menu.addAction(MapDocumentActionHandler::instance()->actionRaiseLayer());
		menu.addAction(MapDocumentActionHandler::instance()->actionLowerLayer());
		menu.addSeparator();
		menu.addAction(MapDocumentActionHandler::instance()->actionShowHideAllOtherLayers());
		menu.addSeparator();
		menu.addAction(MapDocumentActionHandler::instance()->actionLayerProperties());
	}

	menu.exec(event->globalPos());
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerView::currentLayerChanged(Layer* layer)
{
	Q_ASSERT(mMapDocument);

	auto sourceIndex = mMapDocument->layerModel()->index(layer);
	auto index = mProxyModel->mapFromSource(sourceIndex);

	selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerView::indexPressed(const QModelIndex& index)
{
	auto sourceIndex = mProxyModel->mapToSource(index);

	if (auto layer = mMapDocument->layerModel()->layer(sourceIndex))
		mMapDocument->setCurrentObject(layer);
}
/*-----------------------------------------------------------------------------------------------------------*/
void LayerView::currentChanged()
{
	Q_ASSERT(mMapDocument);

	auto index = selectionModel()->currentIndex();
	auto sourceIndex = mProxyModel->mapToSource(index);
	auto layer = mMapDocument->layerModel()->layer(sourceIndex);

	mMapDocument->setCurrentLayer(layer);
}
/*-----------------------------------------------------------------------------------------------------------*/
