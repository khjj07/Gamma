#pragma once
#include <functional>
#include <exception>
#include <list>
#include "IObservable.h"
#include "IObserver.h"
#include "IDisposable.h"
#include "SubjectObserver.h"
using namespace std;



template <typename T>
class Subject : public IObservable<T>, IObserver<T>
{
public:
	Subject();
	~Subject();

public:
	virtual void Subscribe(function<void(T)>);
	virtual void Subscribe(function<void(T)>, function<void(T)>);
	virtual void Subscribe(function<void(T)>, function<void(T)>, function<void(exception)>);

public:
	virtual void OnNext(T);
	virtual void OnComplete(T);
	virtual void OnError(exception);

public:
	Subject<T>& Where(function<bool(T)>);

public:
	vector<IObserver<T>*> observers;
	vector<function<bool(T)> > predicates;
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
void Subject<T>::Subscribe(function<void(T)> onNext)
{
	SubjectObserver<T>* newObserver = new SubjectObserver<T>(predicates,onNext);
	predicates.clear();
	observers.push_back(newObserver);
}

template<typename T>
void Subject<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete)
{
	SubjectObserver<T>* newObserver = new SubjectObserver<T>(predicates,onNext, onComplete);
	predicates.clear();
	observers.push_back(newObserver);
}

template<typename T>
void Subject<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete, function<void(exception)> onError)
{
	SubjectObserver<T>* newObserver = new SubjectObserver<T>(predicates,onNext, onComplete, onError);
	predicates.clear();
	observers.push_back(newObserver);
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

template<typename T>
Subject<T>& Subject<T>::Where(function<bool(T)> predicate)
{
	predicates.push_back(predicate);
	return *this;
}