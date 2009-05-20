#ifndef MAPKEYLISTMODEL_H
#define MAPKEYLISTMODEL_H

#include <QStringListModel>
#include <QString>
#include <QMap>
#include <map>

template <class T>
// This is a template class that provides functionality to create a Qt model that provides a QStringListModel to a view. It provides an easy way to link the data to the widgets that display them.
class MapKeyListModel
{
	private:
		QStringListModel * model;
		QMap <QString, T> * data;
		//Set the model to be synchronized to the QMap.
		void synchronizeKeys();
	public:
		//Creates a new MapKeyListModel.
		MapKeyListModel();
		//Retrieves the stringlist model.
		QStringListModel * getModel();
		//Retrieves the data stored in the list.
		QMap <QString, T> * getData();
		//Sets the data of the model to d, deleting the previous data by default.
		void setData(QMap <QString, T> * d, bool deletePrevData=true);
		//To create a new element, call setElement with a new name.
		void setElement(QString name, T d);
		//To delete an element, call delElement with the element's name
		void delElement(QString name);
		//Deletes all elements from the model
		void purge();
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
	{return data;}

template <class T>
void MapKeyListModel<T>::setData(QMap <QString, T> * d, bool deletePrevData)
{
	if(deletePrevData)
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
	
template <class T>
void MapKeyListModel<T>::purge()
	{
	data->clear();
	synchronizeKeys();
	}
#endif

