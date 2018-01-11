/*-----------------------------------------------------------------------------------------------------------*/
#include <QDesktopWidget>
#include <QMouseEvent>
#include "ui_imagecolorpickerwidget.h"
#include "imagecolorpickerwidget.h"
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
ImageColorPickerWidget::ImageColorPickerWidget(QWidget *parent) :
	QFrame(parent, Qt::Popup),
	mUi(new Ui::ImageColorPickerWidgetClass)
{
	mUi->setupUi(this);

	connect(mUi->imageArea, &ClickableLabel::mouseMoved, this, &ImageColorPickerWidget::onMouseMove);
	connect(mUi->imageArea, &ClickableLabel::mouseReleased, this, &ImageColorPickerWidget::onMouseRelease);

	mPreviewIcon = QPixmap(dpiScaled(QSize(96, 24)));
	mPreviewIcon.fill(Qt::transparent);
	mUi->preview->setPixmap(mPreviewIcon);
}
/*-----------------------------------------------------------------------------------------------------------*/
ImageColorPickerWidget::~ImageColorPickerWidget()
{
	delete mUi;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool ImageColorPickerWidget::selectColor(const QString& image)
{
	QPixmap pix(image);
	if (pix.isNull()) return false;

	mImage = pix.toImage();
	mScaleX = 1;
	mScaleY = 1;

	auto rct = QApplication::desktop()->availableGeometry(this);
	const auto maxW = rct.width() * (2.0 / 3.0), maxH = rct.height() * (2.0 / 3.0);

	if (mImage.width() > maxW || mImage.height() > maxH) 
	{
		pix = pix.scaled(static_cast<int>(maxW), static_cast<int>(maxH), Qt::KeepAspectRatio);
		mScaleX = static_cast<double>(qMin(mImage.width(), pix.width())) 
		/ static_cast<double>(qMax(mImage.width(), pix.width()));
		mScaleY = static_cast<double>(qMin(mImage.height(), pix.height())) 
		/ static_cast<double>(qMax(mImage.height(), pix.height()));
	}

	mUi->imageArea->setPixmap(pix);
	mUi->imageArea->adjustSize();

	show();

	return true;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ImageColorPickerWidget::onMouseMove(QMouseEvent* event)
{
	if (!mImage.isNull()) 
	{
		auto pix = QPixmap::grabWidget(mUi->imageArea);
		auto image(pix.toImage());

		mPreviewColor = image.pixel(event->pos().x(), event->pos().y());
		if (!mPreviewColor.isValid())
			mPreviewColor = mSelectedColor;

		mPreviewIcon.fill(mPreviewColor);
		mUi->preview->setPixmap(mPreviewIcon);
		mUi->colorName->setText(mPreviewColor.name());
	}
	else 
	{
		mPreviewColor = mSelectedColor;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void ImageColorPickerWidget::onMouseRelease(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton) 
	{
		if (!mImage.isNull()) 
		{
			mSelectedColor = mPreviewColor;
			emit colorSelected(mSelectedColor);
			close();
		}
	}
	else if (event->button() == Qt::MouseButton::RightButton)
	{
		close();
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void ImageColorPickerWidget::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event)

	move(QApplication::desktop()->availableGeometry(parentWidget()).center() - rect().center());
}
/*-----------------------------------------------------------------------------------------------------------*/
