//
//  Main Widget
//

#include <QtGui>
#include "main.h"
#include "football.h"


//
//  Constructor for Main widget
//
Main::Main()
{
   //  Set window title
   setWindowTitle(tr("Homework 1 - Ethan Kreloff"));

   
   
   QSlider *verticalSlider, *horizontalSlider;
   verticalSlider = new QSlider(Qt::Vertical);
   horizontalSlider = new QSlider(Qt::Horizontal);
   
   Football *football = new Football;
   
   QBoxLayout *layout = new QBoxLayout(QBoxLayout::RightToLeft);
   layout->addWidget(verticalSlider);
   layout->addWidget(football);
   layout->addWidget(horizontalSlider);
   setLayout(layout);
   /*//  Create new Triangle widget
   Triangle* triangle = new Triangle;

   //  Create slider and set range to 0-360 (degrees)
   QSlider* slider = new QSlider(Qt::Vertical);
   slider->setRange(0,360);
   

   //  Create label to show angle
   QLabel* label = new QLabel;
   
   //  Eye candy - set tick interval for display
   slider->setTickInterval(30);
   slider->setTickPosition(QSlider::TicksBelow);

   //  Create toggle
   QComboBox* combo = new QComboBox();
   combo->addItem("Pastel Colors");
   combo->addItem("Texture");

   //  Set layout of child widgets
   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(combo);
   layout->addWidget(slider);
   layout->addWidget(triangle);
   layout->addWidget(label);
   setLayout(layout);

   //  Connect valueChanged() signal of slider to setTheta slot of triangle
   connect(slider, SIGNAL(valueChanged(int)) , triangle , SLOT(setTheta(int)));
   //  Connect toggled() signal of pushbutton to setTexture slot of triangle
   connect(combo, SIGNAL(currentIndexChanged(QString)) , triangle , SLOT(setType(QString)));
   //  Connect message() signal of triangle to setText slot of label
   connect(triangle, SIGNAL(message(QString)) , label , SLOT(setText(QString)));*/
}
