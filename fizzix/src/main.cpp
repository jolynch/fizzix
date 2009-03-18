#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <QCoreApplication>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QCoreApplication::setApplicationName("Fizzix");
	app.setWindowIcon(QIcon(":images/logomini"));
	MainWindow * mainwindow= new MainWindow();
	mainwindow->show();
	return app.exec();
}


#endif
