//
//  OpenGL Triangle Widget
//

#ifndef CACLDISPLAY_H
#define CALCDISPLAY_H

#include <QGLWidget>
#include <QString>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLCDNumber>

class CalcDisplay : public QLCDNumber
{
Q_OBJECT
//  Private data
private:
/*
    int  darth;     //  Texture
    int  theta;     //  Rotation angle
    bool texture;   //  Color/Texture toggle
*/
	// How to tell if the button click is the first or after another one
	bool firstButton;
	bool secondButton;

//  Public access to this widget
public:
/*
    Triangle(QWidget* parent=0);                      //  Constructor
    QSize sizeHint() const {return QSize(64,64);}   //  Default size of widget
*/
	CalcDisplay(QWidget *parent = 0);
	//QSize sizeHint() const {return QSize(64, 64);}
//  Communications with other widgets
public slots:
/*
    void setTheta(int angle);    //  Slot to set angle
    void setType(QString type);  //  Slot to set color/texture
*/

	//void setPan(int distance);
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
	
signals:
/*
    void message(QString text);  //  Signal for messages
*/
//  Need to reimplement these methods inhereted from QGLWidget
protected:
	/*
    void initializeGL();                   //  Initialize widget
    void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
    */
};

#endif
