#ifndef GLDRAWPANE_CPP
#define GLDRAWPANE_CPP

#include "GLdrawpane.h"

#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

GLDrawPane:GLDrawPane(QWidget * parent = 0, _rotate = 1, _zoom = 1, _maxZoom = 100, fieldOfView = 60) : QGLWidget(parent)
{
	rotSpeed = _rotate;
	zoomSpeed = _zoom;
	fov = fieldOfView;
	rot = Quaternion();
	zoom = 1;
	maxZoom = _maxZoom;
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

vec3 GLDrawPane::moveCamera()
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
	return pos;
}

void drawObject(const DrawableObject & obj)
{
	int properties = obj.getProperties();
	if (!(properties & 1))
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		const vector<triangle> & mesh = obj.getVertices();
		const vec3 & colors = obj.getColor();
		const vec3 & pos = obj.getPos();
		glColor4d(colors[0],colors[1],colors[2],1.0);
		glTranslated(pos[0],pos[1],pos[2]);
		if (properties & 2)
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0;i < mesh.size();i++)
			{
				const triangle & currT = mesh[i];
				for (int v = 0;v < 3;v++)
				{
					const vertex & currV = currT[v];
					vec3 currNormal;
					double num;
					for (num = 0;num < currV.triangles.size();num++)
					{
						currNormal += currV(num)->unit_normal;
					}
					currNormal/=currNormal.mag();
					glNormal3d(currNormal[0],currNormal[1],currNormal[2]);
					glVertex3d(currV[0],currV[1],currV[2]);
				}
			}
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			for(int i = 0;i < mesh.size();i++)
			{
				const triangle & currT = mesh[i];
				const vec3 & n = currT.unit_normal;
				glNormal3d(n[0],n[1],n[2]);
				for (int v = 0;v < 3;v++)
				{
					const vertex & currV = currT[v];
					glVertex3d(currV[0],currV[1],currV[2]);
				}
			}
			glEnd();
		}
		glPopMatrix();
	}
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

void GLDrawPane::initializeGL()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void GLDrawPane::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,width/height,.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vec3 pos = moveCamera();
	glEnable(GL_BLEND);
	drawBox((~(GLDrawPanel.boxFrontFaces(maxZoom,pos[0],pos[1],pos[2])))&63,.25);
	glDisable(GL_BLEND);
	const vector<DrawableObject> & objs = panel->getObjs();
	for (int i = 0;i < objs.size();i++) {
		drawObject(obs[i]);
	}
	glEnable(GL_BLEND);
	drawBox(GLDrawPanel.boxFrontFaces(maxZoom,pos[0],pos[1],pos[2]),.25);
	glDisable(GL_BLEND);
}

void GLDrawPane::resizeGL(int _width,int _height)
{
	height = _height;
	width = _width;
}

#endif
