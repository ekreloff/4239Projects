//
//  Main Widget
//

#include <QtGui>
#include <QLCDNumber>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include "main.h"
#include "football.h"
#include "calcdisplay.h"


//
//  Constructor for Main widget
//
Main::Main()
{
   //  Set window title
   setWindowTitle(tr("Homework 1 - Ethan Kreloff"));

   CalcDisplay *resultDisplay = new CalcDisplay();
   
   QString string1 = "1";
   QString string2 = "2";
   QString string3 = "3";
   QString string4 = "4";
   QString string5 = "5";
   QString string6 = "6";
   QString string7 = "7";
   QString string8 = "8";
   QString string9 = "9";
   QString string0 = "0";
   QString stringClear = "Clear";
   QString stringPlus = "+";
   QString stringMinus = "-";
   QString stringTimes = "*";
   QString stringDivide = "/";
   QString stringEquals = "=";
   
   
   
   
   QPushButton *button1 = new QPushButton(string1);
   QPushButton *button2 = new QPushButton(string2);
   QPushButton *button3 = new QPushButton(string3);
   QPushButton *button4 = new QPushButton(string4);
   QPushButton *button5 = new QPushButton(string5);
   QPushButton *button6 = new QPushButton(string6);
   QPushButton *button7 = new QPushButton(string7);
   QPushButton *button8 = new QPushButton(string8);
   QPushButton *button9 = new QPushButton(string9);
   QPushButton *button0 = new QPushButton(string0);
   QPushButton *buttonPlus = new QPushButton(stringPlus);
   QPushButton *buttonMinus = new QPushButton(stringMinus);
   QPushButton *buttonTimes = new QPushButton(stringTimes);
   QPushButton *buttonDivide = new QPushButton(stringDivide);
   QPushButton *buttonEquals = new QPushButton(stringEquals);
   QPushButton *buttonClear = new QPushButton(stringClear);
   
   
   QGridLayout *topLayout = new QGridLayout();
   
   QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
   layout->addWidget(resultDisplay);
   layout->addWidget(button1);
   layout->addWidget(button2);
   layout->addWidget(button3);
   layout->addWidget(button4);
   layout->addWidget(button5);
   layout->addWidget(button6);
   layout->addWidget(button7);
   layout->addWidget(button8);
   layout->addWidget(button9);
   layout->addWidget(button0);
   layout->addWidget(buttonPlus);
   layout->addWidget(buttonMinus);
   layout->addWidget(buttonTimes);
   layout->addWidget(buttonDivide);
   layout->addWidget(buttonEquals);
   layout->addWidget(buttonClear);
   topLayout->addWidget(resultDisplay, 0,3, Qt::AlignRight);
   topLayout->addWidget(button1,1,0);
   topLayout->addWidget(button2,1,1);
   topLayout->addWidget(button3,1,2);
   topLayout->addWidget(button4,2,0);
   topLayout->addWidget(button5,2,1);
   topLayout->addWidget(button6,2,2);
   topLayout->addWidget(button7,3,0);
   topLayout->addWidget(button8,3,1);
   topLayout->addWidget(button9,3,2);
   topLayout->addWidget(button0,4,1);
   topLayout->addWidget(buttonPlus,1,3);
   topLayout->addWidget(buttonMinus,2,3);
   topLayout->addWidget(buttonTimes,3,3);
   topLayout->addWidget(buttonDivide,4,3);
   topLayout->addWidget(buttonEquals,5,3);
   topLayout->addWidget(buttonClear,5,1);
   //topLayout->addLayout(layout, 1, 4);
   setLayout(topLayout);
   
   connect(button1, SIGNAL(clicked()) , resultDisplay , SLOT(button1Click()));
   connect(button2, SIGNAL(clicked()) , resultDisplay , SLOT(button2Click()));
   connect(button3, SIGNAL(clicked()) , resultDisplay , SLOT(button3Click()));
   connect(button4, SIGNAL(clicked()) , resultDisplay , SLOT(button4Click()));
   connect(button5, SIGNAL(clicked()) , resultDisplay , SLOT(button5Click()));
   connect(button6, SIGNAL(clicked()) , resultDisplay , SLOT(button6Click()));
   connect(button7, SIGNAL(clicked()) , resultDisplay , SLOT(button7Click()));
   connect(button8, SIGNAL(clicked()) , resultDisplay , SLOT(button8Click()));
   connect(button9, SIGNAL(clicked()) , resultDisplay , SLOT(button9Click()));
   connect(button0, SIGNAL(clicked()) , resultDisplay , SLOT(button0Click()));
   connect(buttonPlus, SIGNAL(clicked()) , resultDisplay , SLOT(buttonPlusClick()));
   connect(buttonMinus, SIGNAL(clicked()) , resultDisplay , SLOT(buttonMinusClick()));
   connect(buttonTimes, SIGNAL(clicked()) , resultDisplay , SLOT(buttonTimesClick()));
   connect(buttonDivide, SIGNAL(clicked()) , resultDisplay , SLOT(buttonDivideClick()));
   connect(buttonEquals, SIGNAL(clicked()) , resultDisplay , SLOT(buttonEqualsClick()));
   connect(buttonClear, SIGNAL(clicked()) , resultDisplay , SLOT(buttonClearClick()));
   
   //  Connect valueChanged() signal of slider to setTheta slot of triangle
   //connect(verticalSlider, SIGNAL(valueChanged(int)) , football , SLOT(setPan(int)));
   
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
