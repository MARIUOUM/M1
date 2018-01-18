#ifndef JEU2048
#define JEU2048

#define ID_JEU2048 2

#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <cstdio>

#include "jeux.hpp"



class jeu2048:public jeux<int>{
protected:
	
        int nFusion;
	int maxFusion;
       



public:
	
	
	jeu2048(int,int,int);
    virtual ~jeu2048();
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
