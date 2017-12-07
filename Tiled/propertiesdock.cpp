/*-----------------------------------------------------------------------------------------------------------*/
#include <QContextMenuEvent>
#include <QSignalMapper>
#include <QMenu>
#include <array>
#include <QToolBar>
#include <QInputDialog>
#include <QVBoxLayout>
#include "object.h"
#include "document.h"
#include "propertiesdock.h"
#include "propertybrowser.h"
#include "changeproperties.h"
#include "addpropertydialog.h"
#include "groupcommand.h"
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
PropertiesDock::PropertiesDock(QWidget* parent) :
	QDockWidget(parent),
	mDocument(nullptr),
	mPropertyBrowser(new PropertyBrowser(this)),
	mToolBar(new QToolBar),
	mActionAddProperty(nullptr),
	mActionRemoveProperty(nullptr),
	mActionRenameProperty(nullptr)
{
	setObjectName(QLatin1String("Properties"));
	
	auto widget = new QWidget(this);
	auto layout = new QVBoxLayout(widget);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(mPropertyBrowser);
	layout->addWidget(mToolBar);
	widget->setLayout(layout);

	buildToolBar();
	setWidget(widget);

	updateActions();
	retranslateUi();

	connect(mPropertyBrowser, &PropertyBrowser::selectedItemsChanged, this, &PropertiesDock::updateActions);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::setDocument(Document* document)
{
	if (mDocument == document) return;

	if(mDocument)
	{
		mDocument->disconnect(this);
	}

	mDocument = document;

	mPropertyBrowser->setDocument(mDocument);

	if(mDocument)
	{
		connect(mDocument, &Document::currentObjectChanged, this, &PropertiesDock::currentObjectChanged);

		connect(mDocument, &Document::propertyAdded, this, &PropertiesDock::updateActions);
		connect(mDocument, &Document::propertyRemoved, this, &PropertiesDock::updateActions);
	}

	currentObjectChanged((mDocument) ? mDocument->currentObject() : nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::contextMenuEvent(QContextMenuEvent* event)
{
	auto object = mDocument->currentObject();
	if (!object) return;

	QMenu contextMenu;
	QSignalMapper signalMapper;

	auto convertTo = contextMenu.addMenu(tr("Convert To"));
	auto rename = contextMenu.addAction(tr("Rename..."));
	auto remove = contextMenu.addAction(tr("Remove..."));
	
	rename->setIcon(QIcon(QLatin1String(":/MapEditor/images/16x16/rename.png")));
	remove->setIcon(QIcon(QLatin1String(":/MapEditor/images/16x16/remove.png")));

	auto items = mPropertyBrowser->selectedItems();
	auto allCustomProperties = !items.isEmpty() && mPropertyBrowser->allCustomPropertyItem(items);

	convertTo->menuAction()->setEnabled(allCustomProperties);
	rename->setEnabled(allCustomProperties && items.count() == 1);
	remove->setEnabled(allCustomProperties);

	if(convertTo->menuAction()->isEnabled())
	{
		QStringList propertyNames;

		for (decltype(auto) item : items)
			propertyNames.append(item->property()->propertyName());

		const std::array<int, 6> types =
		{
			QVariant::Bool,
			QVariant::Color,
			QVariant::Double,
			QVariant::Url,
			QVariant::Int,
			QVariant::String
		};

		for(decltype(auto) type : types)
		{
			auto allCanConvert = true;
			auto someDifferentType = false;

			for(decltype(auto) propertyName : propertyNames)
			{
				auto propertyValue = object->property(propertyName);

				if (propertyValue.userType() != type)
					someDifferentType = true;

				if (!propertyValue.convert(type))
					allCanConvert = false;
			}

			if(someDifferentType && allCanConvert)
			{
				auto action = convertTo->addAction(typeToName(type));

				connect(action, &QAction::triggered, &signalMapper,
					static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));

				signalMapper.setMapping(action, type);
			}
		}
	}

	connect(rename, &QAction::triggered, this, &PropertiesDock::renameProperty);
	connect(remove, &QAction::triggered, this, &PropertiesDock::removeProperties);
	connect(&signalMapper, static_cast<void(QSignalMapper::*)(int)>(&QSignalMapper::mapped),
		this, &PropertiesDock::convertProperty);

	contextMenu.exec(event->globalPos());
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::changeEvent(QEvent* event)
{
	QDockWidget::changeEvent(event);

	switch (event->type())
	{
	case QEvent::LanguageChange:
		retranslateUi();
		break;
	default:
		break;
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::currentObjectChanged(Object* object)
{
	mPropertyBrowser->setObject(object);
	mPropertyBrowser->setEnabled(object);
	mActionAddProperty->setEnabled(object);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::updateActions()
{
	auto items = mPropertyBrowser->selectedItems();
	auto allCustomProperties = !items.isEmpty() && mPropertyBrowser->allCustomPropertyItem(items);

	mActionRemoveProperty->setEnabled(allCustomProperties);
	mActionRenameProperty->setEnabled(allCustomProperties && items.size() == 1);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::addProperty()
{
	AddPropertyDialog dialog(mPropertyBrowser);
	if (dialog.exec() != AddPropertyDialog::Accepted) return;

	auto object = mDocument->currentObject();
	if (!object) return;
		
	if(!object->hasProperty(dialog.propertyName()))
	{
		auto undoStack = mDocument->undoStack();
		undoStack->push(new SetProperty(mDocument, object,
			dialog.propertyName(), dialog.propertyValue()));
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::removeProperties()
{
	auto object = mDocument->currentObject();
	if (!object) return;

	auto items = mPropertyBrowser->selectedItems();
	if (items.isEmpty() || !mPropertyBrowser->allCustomPropertyItem(items)) return;

	auto undoStack = mDocument->undoStack();

	QList<Command*> commands;
	for (decltype(auto) item : items)
	{
		commands.append(new RemoveProperty(mDocument,
			mDocument->currentObject(),
			item->property()->propertyName()));
	}
		
	undoStack->push(new GroupCommand(
		tr("Remove Property/Properties", nullptr, items.size()),
		std::move(commands)));
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::renameProperty()
{
	auto items = mPropertyBrowser->selectedItems();
	if (items.count() != 1) return;

	auto item = items.first();
	if (!mPropertyBrowser->isCustomPropertyItem(item)) return;

	bool ok;
	QInputDialog inputDialog;

	inputDialog.setWindowFlags(inputDialog.windowFlags() & (~Qt::WindowContextHelpButtonHint));
	auto newName = QInputDialog::getText(this, tr("Rename Property"), tr("Name:"), 
		QLineEdit::Normal, item->property()->propertyName(), &ok, inputDialog.windowFlags());

	if (ok && !newName.isEmpty())
	{
		mDocument->undoStack()->push(new RenameProperty(mDocument, mDocument->currentObject(),
			item->property()->propertyName(), newName));
	}
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::convertProperty(int type)
{
	auto undoStack = mDocument->undoStack();
	auto object = mDocument->currentObject();
	auto items = mPropertyBrowser->selectedItems();
	
	QList<Command*> commands;
	for (decltype(auto) item : items)
	{
		auto propertyName = item->property()->propertyName();
		auto propertyValue = object->property(propertyName);

		propertyValue.convert(type);

		commands.append(new SetProperty(mDocument, object, propertyName, propertyValue));
	}

	undoStack->push(new GroupCommand(
		tr("Convert Property/Properties", nullptr, items.size()),
		std::move(commands)));
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::buildToolBar()
{
	Q_ASSERT(mToolBar);
	Q_ASSERT(!mActionAddProperty);
	Q_ASSERT(!mActionRemoveProperty);
	Q_ASSERT(!mActionRenameProperty);

	mActionAddProperty = new QAction(this);
	mActionRemoveProperty = new QAction(this);
	mActionRenameProperty = new QAction(this);

	mActionAddProperty->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/add.png"), { QSize(16,16) }));
	mActionRemoveProperty->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/remove.png"), { QSize(16,16) }));
	mActionRenameProperty->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/rename.png"), { QSize(16,16) }));

	mActionRemoveProperty->setShortcut(QKeySequence::Delete);
	mActionRemoveProperty->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	addAction(mActionRemoveProperty);

	mToolBar->addActions({ mActionAddProperty, mActionRemoveProperty, mActionRenameProperty });
	mToolBar->setIconSize(iconSize(IconSize::Small));

	connect(mActionRenameProperty, &QAction::triggered, this, &PropertiesDock::renameProperty);
	connect(mActionRemoveProperty, &QAction::triggered, this, &PropertiesDock::removeProperties);
	connect(mActionAddProperty, &QAction::triggered, this, &PropertiesDock::addProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PropertiesDock::retranslateUi()
{
	setWindowTitle(tr("Properties"));
}
/*-----------------------------------------------------------------------------------------------------------*/
