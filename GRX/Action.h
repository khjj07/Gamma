#pragma once
#include <functional>

using namespace std;

template <typename T>
class Action
{
public:
	virtual void dummy() {};
};

template <typename T>
class QueryAction :public Action<T>
{
public:
	QueryAction(function<T(T)> act)
	{
		action = act;
	}
	function<T(T)> action;
	virtual void dummy() {};
};

template <typename T>
class PredicateAction :public Action<T>
{
public:
	PredicateAction(function<bool(T)> act)
	{
		action = act;
	}
	function<bool(T)> action;
	virtual void dummy() {};
};