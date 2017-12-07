/*-----------------------------------------------------------------------------------------------------------*/
#include "ui_newmapdialog.h"
#include "preferencesmanager.h"
#include "newmapdialog.h"
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
static Map::Orientation orientationByIndex(int index)
{
	Q_ASSERT(index >= static_cast<int>(Map::Orientation::Orthogonal) &&
		index <= static_cast<int>(Map::Orientation::Hexagonal));

	auto orientation = static_cast<Map::Orientation>(index);
	return orientation;
}
/*-----------------------------------------------------------------------------------------------------------*/
static Map::RenderOrder renderOrderByIndex(int index)
{
	Q_ASSERT(index >= static_cast<int>(Map::RenderOrder::RightDown) &&
		index <= static_cast<int>(Map::RenderOrder::LeftUp));

	auto renderOrder = static_cast<Map::RenderOrder>(index);
	return renderOrder;
}
/*-----------------------------------------------------------------------------------------------------------*/
NewMapDialog::NewMapDialog(QWidget* parent) :
	QDialog(parent),
	mUi(new Ui::NewMapDialogClass),
	mNewMap(nullptr)
{
	mUi->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	resize(dpiScaled(size()));

	auto preferences = PreferencesManager::instance();
	mUi->orientation->setCurrentIndex(preferences->newMapOrientationIndex());
	mUi->renderOrder->setCurrentIndex(preferences->newMapRenderOrderIndex());
	mUi->mapWidth->setValue(preferences->newMapSize().width());
	mUi->mapHeight->setValue(preferences->newMapSize().height());
	mUi->tileWidth->setValue(preferences->newMapTileSize().width());
	mUi->tileHeight->setValue(preferences->newMapTileSize().height());

	connect(mUi->mapWidth, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &NewMapDialog::updatePixelSize);
	connect(mUi->mapHeight, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &NewMapDialog::updatePixelSize);
	connect(mUi->tileWidth, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &NewMapDialog::updatePixelSize);
	connect(mUi->tileHeight, QOverload<int>::of(&QSpinBox::valueChanged),
		this, &NewMapDialog::updatePixelSize);
	connect(mUi->orientation, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &NewMapDialog::updatePixelSize);

	updatePixelSize();
}
/*-----------------------------------------------------------------------------------------------------------*/
NewMapDialog::~NewMapDialog()
{
	delete mUi;
}
/*-----------------------------------------------------------------------------------------------------------*/
Map* NewMapDialog::createMap()
{
	if (exec() != QDialog::Accepted) return nullptr;
	else return mNewMap;
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewMapDialog::changeEvent(QEvent* event)
{
	QDialog::changeEvent(event);

	switch (event->type())
	{
	case QEvent::LanguageChange:
		mUi->retranslateUi(this);
		updatePixelSize();
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewMapDialog::tryAccept()
{
	auto mapOrientation = orientationByIndex(mUi->orientation->currentIndex());
	auto mapRenderOrder = renderOrderByIndex(mUi->renderOrder->currentIndex());
	auto mapSize = QSize(mUi->mapWidth->value(), mUi->mapHeight->value());
	auto tileSize = QSize(mUi->tileWidth->value(), mUi->tileHeight->value());

	Q_ASSERT(mapSize.width() > 0 && mapSize.height() > 0);
	Q_ASSERT(tileSize.width() > 0 && tileSize.height() > 0);

	auto map = new Map(mapOrientation, mapRenderOrder, mapSize, tileSize);
	Q_ASSERT(map);

	auto preferences = PreferencesManager::instance();
	preferences->setNewMapOrientationIndex(mUi->orientation->currentIndex());
	preferences->setNewMapRenderOrderIndex(mUi->renderOrder->currentIndex());
	preferences->setNewMapSize(mapSize);
	preferences->setNewMapTileSize(tileSize);

	mNewMap = map;
	accept();
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewMapDialog::updatePixelSize()
{
	auto mapOrientation = orientationByIndex(mUi->orientation->currentIndex());
	QSize size;

	switch(mapOrientation)
	{
	case Map::Orientation::Orthogonal:
		size = QSize(32, 32);
		break;

	case Map::Orientation::Isometric:
		size = QSize(32, 32);
		break;

	case Map::Orientation::Hexagonal:
		size = QSize(32, 32);
		break;

	default:
		Q_ASSERT(false);
		break;
	}

	mUi->pixelSizeLabel->setText(tr("%1 x %2 pixels")
		.arg(size.width())
		.arg(size.height()));
}
/*-----------------------------------------------------------------------------------------------------------*/
