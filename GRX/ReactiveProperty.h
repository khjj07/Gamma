#pragma once
#include <functional>
#include <exception>
#include <list>
#include "IObservable.h"
#include "IObserver.h"
#include "IDisposable.h"
#include "Observer.h"
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
	vector<Action<T>*> action;
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
		(*iter)->OnNext(value);
	}
}

template<typename T>
void ReactiveProperty<T>::Subscribe(function<void(T)> onNext)
{
	Observer<T>* newObserver = new Observer<T>(action, onNext);
	action.clear();
	observers.push_back(newObserver);
}

template<typename T>
void ReactiveProperty<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete)
{
	Observer<T>* newObserver = new Observer<T>(action, onNext, onComplete);
	action.clear();
	observers.push_back(newObserver);
}

template<typename T>
void ReactiveProperty<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete, function<void(exception)> onError)
{
	Observer<T>* newObserver = new Observer<T>(action, onNext, onComplete, onError);
	action.clear();
	observers.push_back(newObserver);
}

template<typename T>
ReactiveProperty<T>& ReactiveProperty<T>::Where(function<bool(T)> predicate)
{
	action.push_back(predicate);
	return *this;
}