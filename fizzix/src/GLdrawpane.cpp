#ifndef GLDRAWPANE_CPP
#define GLDRAWPANE_CPP

#include "GLdrawpane.h"

#include <QDebug>
#include <math.h>

#define PI 3.14159265

using namespace std;

double GLDrawPane::sideToZoom = 1.0/(9.0*sqrt(3.0));
Quaternion GLDrawPane::lookatXY(1,0,0,0);
Quaternion GLDrawPane::lookatYZ(.5,.5,.5,.5);
Quaternion GLDrawPane::lookatZX(.5,-.5,-.5,-.5);
Quaternion GLDrawPane::isometric(0.880476, 0.279848, .364705, -0.115917);

GLDrawPane::GLDrawPane(DataBackend * _db,QWidget * parent, double _rotate, double _zoom, double _minZoom, double _maxZoom, double fieldOfView) : QGLWidget(parent)
{
	db=_db;
	rotSpeed = _rotate;
	zoomSpeed = _zoom;
	fov = fieldOfView;
	rot = isometric;
	minZoom = _minZoom;
	maxZoom = _maxZoom/sideToZoom;
	zoom = maxZoom*sideToZoom;
	height = 0;
	width = 0;
	setFocusPolicy(Qt::StrongFocus);
}


QSize GLDrawPane::sizeHint() const
{
	return QSize(700,800);
}

void GLDrawPane::rotate(double upAmt, double leftAmt)
{
	if (upAmt == 0 && leftAmt == 0) return;
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
	rot = toRot * rot;
	rot.normalize(0);
}

void GLDrawPane::changeZoom(double amount)
{
	zoom += amount * zoomSpeed * maxZoom;
	if (zoom > maxZoom) zoom = maxZoom;
	if (zoom < minZoom) zoom = minZoom;
}

vec3 GLDrawPane::moveCamera()
{
	vec3 pos = rot.transformVec(vec3(0,0,1));
	pos *= zoom;
	vec3 up = rot.transformVec(vec3(0,1,0));
	gluLookAt(pos.x,pos.y,pos.z,0,0,0,up.x,up.y,up.z);
	return pos;
}

void GLDrawPane::drawObject(const DrawableObject & obj)
{
	const vector<triangle*> & mesh = obj.getVertices();
	const vec3 & color = obj["SYSTEM_color"].vector/256.0;
	const vec3 & pos = obj.getPos();
	const vec3 npos(0,0,0);
	const Quaternion & q = obj.getQuaternion();
	if(isnan(pos.x)||isnan(pos.y)||isnan(pos.z))
		{drawObject(mesh, color, npos, q, obj.getProperty(HIDDEN), obj.getProperty(SMOOTH));}
	else
		{drawObject(mesh, color, pos, q, obj.getProperty(HIDDEN), obj.getProperty(SMOOTH));}
}

void GLDrawPane::drawObject(const vector<triangle *> & mesh, const vec3 & color, const vec3 & pos, const Quaternion & q, bool hidden, bool smooth)
{
	if (!hidden)
	{
		int mode;
		glGetIntegerv(GL_MATRIX_MODE,&mode);
		glEnable(GL_CULL_FACE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glColor4d(color[0],color[1],color[2],1.0);
		glTranslated(pos[0],pos[1],pos[2]);
		if (smooth)
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0;i < (int)mesh.size();i++)
			{
				const triangle & currT = *(mesh[i]);
				for (int v = 0;v < 3;v++)
				{
					const vertex & currV = currT[v];
					vec3 currNormal;
					double num;
					for (num = 0;num < (int)currV.triangles.size();num++)
					{
						vec3 unitNormal = currV(num).unit_normal;
						vec3 normal = currV(num).normal;
						if (isnan(unitNormal.x)||isnan(unitNormal.y)||isnan(unitNormal.z))
						{
						  cout << "Unit:(%f,%f,%f)" << unitNormal.x << " " << unitNormal.y << " " << unitNormal.z << endl;
						  cout << "Normal:(%f,%f,%f)" << normal.x << " " << normal.y << " " << normal.z << endl;
						}
						else
						{
							currNormal += currV(num).unit_normal;
						}
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
				const triangle & currT = *(mesh[i]);
				const vec3 & n = currT.unit_normal;
				vec3 rotNormal = q.transformVec(n);
				glNormal3d(rotNormal[0],rotNormal[1],rotNormal[2]);
				for (int v = 0;v < 3;v++)
				{
					const vertex & currV = currT[v];
					vec3 rotV = q.transformVec(currV.p);
					glVertex3d(rotV[0],rotV[1],rotV[2]);
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
		glColor4d(1.0,0.8,0.8,alpha);
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
		glColor4d(1.0,0.8,0.8,alpha);
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
		glColor4d(0.8,1.0,0.8,alpha);
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
		glColor4d(0.8,1.0,0.8,alpha);
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
		glColor4d(0.8,0.8,1.0,alpha);
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
		glColor4d(0.8,0.8,1.0,alpha);
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
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	float * toUse = new float[4];
	toUse[0] = .2; toUse[1] = .2; toUse[2] = .2; toUse[3] = 1;
	glLightfv(GL_LIGHT0, GL_AMBIENT, toUse);
	toUse[0] = .5; toUse[1] = .5; toUse[2] = .5; toUse[3] = 1;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, toUse);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	delete[] toUse;
}

void GLDrawPane::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,width/height,.1,maxZoom*2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vec3 pos = moveCamera();
	double l = maxZoom*sideToZoom*1.2;
	float * toUse = new float[4];
	toUse[0] = l; toUse[1] = l; toUse[2] = l; toUse[3] = 0;
	glLightfv(GL_LIGHT0, GL_POSITION, toUse);
	glEnable(GL_BLEND);
	drawBox(GLDrawPane::boxFrontFaces(maxZoom*sideToZoom,pos[0],pos[1],pos[2]),.25,false);
	glDisable(GL_BLEND);
	const QList<DrawableObject *> & objs = (db->getObjectModel()->getData()->values());
	for (int i = 0;i < (int)objs.size();i++) {
		DrawableObject * curr = objs[i];
		if (curr != NULL && ((FizObject *)(curr))->contains("SYSTEM_preset_geomtype"))
		{
			drawObject(*curr);
		}
	}
	glEnable(GL_BLEND);
	drawBox(GLDrawPane::boxFrontFaces(maxZoom*sideToZoom,pos[0],pos[1],pos[2]),.25,true);
	glDisable(GL_BLEND);
	
	delete[] toUse;
}

void GLDrawPane::resizeGL(int _width,int _height)
{
	height = _height;
	width = _width;
	glViewport(0,0,width,height);
}

void GLDrawPane::mouseMoveEvent(QMouseEvent * event)
{
	double scale = qMin(width/2.0, height/2.0);
	double xDist = currPoint.x() - ((event -> pos()).x());
	double yDist = currPoint.y() - ((event -> pos()).y());
	xDist/=scale;
	yDist/=scale;
	rotate(yDist,xDist);
	currPoint = event -> pos();
}

void GLDrawPane::mousePressEvent(QMouseEvent * event)
{
	currPoint = event -> pos();
}

void GLDrawPane::keyPressEvent(QKeyEvent * event)
{
	if(event->key() == Qt::Key_PageUp)
	{
		changeZoom(-1);
	}
	else if (event ->key() == Qt::Key_PageDown)
	{
		changeZoom(1);
	}	
	QGLWidget::keyPressEvent(event);
}

void GLDrawPane::wheelEvent(QWheelEvent * event)
{
  changeZoom(-((double)(event -> delta()))/120.0);
}

void GLDrawPane::setRotation(View v)
{
	if (v == XY)
	{
		rot = lookatXY;
	}
	if (v == YZ)
	{
		rot = lookatYZ;
	}
	if (v == ZX)
	{
		rot = lookatZX;
	}
	if (v == ISOMETRIC)
	{
		rot = isometric;
	}
}

void GLDrawPane::setZoomPercent(double d)
{
	zoom = maxZoom * sideToZoom * 100 / d;
}

void GLDrawPane::showCoordinateAxes(bool b)
{
	showAxes = b;
}

#endif
