#ifndef JEU2048NEGATIVE
#define JEU2048NEGATIVE

#define ID_JEU2048NEGATIVE 3

#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <cstdio>

#define ID_JEU2048NEGATIVE 3


#include "jeux.hpp"



class jeu2048NEGATIVE:public jeux<int>{
protected:
	
        int nFusion;
	int maxFusion;
       



public:
	
	
	jeu2048NEGATIVE(int,int,int);
        virtual ~jeu2048NEGATIVE();
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
