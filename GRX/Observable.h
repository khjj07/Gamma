#pragma once
#include "IObservable.h"
#include "Observer.h"
#include "Action.h"
using namespace std;

template <typename T>
class Observable : public IObservable<T>
{

public:
	virtual void Subscribe(function<void(T)>);
	virtual void Subscribe(function<void(T)>, function<void(T)>);
	virtual void Subscribe(function<void(T)>, function<void(T)>, function<void(exception)>);

public:
	IObservable<T>& Where(PredicateAction<T>*);
	IObservable<T>& Where(function<bool(T)>);
	IObservable<T>& Select(QueryAction<T>*);
	IObservable<T>& Select(function<T(T)>);

public:
	vector<IObserver<T>*> observers;
	vector<Action<T>*> actions;
};

template<typename T>
void Observable<T>::Subscribe(function<void(T)> onNext)
{
	Observer<T>* newObserver = new Observer<T>(actions, onNext);
	actions.clear();
	observers.push_back(newObserver);
}

template<typename T>
void Observable<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete)
{
	Observer<T>* newObserver = new Observer<T>(actions, onNext, onComplete);
	actions.clear();
	observers.push_back(newObserver);
}

template<typename T>
void Observable<T>::Subscribe(function<void(T)> onNext, function<void(T)> onComplete, function<void(exception)> onError)
{
	Observer<T>* newObserver = new Observer<T>(actions, onNext, onComplete, onError);
	actions.clear();
	observers.push_back(newObserver);
}

template<typename T>
IObservable<T>& Observable<T>::Where(PredicateAction<T>* predicate)
{
	actions.push_back(actions);
	return *this;
}

template<typename T>
IObservable<T>& Observable<T>::Where(function<bool(T)> predicate)
{
	actions.push_back(new PredicateAction<T>(predicate));
	return *this;
}

template<typename T>
IObservable<T>& Observable<T>::Select(QueryAction<T>* query)
{
	actions.push_back(query);
	return *this;
}

template<typename T>
IObservable<T>& Observable<T>::Select(function<T(T)> query)
{
	actions.push_back(new  QueryAction<T>(query));
	return *this;
}