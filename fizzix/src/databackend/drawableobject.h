#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <libfizzix/fizobject.h>
#include <libfizzix/fizsphere.h>
#include <libfizzix/fizcylinder.h>
#include <libfizzix/fizprism.h>

enum Bit { HIDDEN, SMOOTH };

class DrawableObject:public FizObject
{
	private:
		int properties;
	public:
        /** Default Constructor
         */
        DrawableObject();
	/** Copy Constructor
	 */
	DrawableObject(FizObject * f);
        /** Constructor that inits the name
         */
		DrawableObject(std::string newname, double mass = 1);
        /** Constructor that inits the name and color
         */
        DrawableObject(std::string newname, vec3 color, double mass = 1);
        /** Constructor that inits the name and vertices
         */     
        DrawableObject(std::string newname, std::vector<triangle*> init, double mass = 1);
        /** Constructor that inits the name vertices, color
         */
        DrawableObject(std::string newname, vec3 color, std::vector<triangle*> init, double mass = 1);
        bool getProperty(Bit bit) const;
        int getProperties() const;
        void setProperty(Bit bit, bool set);
        void setProperties(int props);

		//Create an approximation to a sphere, the number of faces is 8 * (4 ^ subdivs)
		static std::vector<triangle *> makeSphere(double radius, int subdivs = 3);
		//Create an approximation to a cylinder, the number of rectangles around it is num
		static std::vector<triangle *> makeCylinder(double radius, double height, int num=24);
		//Create a l x w x h box
		static std::vector<triangle *> makePrism(double width, double length, double height);
};

#endif

