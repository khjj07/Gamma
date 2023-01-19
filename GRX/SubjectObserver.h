#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"

using namespace std;


template <typename T>
class SubjectObserver : public IObserver<T>
{
public:
	SubjectObserver(vector<function<bool(T)> >, function<void(T)>);
	SubjectObserver(vector<function<bool(T)> >, function<void(T)>, function<void(T)>);
	SubjectObserver(vector<function<bool(T)> >, function<void(T)>, function<void(T)>, function<void(exception)>);

public:
	virtual void OnNext(T);
	virtual void OnComplete(T);
	virtual void OnError(exception);

public:
	function<void(T)> onNextCallback;
	function<void(T)> onCompleteCallback;
	function<void(exception)> onErrorCallback;
	vector<function<bool(T)> > predicate;
};

template<typename T>
SubjectObserver<T>::SubjectObserver(vector<function<bool(T)> > predicate, function<void(T)> onNext)
	:predicate(predicate),onNextCallback(onNext)
{

}

template<typename T>
SubjectObserver<T>::SubjectObserver(vector<function<bool(T)> > predicate, function<void(T)> onNext, function<void(T)> onComplete, function<void(exception)> onError)
	:predicate(predicate), onNextCallback(onNext), onCompleteCallback(onComplete), onErrorCallback(onError)
{

}

template<typename T>
SubjectObserver<T>::SubjectObserver(vector<function<bool(T)> > predicate, function<void(T)> onNext, function<void(T)> onComplete)
	:predicate(predicate), onNextCallback(onNext), onCompleteCallback(onComplete)
{

}


template <typename T>
void SubjectObserver<T>::OnNext(T data)
{
	for (auto iter = predicate.begin(); iter < predicate.end(); iter++)
	{
		if (!(* iter)(data))
		{
			return;
		}
	}
	onNextCallback(data);
}

template <typename T>
void SubjectObserver<T>::OnComplete(T data)
{
	for (auto iter = predicate.begin(); iter < predicate.end(); iter++)
	{
		if (!(*iter)(data))
		{
			return;
		}
	}
	onCompleteCallback(data);
}

template <typename T>
void SubjectObserver<T>::OnError(exception e)
{
	onErrorCallback(e);
}