#ifndef GLDRAWPANE_CPP
#define GLDRAWPANE_CPP

#include "GLdrawpane.h"

#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>

GLDrawPane:GLDrawPane(QWidget * parent = 0, rotate = 1, zoom = 1, fieldOfView = 60) : QGLWidget(parent)
{
	rotSpeed = rotate;
	zoomSpeed = zoom;
	fov = fieldOfView;
	rot = Quaternion();
	zoom = 1;
	height = 0;
	width = 0;
}

QSize GLDrawPane::sizeHint() const
{
	return QSize(700,800);
}

void GLDrawPane::rotate(double upAmt, double leftAmt)
{
	Quaternion posq = rot * Quaternion(0,0,0,1) * (rot.conjugate());
	vec3 pos(posq[1],posq[2],posq[3]);
	Quaternion upq = rot * Quaternion(0,0,1,0) * (rot.conjugate());
	vec3 up(upq[1],upq[2],upq[3]);
	vec3 left = up.cross(pos);
	vec3 comb = up*upAmt + left*leftAmt;
	double mag = comb.mag()*rotSpeed;
	vec3 axis = comb.cross(pos);
	vec3 vecPart = axis*sin(mag);
	Quaternion toRot(cos(mag),vecPart.x,vecPart.y,vecPart.z);
	rot *= toRot;
}

void GLDrawPane::zoom(double amount)
{
	zoom += amount * zoomSpeed;
}

void GLDrawPane::moveCamera()
{
	double w = rot[0];
	double x = rot[1];
	double y = rot[2];
	double z = rot[3];
	GLfloat rotMatrix[] = {1-2*y*y-2*z*z,2*x*y+2*w*z,2*x*z-2*w*y,0,\
						 2*x*y-2*w*z,1-2*x*x-2*z*z,2*y*z+2*w*x,0,\
						 2*x*z+2*y*w,2*y*z+2*w*x,1-2*x*x-2*y*y,0,\
						 0,0,0,1};
	glMultMatrixf(rotMatrix);
}

static int GLDrawPane::boxFrontFaces(double r, double x, double y, double z)
{
	int tot = (x > r);
	tot += ((x < -r) << 1);
	tot += ((y > r) << 2);
	tot += ((y < -r) << 3);
	tot += ((z > r) << 4);
	tot += ((z < -r) << 5);
	return tot; 
}

#endif
