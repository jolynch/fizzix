#ifndef DRAWABLEOBJECT_CPP
#define DRAWABLEOBJECT_CPP

#include "drawableobject.h"

using namespace std;

DrawableObject::DrawableObject(int props):FizObject()
{
	properties = props;
}

DrawableObject::DrawableObject(string newname, int props):FizObject(newname)
{
	properties = props;
}

DrawableObject::DrawableObject(string newname, vec3 color, int props):FizObject(newname, color)
{
	properties = props;
}

DrawableObject::DrawableObject(string newname, vector<triangle*> init, int props):FizObject(newname, init)
{
	properties = props;
}

DrawableObject::DrawableObject(string newname, vec3 color, vector<triangle*> init, int props):FizObject(newname,color,init)
{
	properties = props;
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

#endif
