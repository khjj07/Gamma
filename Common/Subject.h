#pragma once
#include <functional>
#include <exception>
#include <list>
using namespace std;
template <typename T>
class Observer;
template <typename T>
class Observable;

template <typename T>
class Subject : public Observable<T>
{
public:
	Subject();
	~Subject();

public:
	void OnNext(T);
	void OnComplete(T);
	void OnError(exception);
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
		for (auto iter = this->observables.begin(); iter != this->observables.end(); iter++)
		{
			(*iter).OnNext(data);
		}
	}
	catch (exception& e)
	{
		for (auto iter = this->observables.begin(); iter != this->observables.end(); iter++)
		{
			(*iter).OnError(e);
		}
	}

}

template<typename T>
void Subject<T>::OnComplete(T data)
{
	try
	{
		for (auto iter = this->observables.begin(); iter != this->observables.end(); iter++)
		{
			(*iter).OnComplete(data);
		}
	}
	catch (exception e)
	{
		for (auto iter = this->observables.begin(); iter != this->observables.end(); iter++)
		{
			(*iter).OnError(e);
		}
	}
}

template<typename T>
void Subject<T>::OnError(exception e)
{
	for (auto iter = this->observables.begin(); iter != this->observables.end(); iter++)
	{
		(*iter).OnError(e);
	}
}