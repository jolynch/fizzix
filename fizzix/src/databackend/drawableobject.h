#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <libfizzix/fizobject.h>

enum Bit { HIDDEN, SMOOTH };

class DrawableObject:public FizObject
{
	private:
		int properties;
	public:
        /** Default Constructor
         */
        DrawableObject(int props = 0);
        /** Constructor that inits the name
         */
		DrawableObject(std::string newname, int props = 0);
        /** Constructor that inits the name, color and possibly the smoothity
         */
        DrawableObject(std::string newname, vec3 color, int props = 0);
        /** Constructor that inits the name and vertices and possibly the smoothity
         */     
        DrawableObject(std::string newname, std::vector<triangle> init, int props = 0);
        /** Constructor that inits the vertices, color, and smoothity
         */
        DrawableObject(std::string newname, vec3 color, std::vector<triangle> init, int props = 0);
        bool getProperty(Bit bit) const;
        int getProperties() const;
        void setProperty(Bit bit, bool set);
        void setProperties(int props);
};

#endif

