/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QDockWidget>
/*-----------------------------------------------------------------------------------------------------------*/
class Document;
class PropertyBrowser;
class Object;
class QToolBar;
/*-----------------------------------------------------------------------------------------------------------*/
class PropertiesDock final : public QDockWidget
{
	Q_OBJECT

public:
	explicit PropertiesDock(QWidget* parent = nullptr);
	~PropertiesDock() override = default;

	PropertiesDock(PropertiesDock&&) = delete;
	PropertiesDock(const PropertiesDock&) = delete;

	PropertiesDock& operator=(PropertiesDock&&) = delete;
	PropertiesDock& operator=(const PropertiesDock&) = delete;

	void setDocument(Document* document);

protected:
	void contextMenuEvent(QContextMenuEvent* event) override;
	void changeEvent(QEvent* event) override;

private slots:
	void currentObjectChanged(Object* object);
	void updateActions();

	void addProperty();
	void removeProperties();
	void renameProperty();

	void convertProperty(int type);

private:
	void buildToolBar();
	void retranslateUi();

private:
	Document* mDocument;
	PropertyBrowser* mPropertyBrowser;

	QToolBar* mToolBar;
	QAction *mActionAddProperty;
	QAction *mActionRemoveProperty;
	QAction *mActionRenameProperty;
};
/*-----------------------------------------------------------------------------------------------------------*/
