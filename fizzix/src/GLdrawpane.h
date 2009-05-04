#ifndef GLDRAWPANE_H
#define GLDRAWPANE_H

#include <vector>
#include "databackend/drawableobject.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <libfizzix/gen_structs.h>
#include <libfizzix/quaternion.h>

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
		//Current rotation to perform each frame
		Quaternion currRot;
		//How fast to zoom in and out
		double zoomSpeed;
		//Current zoom
		double zoom;
		//Maximum zoom, and the size of the box
		double maxZoom;
		//Information about the window
		double height;
		double width;
		double fov;

		QPoint currPoint;
	protected:
		//Turn on the lights
		void initializeGL();
		//Render the scene.  Rotate the camera, draw the transparent box, and draw each object
		void paintGL();
		//Reset the width and height for projection purposes
		void resizeGL(int _width, int _height);
		void mouseMoveEvent(QMouseEvent * event);
		void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	public:
		//Create the GL panel
		GLDrawPane(QWidget * parent = 0, double _rotate = 1, double _zoom = 1, double _maxZoom = 100, double fieldOfView = 60);

		//Return the requested size of this widget.
		QSize sizeHint() const;
		
		static double sideToZoom;
};

#endif
