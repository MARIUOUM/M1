#ifndef OBSERVABLE_HPP_INCLUDED
#define OBSERVABLE_HPP_INCLUDED

#include "libs.hpp"

class Observer;

class Observable
{
private:
	list<Observer*> * _m_observers;
public:
	Observable();
	~Observable();
	virtual void attach(Observer*);
	virtual void detach(Observer*);
	virtual void notifyAll();
};

#endif