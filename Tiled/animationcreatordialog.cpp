/*-----------------------------------------------------------------------------------------------------------*/
#include <QToolBar>
#include "animationcreatordialog.h"
#include "ui_animationcreator.h"
#include "spinboxdelegate.h"
#include "framelistmodel.h"
#include "tilesettablemodel.h"
#include "tilesetdocument.h"
#include "frame.h"
#include "tile.h"
#include "utils.h"
#include "rangeset.h"
/*-----------------------------------------------------------------------------------------------------------*/
AnimationCreatorDialog::AnimationCreatorDialog(QWidget* parent) :
	DialogWithToggleView(parent),
	mUi(new Ui::AnimationCreatorClass),
	mToolBar(new QToolBar),
	mFrameUp(nullptr),
	mFrameDown(nullptr),
	mFrameRemove(nullptr),
	mTile(nullptr),
	mTilesetDocument(nullptr),
	mFrameListModel(new FrameListModel(nullptr, nullptr, this)),
	mTilesetModel(new TilesetTableModel(static_cast<TilesetDocument*>(nullptr), nullptr, this))
{
	mUi->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	resize(dpiScaled(size()));
	
	mUi->toolbarLayout->addWidget(mToolBar, 1);
	mUi->tilesetView->setMarkAnimatedTiles(false);
	mUi->tilesetView->setModel(mTilesetModel);
	mUi->frameList->setModel(mFrameListModel);
	mUi->frameList->setItemDelegateForColumn(1, new SpinBoxDelegate({
	{ QLatin1String("minimum"), 1 },
	{ QLatin1String("maximum"), 999999 },
	{ QLatin1String("singleStep"), 1 },
	{ QLatin1String("frame"), false }
	}, mUi->frameList));

	buildToolBar();
	updateActions();
	retranslateUi();

	connect(mUi->tilesetView, &TilesetView::doubleClicked, 
		this, &AnimationCreatorDialog::addFrameForTileAt);
	
	connect(mFrameListModel, &FrameListModel::rowsMoved, 
		this, &AnimationCreatorDialog::updateActions);
	connect(mFrameListModel, &FrameListModel::rowsRemoved, 
		this, &AnimationCreatorDialog::updateActions);
	connect(mFrameListModel, &FrameListModel::rowsInserted, 
		this, &AnimationCreatorDialog::updateActions);
	connect(mFrameListModel, &FrameListModel::modelReset,
		this, &AnimationCreatorDialog::updateActions);
	connect(mUi->frameList->selectionModel(), &QItemSelectionModel::selectionChanged, 
		this, &AnimationCreatorDialog::updateActions);
}
/*-----------------------------------------------------------------------------------------------------------*/
AnimationCreatorDialog::~AnimationCreatorDialog()
{
	delete mUi; 
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::setTilesetDocument(TilesetDocument* tilesetDocument)
{
	if(tilesetDocument)
	{
		mTilesetDocument->disconnect(this);
	}

	mTilesetDocument = tilesetDocument;
	mUi->preview->setTilesetDocument(mTilesetDocument);
	mFrameListModel->setTilesetDocument(mTilesetDocument);
	mTilesetModel->setTilesetDocument(mTilesetDocument);

	if(mTilesetDocument)
	{
		connect(mTilesetDocument, &TilesetDocument::currentTileChanged,
			this, &AnimationCreatorDialog::setTile);
	}

	setTile(mTilesetDocument ? mTilesetDocument->currentTile() : nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::changeEvent(QEvent* event)
{
	QDialog::changeEvent(event);

	switch (event->type())
	{
	case QEvent::LanguageChange:
		mUi->retranslateUi(this);
		retranslateUi();
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::setTile(Tile* tile)
{
	if (mTile == tile) return;

	mTile = tile;

	mTilesetModel->setTileset(mTile ? mTile->tileset() : nullptr);
	mFrameListModel->setTile(mTile);

	mUi->frameList->setEnabled(static_cast<bool>(mTile));
	mUi->tilesetView->setEnabled(static_cast<bool>(mTile));
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::addFrameForTileAt(const QModelIndex& index)
{
	Q_ASSERT(mTile);

	auto tilesetModel = qobject_cast<TilesetTableModel*>(mUi->tilesetView->model());
	Q_ASSERT(tilesetModel);

	auto tile = tilesetModel->tile(index);
	Q_ASSERT(tile);

	mFrameListModel->addFrame(Frame(tile->id()));
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::frameUp()
{
	const auto selectionModel = mUi->frameList->selectionModel();
	auto currentIndex = selectionModel->currentIndex();
	Q_ASSERT(currentIndex.isValid());

	mFrameListModel->moveRow(currentIndex.parent(), currentIndex.row(),
		currentIndex.parent(), currentIndex.row() - 1);
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::frameDown()
{
	const auto selectionModel = mUi->frameList->selectionModel();
	auto currentIndex = selectionModel->currentIndex();
	Q_ASSERT(currentIndex.isValid());
	
	mFrameListModel->moveRow(currentIndex.parent(), currentIndex.row(),
		currentIndex.parent(), currentIndex.row() + 1);
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::framesRemove()
{
	const auto selectionModel = mUi->frameList->selectionModel();
	auto selectionIndexes = selectionModel->selectedIndexes();
	Q_ASSERT(!selectionIndexes.isEmpty());

	RangeSet<int> ranges;
	for (decltype(auto) index : selectionIndexes)
		ranges.insert(index.row());

	Q_ASSERT(!ranges.isEmpty());

	for(auto iter = ranges.rbegin(); iter != ranges.rend(); ++iter)
		mFrameListModel->removeRows(iter.first(), iter.length(), QModelIndex());
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::updateActions()
{
	const auto selectionModel = mUi->frameList->selectionModel();
	auto selectionIndexes = selectionModel->selectedRows();

	const auto oneSelected = selectionIndexes.size() == 1;
	const auto frameUpEnabled = oneSelected && selectionIndexes.first().row() > 0;
	const auto frameDownEnabled = oneSelected && selectionIndexes.first().row() < mFrameListModel->rowCount() - 1;

	mFrameUp->setEnabled(frameUpEnabled);
	mFrameDown->setEnabled(frameDownEnabled);
	mFrameRemove->setEnabled(selectionIndexes.size() > 0);
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::buildToolBar()
{
	Q_ASSERT(mToolBar);
	Q_ASSERT(!mFrameUp);
	Q_ASSERT(!mFrameDown);
	Q_ASSERT(!mFrameRemove);

	mFrameUp = new QAction(this);
	mFrameDown = new QAction(this);
	mFrameRemove = new QAction(this);

	mFrameRemove->setShortcut(QKeySequence::Delete);
	mFrameRemove->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	addAction(mFrameRemove);

	mFrameUp->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/go-up.png"), { QSize(16,16) }));
	mFrameDown->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/go-down.png"), { QSize(16,16) }));
	mFrameRemove->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-delete.png"), { QSize(16,16) }));

	mToolBar->addActions({ mFrameUp, mFrameDown, mFrameRemove });
	mToolBar->setIconSize(iconSize(IconSize::Small));

	connect(mFrameUp, &QAction::triggered, this, &AnimationCreatorDialog::frameUp);
	connect(mFrameDown, &QAction::triggered, this, &AnimationCreatorDialog::frameDown);
	connect(mFrameRemove, &QAction::triggered, this, &AnimationCreatorDialog::framesRemove);
}
/*-----------------------------------------------------------------------------------------------------------*/
void AnimationCreatorDialog::retranslateUi()
{
	setWindowTitle(tr("Tile Animation Editor"));
}
/*-----------------------------------------------------------------------------------------------------------*/
