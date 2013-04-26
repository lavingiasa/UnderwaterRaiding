#include <QtGui/QApplication>
#include <QtGui>
#include "mainwindow.h"

/** @mainpage CSCI 102 PA #5
	@section purpose Purpose/Overview: This application is meant to be a game that will be used for me to show my programming skills in QT and cpp in general. It is meant to be a culmination of all we have done in the class. This game is an arcade like shooter where you have to defend the earth from the evil fish who are coming to ransack it. 
		1. Use timers to control the movement of 'things' and apparent speed with which a program executes.
		2. Implement several types of GUI user input classes for all user input.
		3. Understand how to create, and destroy, graphical objects dynamically.
		4. Practice how to show, or hide, Qt widgets to change what the user can see.
		5. Practice the handling of GUI-based events in Qt.

	@section requirments Requirments: 
		1. Make a design document that will model the game
		2. Impliment 5 "things" that move in different ways
		3. Have buttons work correctly and stuff like that
		4. Pause button, start button, quit button
		5. Make the game work as it is supposed to
		6. A full list of reqs. can be found here: https://github.com/usc-csci102-spring2013/programming_assignments/wiki/PA5-Grading-Notes

	@author Samir Lavingia

  
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;

    w->show();

    return a.exec();
}
