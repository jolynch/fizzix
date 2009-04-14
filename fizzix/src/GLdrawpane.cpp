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
	Quaternion posq = rot * Quaternion(0,0,0,1) * (rot.conjugate());
	vec3 pos(posq[1],posq[2],posq[3]);
	pos *= zoom;
	Quaternion upq = rot * Quaternion(0,0,1,0) * (rot.conjugate());
	vec3 up(upq[1],upq[2],upq[3]);
	gluLookAt(pos.x,pos.y,pos.z,0,0,0,up.x,up.y,up.z);
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
