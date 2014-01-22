//
//  Created By Ethan Kreloff January 21st, 2014
//

#include <QApplication>
#include "main.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show Hello widget
   Main mainWidget;
   mainWidget.show();
   //  Main loop for application
   return app.exec();
}
