/*-----------------------------------------------------------------------------------------------------------*/
#include <QAction>
#include "actionmanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
ActionManager* ActionManager::mInstance = nullptr;
/*-----------------------------------------------------------------------------------------------------------*/
ActionManager* ActionManager::instance()
{
	if (!mInstance)
		mInstance = new ActionManager();

	Q_ASSERT(mInstance);
	return mInstance;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ActionManager::deleteInstance()
{
	Q_ASSERT(mInstance);
	delete mInstance;
	mInstance = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
void ActionManager::registerAction(QAction* action, const QString& id)
{
	Q_ASSERT(action);
	Q_ASSERT(!mActions.contains(id));

	mActions.insert(id, action);
}
/*-----------------------------------------------------------------------------------------------------------*/
void ActionManager::unregisterAction(const QString& id)
{
	Q_ASSERT(!id.isEmpty());
	Q_ASSERT(mActions.contains(id));

	mActions.remove(id);
}
/*-----------------------------------------------------------------------------------------------------------*/
QAction* ActionManager::action(const QString& id) const
{
	return mActions.value(id, nullptr);
}
/*-----------------------------------------------------------------------------------------------------------*/