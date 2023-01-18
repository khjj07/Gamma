#pragma once
#include <exception>
#include <functional>
#include <list>
using namespace std;

template<typename T>
class Subject;

template<typename T>
class Observer;

template <typename T>
class Observable
{
public:
	friend class Subject<T>;

public:
	Observable();
	Observable(Observer<T>*, Observable*);

public:
	Observable<T> Where(function<bool(T)>);
	Observable<T> Subscribe(function<void(T)>);
	Observable<T> Subscribe(function<void(T)>, function<void(T)>);
	Observable<T> Subscribe(function<void(T)>, function<void(T)>, function<void(T)>);
	virtual void OnNext(T);
	virtual void OnComplete(T);
	virtual void OnError(exception);

public:
	Observer<T>* observer;
	list<function<bool(T)> > condition;

public:
	list<Observable<T> > observables;

};

template<typename T>
Observable<T>::Observable()
{
	
}

template<typename T>
Observable<T>::Observable(Observer<T>* observer, Observable* observable)
	:observer(observer)
{
	condition = observable->condition;
}

template<typename T>
Observable<T> Observable<T>::Subscribe(function<void(T)> onNext)
{
	Observer<T>* newObserver = new Observer<T>(onNext);
	Observable<T>* newObservable = new Observable<T>(newObserver, this);
	observables.push_back(*newObservable);
	return *newObservable;
}

template<typename T>
Observable<T> Observable<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete)
{
	Observer<T>* newObserver = new Observer<T>(onNext);
	Observable<T>* newObservable = new Observable<T>(newObserver, this);
	observables.push_back(*newObservable);
	return *newObservable;
}

template<typename T>
Observable<T> Observable<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete, function<void(T)> onError)
{
	Observer<T>* newObserver = new Observer<T>(onNext, onComplete, onError);
	Observable<T>* newObservable = new Observable<T>(newObserver, this);
	observables.push_back(*newObservable);
	return *newObservable;
}

template<typename T>
void Observable<T>::OnNext(T data)
{
	for (auto iter = condition.begin(); iter != condition.end(); iter++)
	{
		if (!(*iter)(data))
		{
			return;
		}
	}
	observer->OnNext(data);
}

template<typename T>
void Observable<T>::OnComplete(T data)
{
	observer->OnComplete(data);
}

template<typename T>
void Observable<T>::OnError(exception e)
{
	observer->OnError(e);
}

template<typename T>
Observable<T> Observable<T>::Where(function<bool(T)> con)
{
	Observable<T> ret;
	condition.push_back(con);

	return ret;
}