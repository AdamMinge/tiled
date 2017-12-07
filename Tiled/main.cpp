/*-----------------------------------------------------------------------------------------------------------*/
#include "singleapplication.h"
#include "mainwindow.h"
/*-----------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	SingleApplication::setOrganizationName("Mig23");
	SingleApplication::setApplicationName("TiledMapEditor");

	SingleApplication a(argc, argv);
	MainWindow w;

	QObject::connect(&a, &SingleApplication::instanceStarted, [&w]() {
		w.raise();
		w.activateWindow();
	});

	w.show();

	return a.exec();
}
/*-----------------------------------------------------------------------------------------------------------*/
