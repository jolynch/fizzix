#ifndef MAPUTIL_H
#define MAPUTIL_H

#include <string>
#include <iterator>
#include <map>
#include <QMap>

template <class T>
class MapUtil
{
	public:
	static std::map<std::string, T> * qMapToStdMapCopy(QMap<QString, T> arg)
	{
		std::map<std::string, T> * toReturn=new std::map<std::string, T>();
		QMapIterator<QString, T> i(arg);
		while(i.hasNext()) 
		{
			i.next();
			(*toReturn)[(i.key().toStdString())]=i.value();
 		}
		return toReturn;
	}
	
	static std::map<std::string, T*> * qMapToStdMapCopy(QMap<QString, T*> arg)
	{
		std::map<std::string, T*> * toReturn=new std::map<std::string, T*>();
		QMapIterator<QString, T*> i(arg);
		while(i.hasNext()) 
		{
			i.next();
			(*toReturn)[(i.key().toStdString())]=new T(*(i.value()));
 		}
		return toReturn;
	}
	
	static void deepDelete(QMap<QString, T*> * arg)
	{
		QMapIterator<QString, T*> i(&arg);
		while(i.hasNext()) 
		{
			i.next();
			delete i.value();
			i.value()=NULL;
 		}
		delete arg;
	}

	static void deepDelete(std::map<std::string, T*> * arg)
	{
		typename std::map<std::string, T*>::iterator p;
		for(p = arg->begin(); p != arg->end(); p++)
		{
			delete p->second;
			p->second=NULL;
		}
	}

};

#endif
