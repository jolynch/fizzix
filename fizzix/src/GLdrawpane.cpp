#ifndef GLDRAWPANE_CPP
#define GLDRAWPANE_CPP

#include "GLdrawpane.h"

#include <math.h>

//#include <GL/gl.h>
//#include <GL/glu.h>
#include <QDebug>
#include <math.h>

#define PI 3.14159265

using namespace std;

double GLDrawPane::sideToZoom = 1.0/(2.0*sqrt(3.0));

GLDrawPane::GLDrawPane(QWidget * parent, double _rotate, double _zoom, double _maxZoom, double fieldOfView) : QGLWidget(parent)
{
	rotSpeed = _rotate;
	zoomSpeed = _zoom;
	fov = fieldOfView;
	rot = Quaternion();
	currRot = Quaternion();
	maxZoom = _maxZoom;
	zoom = maxZoom;
	height = 0;
	width = 0;
	double theta = 0.955316618-.1;
	double to2 = theta/2.0;
	rot = Quaternion(cos(to2),sin(to2)/sqrt(2),sin(to2)/sqrt(2),0.0);
	setMouseTracking(true);
}


QSize GLDrawPane::sizeHint() const
{
	return QSize(700,800);
}

void GLDrawPane::rotate(double upAmt, double leftAmt)
{
	vec3 pos = rot.transformVec(vec3(0,0,1));
	vec3 up = rot.transformVec(vec3(0,1,0));
	vec3 left = pos.cross(up);
	vec3 comb = up*upAmt + left*leftAmt;
	double mag = comb.mag();
	comb /= mag;
	mag *= rotSpeed;
	vec3 axis = comb.cross(pos);
	vec3 vecPart = axis*sin(mag);
	Quaternion toRot(cos(mag),vecPart.x,vecPart.y,vecPart.z);
	currRot = toRot;
	rot = toRot * rot;
	rot.normalize(.0000001);
}

void GLDrawPane::changeZoom(double amount)
{
	zoom += amount * zoomSpeed;
	if (zoom > maxZoom) zoom = maxZoom;
	if (zoom < -maxZoom) zoom = -maxZoom;
}

vec3 GLDrawPane::moveCamera()
{
	vec3 pos = rot.transformVec(vec3(0,0,1));
	pos *= zoom;
	vec3 up = rot.transformVec(vec3(0,1,0));
	//	qDebug("Rotation: (%f, %f, %f, %f)",rot[0],rot[1],rot[2],rot[3]);
	//	qDebug("Position: (%f, %f, %f)\nUp:  (%f, %f, %f)",pos.x,pos.y,pos.z,up.x,up.y,up.z);
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
		const Quaternion & q = obj.getQuaternion();
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
					currNormal = q.transformVec(currNormal);
					glNormal3d(currNormal[0],currNormal[1],currNormal[2]);
					vec3 rotV = q.transformVec(currV.p);
					glVertex3d(rotV[0],rotV[1],rotV[2]);
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
				vec3 rotNormal = q.transformVec(n);
				glNormal3d(rotNormal[0],rotNormal[1],rotNormal[2]);
				for (int v = 0;v < 3;v++)
				{
					const vertex & currV = currT[v];
					vec3 rotV = q.transformVec(currV.p);
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
	int f = (int)(!front);
	double l = maxZoom*sideToZoom;
	if ((faces & (1 << 0)) ^ (f<<0))
	{
		glColor4d(1.0,0.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(2*front-1,0,0);
		glVertex3d(l,l,-l);
		glVertex3d(l,l,l);
		glVertex3d(l,-l,-l);
		glVertex3d(l,-l,l);
		glEnd();
	}
	if ((faces & (1 << 1)) ^ (f<<1))
	{
		glColor4d(1.0,0.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(1-2*front,0,0);
		glVertex3d(-l,-l,-l);
		glVertex3d(-l,-l,l);
		glVertex3d(-l,l,-l);
		glVertex3d(-l,l,l);
		glEnd();
	}
	if ((faces & (1 << 2)) ^ (f<<2))
	{
		glColor4d(0.0,1.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,2*front-1,0);
		glVertex3d(-l,l,l);
		glVertex3d(l,l,l);
		glVertex3d(-l,l,-l);
		glVertex3d(l,l,-l);
		glEnd();
	}
	if ((faces & (1 << 3)) ^ (f<<3))
	{
		glColor4d(0.0,1.0,0.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,1-2*front,0);
		glVertex3d(-l,-l,-l);
		glVertex3d(l,-l,-l);
		glVertex3d(-l,-l,l);
		glVertex3d(l,-l,l);
		glEnd();
	}
	if ((faces & (1 << 4)) ^ (f<<4))
	{
		glColor4d(0.0,0.0,1.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,0,2*front-1);
		glVertex3d(l,-l,l);
		glVertex3d(l,l,l);
		glVertex3d(-l,-l,l);
		glVertex3d(-l,l,l);
		glEnd();
	}
	if ((faces & (1 << 5)) ^ (f<<5))
	{
		glColor4d(0.0,0.0,1.0,alpha);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(0,0,1-2*front);
		glVertex3d(-l,-l,-l);
		glVertex3d(-l,l,-l);
		glVertex3d(l,-l,-l);
		glVertex3d(l,l,-l);
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
	rot = currRot * rot;
	rot.normalize(0.0001);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,width/height,.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vec3 pos = moveCamera();
	glEnable(GL_BLEND);
	drawBox(GLDrawPane::boxFrontFaces(maxZoom*sideToZoom,pos[0],pos[1],pos[2]),.25,false);
	glDisable(GL_BLEND);
	/*const vector<DrawableObject *> & objs = panel->getObjs();
	for (int i = 0;i < (int)objs.size();i++) {
	  drawObject(*(objs[i]));
	  }*/
	glEnable(GL_BLEND);
	drawBox(GLDrawPane::boxFrontFaces(maxZoom*sideToZoom,pos[0],pos[1],pos[2]),.25,true);
	glDisable(GL_BLEND);
}

void GLDrawPane::resizeGL(int _width,int _height)
{
	height = _height;
	width = _width;
	glViewport(0,0,width,height);
}

void GLDrawPane::mouseMoveEvent(QMouseEvent * event)
{
	if ((event -> modifiers()) && (Qt::ControlModifier))
	{
		double scale = qMin(width/2.0, height/2.0);
		double xDist = (width/2.0) - ((event -> pos()).x());
		double yDist = (height/2.0) - ((event -> pos()).y());
		xDist/=scale;
		yDist/=scale;
		rotate(yDist,xDist);
		repaint();
	}
}

#endif
