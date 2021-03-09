#include <QApplication>
#include <locale.h>
#include "widget.h"


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	setlocale(LC_ALL, NULL);
	
	widget widget;
	widget.show();

	app.exec();
}
