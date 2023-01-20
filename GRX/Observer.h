#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"
#include "Action.h"

using namespace std;


template <typename T>
class Observer : public IObserver<T>
{
public:
	Observer(vector<Action<T>*>, function<void(T)>);
	Observer(vector<Action<T>*>, function<void(T)>, function<void(T)>);
	Observer(vector<Action<T>*>, function<void(T)>, function<void(T)>, function<void(exception)>);

public:
	virtual void OnNext(T);
	virtual void OnComplete(T);
	virtual void OnError(exception);

public:
	function<void(T)> onNextCallback;
	function<void(T)> onCompleteCallback;
	function<void(exception)> onErrorCallback;
	vector<Action<T>*> action;
};

template<typename T>
Observer<T>::Observer(vector<Action<T>*> action, function<void(T)> onNext)
	:action(action), onNextCallback(onNext)
{

}

template<typename T>
Observer<T>::Observer(vector<Action<T>*> action, function<void(T)> onNext, function<void(T)> onComplete, function<void(exception)> onError)
	:action(action), onNextCallback(onNext), onCompleteCallback(onComplete), onErrorCallback(onError)
{

}

template<typename T>
Observer<T>::Observer(vector<Action<T>*> action, function<void(T)> onNext, function<void(T)> onComplete)
	:action(action), onNextCallback(onNext), onCompleteCallback(onComplete)
{

}


template <typename T>
void Observer<T>::OnNext(T data)
{
	for (auto iter = action.begin(); iter < action.end(); iter++)
	{
		QueryAction<T>* temp1=dynamic_cast<QueryAction<T>*>(*iter);
		PredicateAction<T>* temp2=dynamic_cast<PredicateAction<T>*>(*iter);
		if (temp1)
		{
			data = temp1->action(data);
		}
		else if (temp2 && !(temp2->action(data)))
		{
			return;
		}
		
	}
	onNextCallback(data);
}

template <typename T>
void Observer<T>::OnComplete(T data)
{
	for (auto iter = action.begin(); iter < action.end(); iter++)
	{
		QueryAction<T>* temp1 = dynamic_cast<QueryAction<T>*>(*iter);
		PredicateAction<T>* temp2 = dynamic_cast<PredicateAction<T>*>(*iter);
		if (temp1)
		{
			data = temp1->action(data);
		}
		else if (temp2 && !(temp2->action(data)))
		{
			return;
		}
	}
	onCompleteCallback(data);
}

template <typename T>
void Observer<T>::OnError(exception e)
{
	onErrorCallback(e);
}