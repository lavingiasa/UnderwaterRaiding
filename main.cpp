#include <QtGui/QApplication>
#include "mainwindow.h"

/** @mainpage CSCI 102 PA #5
	@section purpose Purpose/Overview

 
	@section requirments Requirments

  
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
