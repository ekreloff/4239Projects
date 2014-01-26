/* *******************************************************
 * Created By Ethan Kreloff January 21, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * Main C++ function that calls the Qt wrapper.
 * *******************************************************
 * hw1.cpp
 * ******************************************************/
#include <QApplication>
#include "main.h"

int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show calculator 
   Main mainWidget;
   mainWidget.show();
   //  Main loop for application
   return app.exec();
}
