#ifndef MAPKEYLISTMODEL_H
#define MAPKEYLISTMODEL_H

#include <QStringListModel>
#include <QString>
#include <QMap>
#include <map>

template <class T>
class MapKeyListModel
{
	private:
		QStringListModel * model;
		QMap <QString, T> * data;
		void synchronizeKeys();
	public:
		MapKeyListModel();
		QStringListModel * getModel();
		QMap <QString, T> * getData();
		void setData(QMap <QString, T> * d);
		//To create a new element, call setElement with a new name.
		void setElement(QString name, T d);
		void delElement(QString name);
};
#endif

#ifndef MAPKEYLISTMODEL_CPP
#define MAPKEYLISTMODEL_CPP
template <class T>
MapKeyListModel<T>::MapKeyListModel()
	{
	data=new QMap<QString, T>();
	model=new QStringListModel();
	}
	
template <class T>
QStringListModel * MapKeyListModel<T>::getModel()
	{
	return model;
	}
	
template <class T>
void MapKeyListModel<T>::synchronizeKeys()
	{
	model->setStringList(data->keys());
	}
	
template <class T>
QMap <QString, T> * MapKeyListModel<T>::getData()
	{return data->toStdMap();}

template <class T>
void MapKeyListModel<T>::setData(QMap <QString, T> * d)
	{
	delete data;
	data=d;
	synchronizeKeys();
	}

template <class T>
void MapKeyListModel<T>::setElement(QString name, T d)
	{
	if(data->contains(name))
		{
		data->remove(name);
		}
	else
		{
		model->insertRows(model->rowCount(),1);
		model->setData(model->index(model->rowCount()-1,0),name);
		}
	data->insert(name, d);
	model->sort(0);
	}

template <class T>
void MapKeyListModel<T>::delElement(QString name)
	{
	data->remove(name);
	synchronizeKeys();
	}
#endif

