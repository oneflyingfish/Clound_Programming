#include <QtWidgets/QApplication>
#include<QTranslator.h>
#include<QDebug>

#include "try1_NotePad.h"
#include "CommunicationClass.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	/*MyTabWidget m;
	m.show();*/

	try1_NotePad w;
	w.show();

	//CommunicationClass c;
	//c.show();

	return app.exec();
}
