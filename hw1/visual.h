/* *******************************************************
 * Created By Ethan Kreloff January 21, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * OpenGL display for visual calculation. 
 * *******************************************************
 * visual.h
 * ******************************************************/
 
 #ifndef VISUAL_H
 #define VISUAL_H
 
 #include <QGLWidget>
class Visual : public QGLWidget
{
	Q_OBJECT
	private:
		double firstNumber;
		
	public:
		Visual(QWidget* parent=0);                      //  Constructor
		QSize sizeHint() const {return QSize(1000,1000);}   //  Default size of widget

	public slots:
		void setNumber(double number);
	signals:

	protected:
		void initializeGL();                   //  Initialize widget
		void resizeGL(int width, int height);  //  Resize widget
		void paintGL();                        //  Draw widget
};

#endif
