/*-----------------------------------------------------------------------------------------------------------*/
#include <QFileDialog>
#include <QMessageBox>
#include "ui_newtilesetdialog.h"
#include "imagereference.h"
#include "imagecolorpickerwidget.h"
#include "newtilesetdialog.h"
#include "preferencesmanager.h"
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
NewTilesetDialog::NewTilesetDialog(QWidget* parent) :
	QDialog(parent),
	mUi(new Ui::NewTilesetDialogClass),
	mNameWasEdited(false),
	mNewTileset(nullptr)
{
	mUi->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	resize(dpiScaled(size()));

	const auto preferences = PreferencesManager::instance();
	mUi->useTransparentColor->setChecked(preferences->newTilesetUseTransparentColor());
	mUi->colorButton->setColor(preferences->newTilesetTransparentColor());
	mUi->tileWidth->setValue(preferences->newTilesetTileSize().width());
	mUi->tileHeight->setValue(preferences->newTilesetTileSize().height());
	mUi->spacing->setValue(preferences->newTilesetSpacing());
	mUi->margin->setValue(preferences->newTilesetMargin());

	connect(mUi->browseButton, &QPushButton::clicked, this, &NewTilesetDialog::browse);
	connect(mUi->name, &QLineEdit::textEdited, this, &NewTilesetDialog::nameEdited);
	connect(mUi->name, &QLineEdit::textChanged, this, &NewTilesetDialog::updateOkButton);
	connect(mUi->image, &QLineEdit::textChanged, this, &NewTilesetDialog::updateOkButton);
	connect(mUi->image, &QLineEdit::textChanged, this, &NewTilesetDialog::updateColorPickerButton);
	connect(mUi->useTransparentColor, &QCheckBox::toggled, this, &NewTilesetDialog::updateColorPickerButton);
	connect(mUi->dropperButton, &QToolButton::clicked, this, &NewTilesetDialog::pickColorFromImage);

	updateOkButton();
}
/*-----------------------------------------------------------------------------------------------------------*/
NewTilesetDialog::~NewTilesetDialog()
{
	delete mUi;
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::setImagePath(const QString& path)
{
	mPath = path;
	const QFileInfo fileInfo(path);

	if (fileInfo.isFile()) 
	{
		mUi->image->setText(path);
		mUi->name->setText(fileInfo.completeBaseName());
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
Tileset* NewTilesetDialog::createTileset()
{
	if (exec() != QDialog::Accepted) return nullptr;
	else return mNewTileset;
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::changeEvent(QEvent* event)
{
	QDialog::changeEvent(event);

	switch (event->type())
	{
	case QEvent::LanguageChange:
		mUi->retranslateUi(this);
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::browse()
{
	const auto filter = readableImageFormatsFilter();
	auto path = QFileDialog::getOpenFileName(this, tr("Tileset Image"), mPath, filter);

	if (!path.isEmpty())
	{
		mUi->image->setText(path);
		mPath = path;

		if (!mNameWasEdited)
			mUi->name->setText(QFileInfo(mPath).completeBaseName());
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::nameEdited(const QString& name)
{
	mNameWasEdited = !name.isEmpty();
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::updateOkButton()
{
	auto okButton = mUi->buttonBox->button(QDialogButtonBox::Ok);

	auto enabled = true;
	enabled &= !mUi->name->text().isEmpty();
	enabled &= !mUi->image->text().isEmpty();

	okButton->setEnabled(enabled);
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::updateColorPickerButton()
{
	mUi->dropperButton->setEnabled(mUi->useTransparentColor->isChecked() &&
		!mUi->image->text().isEmpty());
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::tryAccept()
{
	const auto name = mUi->name->text();
	const auto image = mUi->image->text();
	const auto useTransparentColor = mUi->useTransparentColor->isChecked();
	const auto transparentColor = mUi->colorButton->color();
	const auto tileWidth = mUi->tileWidth->value();
	const auto tileHeight = mUi->tileHeight->value();
	const auto spacing = mUi->spacing->value();
	const auto margin = mUi->margin->value();

	Q_ASSERT(!name.isEmpty());
	Q_ASSERT(!image.isEmpty());
	Q_ASSERT((useTransparentColor) ? transparentColor.isValid() : true);
	Q_ASSERT(tileWidth >= 0 && tileHeight >= 0);
	Q_ASSERT(spacing >= 0 && margin >= 0);

	auto tileset = new Tileset(name, ImageReference(image,
		(useTransparentColor) ? transparentColor : QColor()),
		QSize(tileWidth, tileHeight), spacing, margin);

	Q_ASSERT(tileset);

	tileset->loadTileset();
	if(!tileset->isValid())
	{
		QMessageBox::critical(this, tr("Error"),
			tr("Failed to load tileset image '%1'.")
			.arg(image));
		return;
	}
	if(tileset->tileCount() == 0)
	{
		QMessageBox::critical(this, tr("Error"),
			tr("No tiles found in the tileset image "
				"when using the given tile size, "
				"margin and spacing!"));
		return;
	}

	auto preferences = PreferencesManager::instance();
	preferences->setNewTilesetUseTransparentColor(useTransparentColor);
	preferences->setNewTilesetTransparentColor(transparentColor);
	preferences->setNewTilesetTileSize(QSize(tileWidth, tileHeight));
	preferences->setNewTilesetSpacing(spacing);
	preferences->setNewTilesetMargin(margin);
	
	mNewTileset = tileset;
	accept();
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::pickColorFromImage()
{
	auto *popup = new ImageColorPickerWidget(mUi->dropperButton);
	popup->setAttribute(Qt::WA_DeleteOnClose);

	connect(popup, SIGNAL(colorSelected(QColor)), SLOT(colorSelected(QColor)));

	if (!popup->selectColor(mUi->image->text())) delete popup;
}
/*-----------------------------------------------------------------------------------------------------------*/
void NewTilesetDialog::colorSelected(const QColor& color)
{
	mUi->colorButton->setColor(color);
}
/*-----------------------------------------------------------------------------------------------------------*/
