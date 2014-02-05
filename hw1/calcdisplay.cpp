/* *******************************************************
 * Created By Ethan Kreloff January 21, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder and 
 * examples from qt-project.org.
 * *******************************************************
 * Displays numbers as a qlcdnumber
 * *******************************************************
 * calcdisplay.cpp
 * ******************************************************/

#include "calcdisplay.h"

//
//  Constructor
//
CalcDisplay::CalcDisplay(QWidget* parent)
{
	(void) parent; //unused
	operation = false;
	
	this->setSegmentStyle(QLCDNumber::Flat);
	this->setDigitCount(99);
}


// 
// Slot Functions
//
void CalcDisplay::button1Click()
{	
	if(intValue() < MAXNUM){
		display(value()*10 + 1);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::button2Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 2);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::button3Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 3);
	}
	emit currentValue(intValue(), operation);
}
	
void CalcDisplay::button4Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 4);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::button5Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 5);
	}
	emit currentValue(intValue(), operation);
}
	
void CalcDisplay::button6Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 6);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::button7Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 7);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::button8Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 8);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::button9Click()
{
	if(intValue() < MAXNUM){
		display(value()*10 + 9);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::button0Click()
{
	if(intValue() < MAXNUM){
		display(value()*10);
	}
	emit currentValue(intValue(), operation);
}

void CalcDisplay::buttonPlusClick()
{	
	if(!operation){
		operation = true;
		opType = '+';
		previousVal = value();
		display(0);
	}
	
}

void CalcDisplay::buttonMinusClick()
{
	if(!operation){
		operation = true;
		opType = '-';
		previousVal = value();
		display(0);
	}
}

void CalcDisplay::buttonTimesClick()
{
	if(!operation){
		operation = true;
		opType = '*';
		previousVal = value();
		display(0);
	}
}

void CalcDisplay::buttonDivideClick()
{
	if(!operation){
		operation = true;
		opType = '/';
		previousVal = value();
		display(0);
	}
}

void CalcDisplay::buttonEqualsClick()
{	
	if(operation){
		switch(opType){
			case '+':
				display(previousVal + value());
				break;
			case '-':
				display(previousVal - value());
				break;
			case '*':
				display(previousVal * value());
				break;
			case '/':
				display(previousVal / value());
				break;
		}
		emit currentValue(intValue(), 2);
		
	}
}

void CalcDisplay::buttonClearClick()
{
	operation = false;
	previousVal = 0;
	display(0);
	emit currentValue(0, 0);
	emit currentValue(0, 1);
	emit currentValue(0, 2);
}

void CalcDisplay::buttonDeleteClick()
{	
	int newNum = (intValue() - (intValue()%10))/10;
	display(newNum);
	emit currentValue(intValue(), operation);
	
}

void CalcDisplay::buttonBinClick()
{
	this->setBinMode();
}
void CalcDisplay::buttonDecClick()
{
	this->setDecMode();
}
void CalcDisplay::buttonHexClick()
{
	this->setHexMode();
}
void CalcDisplay::buttonOctClick()
{
	setOctMode();
}


