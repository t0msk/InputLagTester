/*******************************************************
* Name: InputLagTester								   *
* Create date: 29.12.2018                              *
* Author:  Tomáš "tomsk" Sabo                          *
* Purpose:  Test Input Lag / reflexes      			   *
* Usage: Runs the program, click START and click big   *
* button, when red.							  		   *
*******************************************************/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
