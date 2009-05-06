#ifndef GLDRAWPANE_H
#define GLDRAWPANE_H

#include <vector>
#include <QGLWidget>
#include <QMouseEvent>
#include <libfizzix/gen_structs.h>
#include <libfizzix/quaternion.h>

#include "databackend/drawableobject.h"

enum View {XY,YZ,ZX,ISOMETRIC};

class GLDrawPane: public QGLWidget
{ Q_OBJECT
	private:
		//Rotate the current quaternion
		//  @param up:  How much to rotate following the up vector.  Negative for down.
		//  @param left:  How much to rotate following the left vector.  Negative for right.
		void rotate(double upAmt, double leftAmt);
		//Zoom in by amount (out if amount is negative) scaled by zoomSpeed.
		void changeZoom(double amount);
		//Move and rotate the camera corresponding to the current quaternion.  Requires a current gl context.
		//  @return:  the current camera position
		vec3 moveCamera();
		//Draw any object composed of a triangle mesh.  The triangles must store unit normals.
		void drawObject(const DrawableObject & obj);
		void drawObject(const std::vector<triangle *> & mesh, const vec3 & color, const vec3 & pos, const Quaternion & q, bool hidden, bool smooth);
		//Given a box with faces (x,y,z) = (+r,-r) which contains objects, return which faces are behind any drawn objects, and which are in front of them as bits in an integer.
		//  @return:  A 6 bit integer with bits (from least to most significant):
		//    x = +r
		//    x = -r
		//    y = +r
		//    y = -r
		//    z = +r
		//    z = -r
		static int boxFrontFaces(double r, double x, double y, double z);
		//Draw the box with faces on as specified by boxFrontFaces()
		void drawBox(int faces,double alpha,bool front);
		//The Object panel to get the list of objects from
	   	//ObjectPanel * panel;
		//How fast to rotate
		double rotSpeed;
		//Current orientation
		Quaternion rot;
		//How fast to zoom in and out
		double zoomSpeed;
		//Current zoom
		double zoom;
		//Minimum zoom (must be > 0)
		double minZoom;
		//Maximum zoom, and determines the size of the box
		double maxZoom;
		//Information about the window
		double height;
		double width;
		//Field of view
		double fov;

		//Current point of the mouse (used for rotation
		QPoint currPoint;

		//Whether or not to show a small version of the axes
		bool showAxes;

	protected:
		//Turn on the lights
		void initializeGL();
		//Render the scene.  Rotate the camera, draw the transparent box, and draw each object
		void paintGL();
		//Reset the width and height for projection purposes
		void resizeGL(int _width, int _height);
		void mouseMoveEvent(QMouseEvent * event);
		void mousePressEvent(QMouseEvent * event);
   		void keyPressEvent(QKeyEvent * event);
		void wheelEvent(QWheelEvent * event);
	public:
		//Create the GL panel
		GLDrawPane(QWidget * parent = 0, double _rotate = .1, double _zoom = .01, double _minZoom = .1, double _maxZoom = 100, double fieldOfView = 13);

		//Return the requested size of this widget.
		QSize sizeHint() const;
		
		static double sideToZoom;
		static Quaternion lookatXY;
		static Quaternion lookatYZ;
		static Quaternion lookatZX;
		static Quaternion isometric;
	public slots:
		//Set the rotation matrix to one of the predefined types
		void setRotation(View v);
		//Set the zoom percentage (d = 100 is full size)
		void setZoomPercent(double d);
		//Show/Hide the coordinate axes
		void showCoordinateAxes(bool b);
};

#endif
