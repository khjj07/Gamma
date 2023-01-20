#pragma once
#include <functional>
#include <exception>
#include <list>
#include "Observable.h"
#include "IObserver.h"
#include "IDisposable.h"
#include "Observer.h"
using namespace std;



template <typename T>
class Subject : public Observable<T>, IObserver<T>
{
public:
	Subject();
	~Subject();

public:
	virtual void OnNext(T);
	virtual void OnComplete(T);
	virtual void OnError(exception);


};

template<typename T>
Subject<T>::Subject()
{

}

template<typename T>
Subject<T>::~Subject()
{

}

template<typename T>
void Subject<T>::OnNext(T data)
{
	try
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnNext(data);
		}
	}
	catch (exception e)
	{
		OnError(e);
	}

}

template<typename T>
void Subject<T>::OnComplete(T data)
{
	try
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnComplete(data);
		}
	}
	catch (exception e)
	{
		OnError(e);
	}
}

template<typename T>
void Subject<T>::OnError(exception e)
{
	for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
	{
		(*iter)->OnError(e);
	}
}

