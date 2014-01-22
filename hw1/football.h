//
//  OpenGL Triangle Widget
//

#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <QGLWidget>
#include <QString>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>

class Football : public QGLWidget
{
Q_OBJECT
//  Private data
private:
/*
    int  darth;     //  Texture
    int  theta;     //  Rotation angle
    bool texture;   //  Color/Texture toggle
*/
	int  theta;     //  Rotation angle

//  Public access to this widget
public:
/*
    Triangle(QWidget* parent=0);                      //  Constructor
    QSize sizeHint() const {return QSize(400,400);}   //  Default size of widget
*/
	Football(QWidget *parent = 0);
	QSize sizeHint() const {return QSize(400, 400);}
//  Communications with other widgets
public slots:
/*
    void setTheta(int angle);    //  Slot to set angle
    void setType(QString type);  //  Slot to set color/texture
*/
	
signals:
/*
    void message(QString text);  //  Signal for messages
*/
//  Need to reimplement these methods inhereted from QGLWidget
protected:
    void initializeGL();                   //  Initialize widget
    //void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
};

#endif
