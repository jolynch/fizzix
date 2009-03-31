#ifndef GLDRAWPANE_H
#define GLDRAWPANE_H

#include <vector>
#include <QGLWidget>
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
		void zoom(double amount);
		//Move and rotate the camera corresponding to the current quaternion.  Requires a current gl context.
		void moveCamera();
		//Draw any object composed of a triangle mesh.  The triangles must store unit normals.
		void drawObject(const std::vector<Triangle> & mesh);
		//Given a box with faces (x,y,z) = (+r,-r) which contains objects, return which faces are behind any drawn objects, and which are in front of them as bits in an integer.
		//  @return:  A 6 bit integer with bits (from least to most significant):
		//    x = +r
		//    x = -r
		//    y = +r
		//    y = -r
		//    z = +r
		//    z = -r
		int boxFrontFaces(double r, double x, double y, double z) const;
		
		//How fast to rotate
		const double rotSpeed;
		//Current orientation
		Quaternion rot;

		//How fast to zoom in and out
		const double zoomSpeed;
		//Current zoom
		double zoom;

		//Information about the window
		double height;
		double width;
		const double fov;

	protected:
		//Turn on the lights
		void initializeGL();
		//Render the scene.  Rotate the camera, draw the transparent box, and draw each object
		void paintGL();
		//Reset the width and height for projection purposes
		void resizeGL(int width, int height);

	public:
		//Create the GL panel
		GLDrawPane(QWidget * parent = 0);

		//Return the requested size of this widget.
		QSize sizeHint() const;
}

#endif
