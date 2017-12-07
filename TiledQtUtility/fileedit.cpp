/*-----------------------------------------------------------------------------------------------------------*/
#include <QLineEdit>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include "fileedit.h"
/*-----------------------------------------------------------------------------------------------------------*/
FileEdit::FileEdit(QWidget* parent) :
	QWidget(parent)
{
	auto layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	mLineEdit = new QLineEdit(this);
	mLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

	mOkTextColor = mLineEdit->palette().color(QPalette::Active, QPalette::Text);
	mErrorTextColor = Qt::red;

	auto button = new QToolButton(this);
	button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
	button->setFixedWidth(20);
	button->setText(QLatin1String("..."));
	layout->addWidget(mLineEdit);
	layout->addWidget(button);

	setFocusProxy(mLineEdit);
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_InputMethodEnabled);

	connect(mLineEdit, &QLineEdit::textChanged, this, &FileEdit::validate);
	connect(mLineEdit, &QLineEdit::textEdited, this, &FileEdit::textEdited);
	connect(button, &QAbstractButton::clicked, this, &FileEdit::buttonClicked);
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::setFileUrl(const QUrl& url)
{
	const auto path = url.toLocalFile();
	if (mLineEdit->text() != path)
		mLineEdit->setText(path);	
}
/*-----------------------------------------------------------------------------------------------------------*/
QUrl FileEdit::fileUrl() const
{
	const auto path = mLineEdit->text();
	return QUrl::fromLocalFile(path);
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::setFilter(const QString& filter)
{
	mFilter = filter;
}
/*-----------------------------------------------------------------------------------------------------------*/
QString FileEdit::filter() const
{
	return mFilter;
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::focusInEvent(QFocusEvent* event)
{
	mLineEdit->event(event);
	QWidget::focusInEvent(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::focusOutEvent(QFocusEvent* event)
{
	mLineEdit->event(event);
	QWidget::focusOutEvent(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::keyPressEvent(QKeyEvent* event)
{
	mLineEdit->event(event);
	QWidget::keyPressEvent(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::keyReleaseEvent(QKeyEvent* event)
{
	mLineEdit->event(event);
	QWidget::keyReleaseEvent(event);
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::validate()
{
	auto textColor = mOkTextColor;
	const auto url(fileUrl());

	if (!QFile::exists(url.toLocalFile())) 
		textColor = mErrorTextColor;
	
	auto palette = mLineEdit->palette();
	palette.setColor(QPalette::Active, QPalette::Text, textColor);
	mLineEdit->setPalette(palette);
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::textEdited()
{
	emit fileUrlChanged(fileUrl());
}
/*-----------------------------------------------------------------------------------------------------------*/
void FileEdit::buttonClicked()
{
	auto url = QFileDialog::getOpenFileUrl(this,
		tr("Choose a File"), fileUrl(), mFilter);

	if (url.isEmpty()) return;
	
	setFileUrl(url);
	emit fileUrlChanged(url);
}
/*-----------------------------------------------------------------------------------------------------------*/
