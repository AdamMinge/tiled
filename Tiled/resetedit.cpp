/*-----------------------------------------------------------------------------------------------------------*/
#include <QHBoxLayout>
#include <QToolButton>
#include "resetedit.h"
#include "utils.h"
/*-----------------------------------------------------------------------------------------------------------*/
ResetEdit::ResetEdit(QtProperty *property, QWidget *editor, QWidget *parent) :
	QWidget(parent),
	mProperty(property)
{
	auto layout = new QHBoxLayout(this);
	
	auto resetButton = new QToolButton(this);
	resetButton->setIcon(makeIcon(QLatin1String(":/Tiled/images/%1/edit-clear.png"), { QSize(16,16) }));
	resetButton->setIconSize(iconSize(IconSize::Small));
	resetButton->setAutoRaise(true);
	
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(editor);
	layout->addWidget(resetButton);

	connect(resetButton, &QToolButton::clicked, this, &ResetEdit::buttonClicked);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ResetEdit::buttonClicked()
{
	emit resetProperty(mProperty);
}
/*-----------------------------------------------------------------------------------------------------------*/