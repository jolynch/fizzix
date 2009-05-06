#ifndef DRAWABLEOBJECT_CPP
#define DRAWABLEOBJECT_CPP

#include <QDebug>
#include <math.h>
#include "drawableobject.h"

#define PI 3.1415926535

using namespace std;

DrawableObject::DrawableObject():FizObject()
{
	properties = 0;
}

DrawableObject::DrawableObject(string newname, double mass):FizObject(newname, mass)
{
	properties = 0;
}

DrawableObject::DrawableObject(string newname, vec3 color, double mass):FizObject(newname, color, mass)
{
	properties = 0;
}

DrawableObject::DrawableObject(string newname, vector<triangle*> init, double mass):FizObject(newname, init, mass)
{
	properties = 0;
}

DrawableObject::DrawableObject(string newname, vec3 color, vector<triangle*> init, double mass):FizObject(newname, color, init, mass)
{
	properties = 0;
}

bool DrawableObject::getProperty(Bit bit) const
{
	return ((bool)((properties & (1 << bit))) >> bit);
}

int DrawableObject::getProperties() const
{
	return properties;
}

void DrawableObject::setProperty(Bit bit, bool set)
{
	properties|=(((int)set) << bit);
	properties&=(((int)set) << bit);
}

void DrawableObject::setProperties(int props)
{
	properties = props;
}

vector<triangle*> DrawableObject::makeSphere(double radius, int subdivs)
{
	vertex * prevVs = new vertex[6];
	prevVs[0] = vertex(radius,0,0);
	prevVs[1] = vertex(-radius,0,0);
	prevVs[2] = vertex(0,radius,0);
	prevVs[3] = vertex(0,-radius,0);
	prevVs[4] = vertex(0,0,radius);
	prevVs[5] = vertex(0,0,-radius);
	triangle * prevTs = new triangle[8];
	prevTs[0] = triangle(prevVs+0,prevVs+2,prevVs+4,false);
	prevVs[0].add_triangle(prevTs+0);
	prevVs[2].add_triangle(prevTs+0);
	prevVs[4].add_triangle(prevTs+0);

	prevTs[1] = triangle(prevVs+0,prevVs+4,prevVs+3,false);
	prevVs[0].add_triangle(prevTs+1);
	prevVs[4].add_triangle(prevTs+1);
	prevVs[3].add_triangle(prevTs+1);

	prevTs[2] = triangle(prevVs+0,prevVs+3,prevVs+5,false);
	prevVs[0].add_triangle(prevTs+2);
	prevVs[3].add_triangle(prevTs+2);
	prevVs[5].add_triangle(prevTs+2);

	prevTs[3] = triangle(prevVs+0,prevVs+5,prevVs+2,false);
	prevVs[0].add_triangle(prevTs+3);
	prevVs[5].add_triangle(prevTs+3);
	prevVs[2].add_triangle(prevTs+3);

	prevTs[4] = triangle(prevVs+1,prevVs+4,prevVs+2,false);
	prevVs[1].add_triangle(prevTs+4);
	prevVs[4].add_triangle(prevTs+4);
	prevVs[2].add_triangle(prevTs+4);

	prevTs[5] = triangle(prevVs+1,prevVs+3,prevVs+4,false);
	prevVs[1].add_triangle(prevTs+5);
	prevVs[3].add_triangle(prevTs+5);
	prevVs[4].add_triangle(prevTs+5);

	prevTs[6] = triangle(prevVs+1,prevVs+5,prevVs+3,false);
	prevVs[1].add_triangle(prevTs+6);
	prevVs[5].add_triangle(prevTs+6);
	prevVs[3].add_triangle(prevTs+6);

	prevTs[7] = triangle(prevVs+1,prevVs+2,prevVs+5,false);
	prevVs[1].add_triangle(prevTs+7);
	prevVs[2].add_triangle(prevTs+7);
	prevVs[5].add_triangle(prevTs+7);

	int pnv = 6;
	int pnf = 8;
	for (int i = 0;i < subdivs;i++)
	{
		int cnf = 4*pnf;
		int cnv = 2 * pnv + pnf - 2;
		vertex * currVs = new vertex[cnv];
		int numVs;
		for(numVs = 0;numVs < pnv;numVs++)
		{
			currVs[numVs] = prevVs[numVs];
		}
		triangle * currTs = new triangle[cnf];
		for (int t = 0;t < pnf;t++)
		{
			triangle * currTriangle = prevTs + t;
			vertex ** tverts = currTriangle->vertices;
			vertex * midpoints[3];
			for (int v = 0;v < 3;v++)
			{
				vertex * v1 = tverts[v];
				int vTo = (v+1)%3;
				vertex * v2 = tverts[vTo];
				int other = (v+2)%3;
				triangle * tnext = 0;
				int same;
				for (int t2 = 0; t2 < ((int)(v1->triangles.size()));t2++)
				{
					same = 7;
					tnext = (v1->triangles)[t2];
					if (tnext != currTriangle)
					{
						for (int vadj = 0;vadj < 3;vadj++)
						{
							vertex * vtest = (tnext->vertices)[vadj];
							if ((vtest == v1) || (vtest == v2))
							{
								same ^= (1 << vadj);
							}
						}
						if ((same == 1) || (same == 2) || (same == 4))
						{
							t2 = ((int)(v1->triangles.size()));
						}
					}
				}
				int otherPos = tnext - prevTs;
				if (t > otherPos)
				{
					int b;
					for (b = -1;same != 0;b++)
					{
						same >>= 1;
					}
					midpoints[other] = ((currTs+(4*otherPos))->vertices)[b];
				}
				else
				{
					vec3 mid = ((v1->p)+(v2->p))/2.0;
					double mag = mid.mag();
				   	mid *= radius;
					mid /= mag;
					currVs[numVs] = vertex(mid[0],mid[1],mid[2]);
					midpoints[other] = (currVs + numVs);
					numVs++;
				}
			}
			int oldInd0 = tverts[0]-prevVs;
			int oldInd1 = tverts[1]-prevVs;
			int oldInd2 = tverts[2]-prevVs;
			currTs[4*t] = triangle(midpoints[0],midpoints[1],midpoints[2],false);
			midpoints[0]->add_triangle(currTs+(4*t+0));
			midpoints[1]->add_triangle(currTs+(4*t+0));
			midpoints[2]->add_triangle(currTs+(4*t+0));
			currTs[4*t+1] = triangle(currVs+oldInd0,midpoints[2],midpoints[1],false);
			currVs[oldInd0].add_triangle(currTs+(4*t+1));
			midpoints[2]->add_triangle(currTs+(4*t+1));
			midpoints[1]->add_triangle(currTs+(4*t+1));
			currTs[4*t+2] = triangle(midpoints[2],currVs+oldInd1,midpoints[0],false);
			midpoints[2]->add_triangle(currTs+(4*t+2));
			currVs[oldInd1].add_triangle(currTs+(4*t+2));
			midpoints[0]->add_triangle(currTs+(4*t+2));
			currTs[4*t+3] = triangle(midpoints[1],midpoints[0],currVs+oldInd2,false);
			midpoints[1]->add_triangle(currTs+(4*t+3));
			midpoints[0]->add_triangle(currTs+(4*t+3));
			currVs[oldInd2].add_triangle(currTs+(4*t+3));
		}
		pnv = cnv;
		pnf = cnf;
		delete[] prevVs;
		delete[] prevTs;
		prevVs = currVs;
		prevTs = currTs;
	}

	vector<triangle *> triangles;
	for (int i = 0;i < pnf;i++)
	{
		triangles.push_back(prevTs+i);
	}
	return triangles;
}

vector<triangle *> DrawableObject::makeCylinder(double radius, double height, int num)
{
	vertex * vertices = new vertex[num * 4 + 2];
	vertices[2*num] = vertex(0,0,height);
	vertices[2*num+1] = vertex(0,0,-height);
	for (int i = 0;i < 2*num;i++)
	{
		int sign = 1 - (i & 1) * 2;
		double theta = PI * (double)i / (double)num;
		double c = cos(theta);
		double s = sin(theta);
		vertices[i] = vertex(c*radius,s*radius,sign*height);
		vertices[i + 2*num + 2] = vertex(c*radius,s*radius,sign*height);
	}

	vector<triangle *> triangles;
	for (int i = 0;i < num-1;i++)
	{
		triangles.push_back(new triangle(vertices+(2*i+0),vertices+(2*i+1),vertices+(2*i+2)));
		triangles.push_back(new triangle(vertices+(2*i+1),vertices+(2*i+3),vertices+(2*i+2)));
		triangles.push_back(new triangle(vertices+(2*num),vertices+(2*i+2*num+2),vertices+(2*i+2*num+4)));
		triangles.push_back(new triangle(vertices+(2*num+1),vertices+(2*i+2*num+5),vertices+(2*i+2*num+3)));
	}
	triangles.push_back(new triangle(vertices+(2*num-2),vertices+(2*num-1),vertices+0));
	triangles.push_back(new triangle(vertices+(2*num-1),vertices+1,vertices+0));
	triangles.push_back(new triangle(vertices+(2*num),vertices+(4*num),vertices+(2*num+2)));
	triangles.push_back(new triangle(vertices+(2*num+1),vertices+(2*num+3),vertices+(4*num+1)));

	return triangles;
}

vector<triangle *> DrawableObject::makePrism(double length, double width, double height)
{
	vertex * vertices = new vertex[14];
	vertices[0] = vertex(length, width, height);
	vertices[1] = vertex(length, width, -height);
	vertices[2] = vertex(length, -width, height);
	vertices[3] = vertex(length, -width, -height);
	vertices[4] = vertex(-length, width, height);
	vertices[5] = vertex(-length, width, -height);
	vertices[6] = vertex(-length, -width, height);
	vertices[7] = vertex(-length, -width, -height);
	vertices[8] = vertex(length, 0, 0);
	vertices[9] = vertex(-length, 0, 0);
	vertices[10] = vertex(0, width, 0);
	vertices[11] = vertex(0, -width, 0);
	vertices[12] = vertex(0, 0, height);
	vertices[13] = vertex(0, 0, -height);

	vector<triangle *> triangles;
	triangles.push_back(new triangle(vertices+8,vertices+0,vertices+2));
	triangles.push_back(new triangle(vertices+8,vertices+2,vertices+3));
	triangles.push_back(new triangle(vertices+8,vertices+3,vertices+1));
	triangles.push_back(new triangle(vertices+8,vertices+1,vertices+0));
	triangles.push_back(new triangle(vertices+9,vertices+4,vertices+5));
	triangles.push_back(new triangle(vertices+9,vertices+5,vertices+7));
	triangles.push_back(new triangle(vertices+9,vertices+7,vertices+6));
	triangles.push_back(new triangle(vertices+9,vertices+6,vertices+4));
	triangles.push_back(new triangle(vertices+10,vertices+0,vertices+1));
	triangles.push_back(new triangle(vertices+10,vertices+1,vertices+5));
	triangles.push_back(new triangle(vertices+10,vertices+5,vertices+4));
	triangles.push_back(new triangle(vertices+10,vertices+4,vertices+0));
	triangles.push_back(new triangle(vertices+11,vertices+2,vertices+6));
	triangles.push_back(new triangle(vertices+11,vertices+6,vertices+7));
	triangles.push_back(new triangle(vertices+11,vertices+7,vertices+3));
	triangles.push_back(new triangle(vertices+11,vertices+3,vertices+2));
	triangles.push_back(new triangle(vertices+12,vertices+0,vertices+4));
	triangles.push_back(new triangle(vertices+12,vertices+4,vertices+6));
	triangles.push_back(new triangle(vertices+12,vertices+6,vertices+2));
	triangles.push_back(new triangle(vertices+12,vertices+2,vertices+0));
	triangles.push_back(new triangle(vertices+13,vertices+1,vertices+3));
	triangles.push_back(new triangle(vertices+13,vertices+3,vertices+7));
	triangles.push_back(new triangle(vertices+13,vertices+7,vertices+5));
	triangles.push_back(new triangle(vertices+13,vertices+5,vertices+1));

	return triangles;
}

#endif
