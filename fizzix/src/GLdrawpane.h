/************************************************************************************************
This file is a part of libfizzix backend to the Fizzix project.
The website for this project is http://code.google.com/p/fizzix .
Copyright (C) 2009
	Joseph Lynch
	Anton Frolenkov
	Purnima Balakrishnan
	Daniel Stiles
	Eric Van Albert

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
************************************************************************************************/
#ifndef GLDRAWPANE_H
#define GLDRAWPANE_H

#include <vector>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QList>
#include <QDebug>
#include <libfizzix/gen_structs.h>
#include <libfizzix/quaternion.h>

#include "databackend/drawableobject.h"
#include "databackend/databackend.h"

enum View {XY,YZ,ZX,ISOMETRIC};

// GLDrawPane is a component that will draw the actual simulation.
class GLDrawPane: public QGLWidget
{ Q_OBJECT
	private:
		DataBackend * db;
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
		GLDrawPane(DataBackend * _db,QWidget * parent = 0, double _rotate = .1, double _zoom = .01, double _minZoom = .1, double _maxZoom = 100, double fieldOfView = 13);

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
