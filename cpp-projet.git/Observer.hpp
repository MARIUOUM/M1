#ifndef OBSERVER_HPP_INCLUDED
#define OBSERVER_HPP_INCLUDED

#include "Observable.hpp"

class Observable;

class Observer
{
protected:
	Observer();
public:
	~Observer();
	virtual void update() = 0;
};

#endif
