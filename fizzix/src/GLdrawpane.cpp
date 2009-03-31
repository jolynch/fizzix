#ifndef GLDRAWPANE_CPP
#define GLDRAWPANE_CPP

#include "GLdrawpane.h"

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
    Quaternion posq = rot * Quaternion(0,0,0,1) * (rot.conjugate);
	vec3 pos(posq[1],posq[2],posq[3];
	Quaternion upq = rot * Quaternion(0,0,1,0) * (rot.conjugate);
	vec3 up(upq[1],upq[2],upq[3]);
	vec3 left = up.cross(pos);
	vec3 comb = up*upAmt + left*leftAmt;

}
