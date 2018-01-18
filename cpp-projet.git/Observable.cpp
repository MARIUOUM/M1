#include "Observable.hpp"
#include "Observer.hpp"


Observable::Observable() : _m_observers(new list<Observer*>())
{
}


Observable::~Observable()
{
	delete _m_observers;
}

void Observable::attach(Observer *o)
{
	_m_observers->push_back(o);
}

void Observable::detach(Observer *o)
{
	_m_observers->remove(o);
}

void Observable::notifyAll()
{
	list<Observer*>::iterator it;
	for (it = _m_observers->begin(); it != _m_observers->end(); it++)
	{
		(*it)->update();
	}
}
