/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QMap>
/*-----------------------------------------------------------------------------------------------------------*/
class Document;
class QAction;
/*-----------------------------------------------------------------------------------------------------------*/
class ActionManager final
{
public:
	static ActionManager* instance();
	static void deleteInstance();

	ActionManager(ActionManager&&) = delete;
	ActionManager(const ActionManager&) = delete;

	ActionManager& operator=(ActionManager&&) = delete;
	ActionManager& operator=(const ActionManager&) = delete;

	void registerAction(QAction* action, const QString& id);
	void unregisterAction(const QString& id);

	QAction* action(const QString& id) const;

private:
	explicit ActionManager() = default;
	~ActionManager() = default;

private:
	static ActionManager* mInstance;
	QMap<QString, QAction*> mActions;
};
/*-----------------------------------------------------------------------------------------------------------*/