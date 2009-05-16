#ifndef MAPUTIL_H
#define MAPUTIL_H

#include <string>
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
			toReturn->insert(i.key().toStdString(),i.value());
 		}
		return toReturn;
	}
	
	static QMap<QString, T*> * mapCopy(QMap<QString, T*> arg)
	{
		QMap<QString, T*> * toReturn=new QMap<QString, T*>();
		QMapIterator<QString, T*> i(arg);
		while(i.hasNext()) 
		{
			i.next();
			toReturn->insert(i.key(), new T(*(i.value())));
 		}
		return toReturn;
	}

	static QMap<QString, T> * mapCopy(QMap<QString, T> arg)
	{
		QMap<QString, T> * toReturn = new QMap<QString, T>(arg);
		return toReturn;
	}
	
};

#endif
