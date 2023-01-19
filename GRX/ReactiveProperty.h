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
class ReactiveProperty : public IObservable<T>
{
public:
	ReactiveProperty();
	ReactiveProperty(T val);
	~ReactiveProperty();
	T value;
	void operator =(T val)
	{
		value = val;
		Notify();
	}
public:
	void Notify();

public:
	virtual void Subscribe(function<void(T)> onNext);
	virtual void Subscribe(function<void(T)> onNext, function<void(T)> onComplete);
	virtual void Subscribe(function<void(T)> onNext, function<void(T)> onComplete, function<void(exception)> onError);
	ReactiveProperty<T>& Where(function<bool(T)> predicate);

public:
	vector<IObserver<T>*> observers;
	vector<function<bool(T)> > predicates;
};

template<typename T>
ReactiveProperty<T>::ReactiveProperty()
{

}

template<typename T>
ReactiveProperty<T>::ReactiveProperty(T val)
{
	value = val;
}

template<typename T>
ReactiveProperty<T>::~ReactiveProperty()
{

}
template<typename T>
void ReactiveProperty<T>::Notify()
{
	for (auto iter = observers.begin(); iter < observers.end(); iter++)
	{
		(*iter)->OnNext(T);
	}
}

template<typename T>
void ReactiveProperty<T>::Subscribe(function<void(T)> onNext)
{
	SubjectObserver<T>* newObserver = new SubjectObserver<T>(predicates, onNext);
	predicates.clear();
	observers.push_back(newObserver);
}

template<typename T>
void ReactiveProperty<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete)
{
	SubjectObserver<T>* newObserver = new SubjectObserver<T>(predicates, onNext, onComplete);
	predicates.clear();
	observers.push_back(newObserver);
}

template<typename T>
void ReactiveProperty<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete, function<void(exception)> onError)
{
	SubjectObserver<T>* newObserver = new SubjectObserver<T>(predicates, onNext, onComplete, onError);
	predicates.clear();
	observers.push_back(newObserver);
}

template<typename T>
ReactiveProperty<T>& ReactiveProperty<T>::Where(function<bool(T)> predicate)
{
	predicates.push_back(predicate);
	return *this;
}