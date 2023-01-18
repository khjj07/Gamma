#pragma once
#include <functional>
#include <exception>
using namespace std;
template<typename T>
class Observable;

template <typename T>
class Observer
{
public:
	friend class Observable<T>;

public:
	Observer(function<void(T)>);
	Observer(function<void(T)>, function<void(T)>);
	Observer(function<void(T)>, function<void(T)>, function<void(T)>);

private:
	function<void(T)> OnNext;
	function<void(T)> OnComplete;
	function<void(exception)> OnError;
};

template<typename T>
Observer<T>::Observer(function<void(T)> onNext)
	:OnNext(onNext)
{

};

template<typename T>
Observer<T>::Observer(function<void(T)> onNext, function<void(T)> onComplete)
	: OnNext(onNext), OnComplete(onComplete)
{

};

template<typename T>
Observer<T>::Observer(function<void(T)> onNext, function<void(T)> onComplete, function<void(T)> onError)
	: OnNext(onNext), OnComplete(onComplete), OnError(onError)
{

};