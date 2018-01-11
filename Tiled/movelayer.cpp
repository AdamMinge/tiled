/*-----------------------------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include "movelayer.h"
#include "grouplayer.h"
#include "mapdocument.h"
#include "layertreemodel.h"
/*-----------------------------------------------------------------------------------------------------------*/
MoveLayer::MoveLayer(MapDocument* mapDocument, Layer* layer, Move move, Command* parent) :
	Command(parent),
	mMapDocument(mapDocument),
	mLayer(layer),
	mMove(move)
{
	if (mMove == Move::Raise)
		setText(QCoreApplication::translate("Undo Commands", "Raise Layer"));
	else
		setText(QCoreApplication::translate("Undo Commands", "Lower Layer"));
}
/*-----------------------------------------------------------------------------------------------------------*/
void MoveLayer::undo()
{
	moveLayer();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MoveLayer::redo()
{
	moveLayer();
}
/*-----------------------------------------------------------------------------------------------------------*/
void MoveLayer::moveLayer()
{
	auto parent = mLayer->parent();
	auto siblings = mLayer->siblings();
	const auto index = mLayer->siblingIndex();

	auto insertionParent = parent;
	auto insertionIndex = mMove == Move::Lower ? index - 1 : index + 1;

	if (mMove == Move::Lower)
	{
		if (insertionIndex < 0) 
		{
			Q_ASSERT(insertionParent);
			insertionIndex = insertionParent->siblingIndex();
			insertionParent = insertionParent->parent();
		}
		else if (auto groupLayer = dynamic_cast<GroupLayer*>(siblings.at(insertionIndex)))
		{
			Q_ASSERT(groupLayer);
			insertionParent = groupLayer;
			insertionIndex = insertionParent->layerCount();
		}
	}
	else 
	{
		if (insertionIndex >= siblings.size()) 
		{
			Q_ASSERT(insertionParent);
			insertionIndex = insertionParent->siblingIndex() + 1;
			insertionParent = insertionParent->parent();
		}
		else if (auto groupLayer = dynamic_cast<GroupLayer*>(siblings.at(insertionIndex)))
		{
			Q_ASSERT(groupLayer);
			insertionParent = groupLayer;
			insertionIndex = 0;
		}
	}

	Q_ASSERT(parent);
	Q_ASSERT(insertionParent);

	auto layerModel = mMapDocument->layerModel();
	layerModel->takeLayer(parent, index);
	layerModel->addLayer(insertionParent, insertionIndex, mLayer);

	mMove = (mMove == Move::Lower) ? Move::Raise : Move::Lower;
}
/*-----------------------------------------------------------------------------------------------------------*/
