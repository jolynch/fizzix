#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <libfizzix/fizobject.h>

class DrawableObject:public FizObject
{
private:
	int properties
public:
	/** Default Constructor
	 */
	DrawableObject(int props = 0):FizObject();
	/** Constructor that inits the name
	 */
	DrawableObject(std:string newname, int props = 0):FizObject(newname);
	/** Constructor that inits the name, color and possibly the smoothity
	 */
	DrawableObject(std::string newname, vec3 color, int props = 0):FizObject(newname,color);
	/** Constructor that inits the name and vertices and possibly the smoothity
	 */	
	DrawableObject(std::string newname, std::vector<triangle> init, int props = 0):FizObject(newname,init);
	/** Constructor that inits the vertices, color, and smoothity
	 */
	DrawableObject(std::string newname, vec3 color, std::vector<triangle> init, int props = 0):FizObject(newname,color,init);
   	bool getProperty(int bit);
	int getProperties();
	void setProperty(int bit,bool set);
	void setProperties(int props);
};

#endif
