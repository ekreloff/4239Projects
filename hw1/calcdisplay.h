//
//  Created By Ethan Kreloff January 21st, 2014
//

//
//  Calculator Display widget
//

#ifndef CACLDISPLAY_H
#define CALCDISPLAY_H

#include <QLCDNumber>

class CalcDisplay : public QLCDNumber
{
Q_OBJECT
//  Private data
private:

	// How to tell if the button click is the first or after another one
	bool operation;
	
	// Type of operation
	char opType;
	
	// First operand
	double previousVal;

//  Public access to this widget
public:
	CalcDisplay(QWidget *parent = 0);
	
//  Communications with other widgets
public slots:
	void button1Click();
	void button2Click();
	void button3Click();
	void button4Click();
	void button5Click();
	void button6Click();
	void button7Click();
	void button8Click();
	void button9Click();
	void button0Click();
	void buttonPlusClick();
	void buttonMinusClick();
	void buttonTimesClick();
	void buttonDivideClick();
	void buttonEqualsClick();
	void buttonClearClick();
	void buttonBinClick();
	void buttonDecClick();
	void buttonHexClick();
	void buttonOctClick();
	
signals:
	double currentValue(double number);
protected:

};

#endif
