/* *******************************************************
 * Created By Ethan Kreloff January 21, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
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
	operation = false;
	
	this->setSegmentStyle(QLCDNumber::Flat);
	this->setDigitCount(15);
}


// 
// Slot Functions
//
void CalcDisplay::button1Click()
{	
	this->display(this->value()*10 + 1);
}

void CalcDisplay::button2Click()
{
	this->display(this->value()*10 + 2);
}

void CalcDisplay::button3Click()
{
	this->display(this->value()*10 + 3);
}
	
void CalcDisplay::button4Click()
{
	this->display(this->value()*10 + 4);
}

void CalcDisplay::button5Click()
{
	this->display(this->value()*10 + 5);
}
	
void CalcDisplay::button6Click()
{
	this->display(this->value()*10 + 6);
}

void CalcDisplay::button7Click()
{
	this->display(this->value()*10 + 7);
}

void CalcDisplay::button8Click()
{
	this->display(this->value()*10 + 8);
}

void CalcDisplay::button9Click()
{
	this->display(this->value()*10 + 9);
}

void CalcDisplay::button0Click()
{
	this->display(this->value()*10);
}

void CalcDisplay::buttonPlusClick()
{	
	if(!operation){
		operation = true;
		opType = '+';
		previousVal = this->value();
		this->display(0);
	}
	
}

void CalcDisplay::buttonMinusClick()
{
	if(!operation){
		operation = true;
		opType = '-';
		previousVal = this->value();
		this->display(0);
	}
}

void CalcDisplay::buttonTimesClick()
{
	if(!operation){
		operation = true;
		opType = '*';
		previousVal = this->value();
		this->display(0);
	}
}

void CalcDisplay::buttonDivideClick()
{
	if(!operation){
		operation = true;
		opType = '/';
		previousVal = this->value();
		this->display(0);
	}
}

void CalcDisplay::buttonEqualsClick()
{	
	if(operation){
		switch(opType){
			case '+':
				this->display(previousVal + this->value());
				break;
			case '-':
				this->display(previousVal - this->value());
				break;
			case '*':
				this->display(previousVal * this->value());
				break;
			case '/':
				this->display(previousVal / this->value());
				break;
		}
		operation = false;
		
	}
}

void CalcDisplay::buttonClearClick()
{
	operation = false;
	previousVal = 0;
	this->display(0);
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

//Signal Functions
/*
double CalcDisplay::currentValue(double number)
{
	return this->value();
}
*/
