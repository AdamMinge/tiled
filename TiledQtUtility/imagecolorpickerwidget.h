/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QFrame>
/*-----------------------------------------------------------------------------------------------------------*/
namespace Ui { class ImageColorPickerWidgetClass; }
/*-----------------------------------------------------------------------------------------------------------*/
class ImageColorPickerWidget final : public QFrame
{
	Q_OBJECT

public:
	explicit ImageColorPickerWidget(QWidget *parent = nullptr);
	~ImageColorPickerWidget() override;

	ImageColorPickerWidget(ImageColorPickerWidget&&) = delete;
	ImageColorPickerWidget(const ImageColorPickerWidget&) = delete;

	ImageColorPickerWidget& operator=(ImageColorPickerWidget&&) = delete;
	ImageColorPickerWidget& operator=(const ImageColorPickerWidget&) = delete;

	bool selectColor(const QString &image);

signals:
	void colorSelected(QColor color);

protected:
	void resizeEvent(QResizeEvent* event) override;

private slots:
	void onMouseMove(QMouseEvent* event);
	void onMouseRelease(QMouseEvent* event);

private:
	Ui::ImageColorPickerWidgetClass* mUi;
	QColor mPreviewColor;
	QColor mSelectedColor;
	QImage mImage;
	QPixmap mPreviewIcon;
	double mScaleX, mScaleY;
};
/*-----------------------------------------------------------------------------------------------------------*/
