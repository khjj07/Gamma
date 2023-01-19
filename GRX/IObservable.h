#pragma once
#include <exception>
#include <functional>
#include <list>
using namespace std;

template <typename T>
class IObservable
{

public:
   virtual void Subscribe(function<void(T)>) abstract;
   virtual void Subscribe(function<void(T)>, function<void(T)>) abstract;
   virtual void Subscribe(function<void(T)>, function<void(T)>, function<void(exception)>) abstract;

};