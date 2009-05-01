#ifndef GLDRAWPANE_CPP
#define GLDRAWPANE_CPP

#include "GLdrawpane.h"

#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

GLDrawPane::GLDrawPane(QWidget * parent, double _rotate, double _zoom, double _maxZoom, double fieldOfView) : QGLWidget(parent)
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
	vec3 pos = rot.transformVec(vec3(0,0,1));
	vec3 up = rot.transformVec(vec3(0,1,0));
	vec3 left = up.cross(pos);
	vec3 comb = up*upAmt + left*leftAmt;
	double mag = comb.mag()*rotSpeed;
	vec3 axis = comb.cross(pos);
	vec3 vecPart = axis*sin(mag);
	Quaternion toRot(cos(mag),vecPart.x,vecPart.y,vecPart.z);
	rot *= toRot;
}

void GLDrawPane::changeZoom(double amount)
{
	zoom += amount * zoomSpeed;
}

vec3 GLDrawPane::moveCamera()
{
	vec3 pos = rot.transformVec(vec3(0,0,1));
	pos *= zoom;
	vec3 up = rot.transformVec(vec3(0,1,0));
	gluLookAt(pos.x,pos.y,pos.z,0,0,0,up.x,up.y,up.z);
	return pos;
}

void drawObject(const DrawableObject & obj)
{
	if (!obj.getProperty(HIDDEN))
	{
		int mode;
		glGetIntegerv(GL_MATRIX_MODE,&mode);
		glEnable(GL_CULL_FACE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		const vector<triangle> & mesh = obj.getVertices();
		const vec3 & colors = obj["color"].vector;
		const vec3 & pos = obj.getPos();
//		const Quaternion & q = obj.getQuaternion();
		glColor4d(colors[0],colors[1],colors[2],1.0);
		glTranslated(pos[0],pos[1],pos[2]);
		if (obj.getProperty(SMOOTH))
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0;i < (int)mesh.size();i++)
			{
				const triangle & currT = mesh[i];
				for (int v = 0;v < 3;v++)
				{
					const vertex & currV = currT[v];
					vec3 currNormal;
					double num;
					for (num = 0;num < (int)currV.triangles.size();num++)
					{
						currNormal += currV(num).unit_normal;
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
			for(int i = 0;i < (int)mesh.size();i++)
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
		glDisable(GL_CULL_FACE);
		glMatrixMode(mode);
	}
}

int GLDrawPane::boxFrontFaces(double r, double x, double y, double z)
{
	int tot = ((x > r) << 0);
	tot += ((x < -r) << 1);
	tot += ((y > r) << 2);
	tot += ((y < -r) << 3);
	tot += ((z > r) << 4);
	tot += ((z < -r) << 5);
	return tot; 
}

void GLDrawPane::drawBox(int faces, double alpha,bool front)
{
	if (faces & (1<<0))
	{
		glColor4d(1.0,0.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(2*front-1,0,0);
		glVertex3d(maxZoom,maxZoom,-maxZoom);
		glVertex3d(maxZoom,maxZoom,maxZoom);
		glVertex3d(maxZoom,-maxZoom,-maxZoom);
		glVertex3d(maxZoom,-maxZoom,maxZoom);
		glEnd();
	}
	if (faces & (1<<1))
	{
		glColor4d(1.0,0.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(1-2*front,0,0);
		glVertex3d(-maxZoom,-maxZoom,-maxZoom);
		glVertex3d(-maxZoom,-maxZoom,maxZoom);
		glVertex3d(-maxZoom,maxZoom,-maxZoom);
		glVertex3d(-maxZoom,maxZoom,maxZoom);
		glEnd();
	}
	if (faces & (1<<2))
	{
		glColor4d(0.0,1.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,2*front-1,0);
		glVertex3d(-maxZoom,maxZoom,maxZoom);
		glVertex3d(maxZoom,maxZoom,maxZoom);
		glVertex3d(-maxZoom,maxZoom,-maxZoom);
		glVertex3d(maxZoom,maxZoom,-maxZoom);
		glEnd();
	}
	if (faces & (1<<3))
	{
		glColor4d(0.0,1.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,1-2*front,0);
		glVertex3d(-maxZoom,-maxZoom,-maxZoom);
		glVertex3d(maxZoom,-maxZoom,-maxZoom);
		glVertex3d(-maxZoom,-maxZoom,maxZoom);
		glVertex3d(maxZoom,-maxZoom,maxZoom);
		glEnd();
	}
	if (faces & (1<<4))
	{
		glColor4d(0.0,0.0,1.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,0,2*front-1);
		glVertex3d(maxZoom,-maxZoom,maxZoom);
		glVertex3d(maxZoom,maxZoom,maxZoom);
		glVertex3d(-maxZoom,-maxZoom,maxZoom);
		glVertex3d(-maxZoom,maxZoom,maxZoom);
		glEnd();
	}
	if (faces & (1<<5))
	{
		glColor4d(0.0,0.0,1.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,0,1-2*front);
		glVertex3d(-maxZoom,-maxZoom,-maxZoom);
		glVertex3d(-maxZoom,maxZoom,-maxZoom);
		glVertex3d(maxZoom,-maxZoom,-maxZoom);
		glVertex3d(maxZoom,maxZoom,-maxZoom);
		glEnd();
	}
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
	drawBox(GLDrawPane::boxFrontFaces(maxZoom,pos[0],pos[1],pos[2]),.25,false);
	glDisable(GL_BLEND);
	/*const vector<DrawableObject *> & objs = panel->getObjs();
	for (int i = 0;i < (int)objs.size();i++) {
	  drawObject(*(objs[i]));
	  }*/
	glEnable(GL_BLEND);
	drawBox(GLDrawPane::boxFrontFaces(maxZoom,pos[0],pos[1],pos[2]),.25,true);
	glDisable(GL_BLEND);
}

void GLDrawPane::resizeGL(int _width,int _height)
{
	height = _height;
	width = _width;
}

#endif
