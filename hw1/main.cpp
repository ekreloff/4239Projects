/* *******************************************************
 * Created By Ethan Kreloff January 21, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder and 
 * examples from qt-project.org.
 * *******************************************************
 * Where all the calculator pieces are assembeled.
 * *******************************************************
 * main.cpp
 * ******************************************************/

#include "main.h"
#include "calcdisplay.h"
#include "visual.h"


//
//  Constructor for Main widget
//
Main::Main()
{
  
   //  Set window title
   setWindowTitle(tr("Homework 1 - Ethan Kreloff"));

   CalcDisplay *resultDisplay = new CalcDisplay();
   Visual *calcVisual = new Visual();
   
   // Text inside calculator butons
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
   QString stringDelete = "Delete";
   QString stringDec = "Decimal";
   QString stringBin = "Binary";
   QString stringHex = "Hexadecimal";
   QString stringOct = "Octal";
   
   
   
   // Calculator Buttons
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
   QPushButton *buttonDelete = new QPushButton(stringDelete);
   QPushButton *buttonDec = new QPushButton(stringDec);
   QPushButton *buttonHex = new QPushButton(stringHex);
   QPushButton *buttonBin = new QPushButton(stringBin);
   QPushButton *buttonOct = new QPushButton(stringOct);
   
   
   // Layout
   QGridLayout *gridLayout = new QGridLayout();
   QBoxLayout *topLayout = new QBoxLayout(QBoxLayout::TopToBottom);
   topLayout->addWidget(resultDisplay);
   topLayout->addWidget(calcVisual);
   gridLayout->addWidget(button1,1,0);
   gridLayout->addWidget(button2,1,1);
   gridLayout->addWidget(button3,1,2);
   gridLayout->addWidget(button4,2,0);
   gridLayout->addWidget(button5,2,1);
   gridLayout->addWidget(button6,2,2);
   gridLayout->addWidget(button7,3,0);
   gridLayout->addWidget(button8,3,1);
   gridLayout->addWidget(button9,3,2);
   gridLayout->addWidget(button0,4,1);
   gridLayout->addWidget(buttonPlus,1,3);
   gridLayout->addWidget(buttonMinus,2,3);
   gridLayout->addWidget(buttonTimes,3,3);
   gridLayout->addWidget(buttonDivide,4,3);
   gridLayout->addWidget(buttonEquals,5,3);
   gridLayout->addWidget(buttonClear,5,0);
   gridLayout->addWidget(buttonDelete,4,0);
   gridLayout->addWidget(buttonDec,6,0);
   gridLayout->addWidget(buttonHex,6,1);
   gridLayout->addWidget(buttonBin,6,2);
   gridLayout->addWidget(buttonOct,6,3);	
   topLayout->addLayout(gridLayout);
   setLayout(topLayout);
   
   // Button click calls
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
   connect(buttonDelete, SIGNAL(clicked()) , resultDisplay , SLOT(buttonDeleteClick()));
   connect(buttonDec, SIGNAL(clicked()) , resultDisplay , SLOT(buttonDecClick()));
   connect(buttonHex, SIGNAL(clicked()) , resultDisplay , SLOT(buttonHexClick()));
   connect(buttonBin, SIGNAL(clicked()) , resultDisplay , SLOT(buttonBinClick()));
   connect(buttonOct, SIGNAL(clicked()) , resultDisplay , SLOT(buttonOctClick()));
   
   connect(resultDisplay, SIGNAL(currentValue(int, int)), calcVisual, SLOT(setNumber(int, int)));
   
   

}
