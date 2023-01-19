#pragma once
#include <functional>
#include <exception>
using namespace std;
template<typename T>
class Observable;

template <typename T>
class IObserver
{

public:
	virtual void OnNext(T) abstract;
	virtual void OnComplete(T) abstract;
	virtual void OnError(exception) abstract;
};