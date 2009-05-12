#ifndef MAPUTIL_H
#define MAPUTIL_H

#include <string>
#include <map>
#include <QMap>

template <class T>
class MapUtil
{
	public:
	static std::map<std::string, T> qMapToStdMap(QMap<QString, T> arg)
	{
		std::map<std::string, T> toReturn;
		QMapIterator<QString, T> i(arg);
		while(i.hasNext()) 
		{
			i.next();
			toReturn[i.key().toStdString()] = i.value();
 		}
		return toReturn;
	}
	
	static QMap<QString, T*> mapCopy(QMap<QString, T*> arg)
	{
		QMap<QString, T*> toReturn;
		QMapIterator<QString, T*> i(arg);
		while(i.hasNext()) 
		{
			i.next();
			toReturn[i.key()] = new T(*(i.value()));
 		}
		return toReturn;
	}

	static QMap<QString, T> mapCopy(QMap<QString, T> arg)
	{
		QMap<QString, T> toReturn = arg;
		return toReturn;
	}
	
};

#endif
