#ifndef TWOTHREEFIVE
#define TWOTHREEFIVE

#define ID_TWOTHREEFIVE 4

#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <cstdio>




#include "jeux.hpp"



class TwoThreeFive:public jeux<int>{
protected:
	
        int nFusion;
	int maxFusion;
       



public:
	
	
	TwoThreeFive(int,int,int);
        virtual ~TwoThreeFive();
	void right();
	void left();
	void up();
	void down();
	virtual bool aGagner()const;
    virtual bool aPerdu()const;
    virtual char randomMove();
    void newCase();
    virtual void play();
    bool testMove(char)const;


};


#endif
