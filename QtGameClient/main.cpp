#include "QtGameClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGameClient w;
	w.show();
	return a.exec();
}
