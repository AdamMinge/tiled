/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QWidget>
#include "tiledqtutility_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class QLineEdit;
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDQTUTILITY_EXPORT FileEdit final : public QWidget
{
	Q_OBJECT

public:
	explicit FileEdit(QWidget* parent = nullptr);
	~FileEdit() override = default;

	FileEdit(FileEdit&&) = delete;
	FileEdit(const FileEdit&) = delete;

	FileEdit& operator=(FileEdit&&) = delete;
	FileEdit& operator=(const FileEdit&) = delete;

	void setFileUrl(const QUrl& url);
	QUrl fileUrl() const;

	void setFilter(const QString& filter);
	QString filter() const;

signals:
	void fileUrlChanged(const QUrl& url);

protected:
	void focusInEvent(QFocusEvent *event) override;
	void focusOutEvent(QFocusEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

private slots:
	void validate();
	void textEdited();
	void buttonClicked();
	
private:
	QLineEdit* mLineEdit;
	QString mFilter;
	QColor mOkTextColor;
	QColor mErrorTextColor;
};
/*-----------------------------------------------------------------------------------------------------------*/
