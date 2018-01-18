#ifndef TAQUIN
#define TAQUIN
#define ID_TAQUIN 1

#include "jeux.hpp"
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class taquin:public  jeux<int>{
private:
        int posX;
        int posY;
        
        
public:
     taquin(int,int,int);
     virtual ~taquin();
     
     virtual bool aGagner() const;
     virtual bool aPerdu()const;
      virtual void play();
     bool deplacer(char a);
     char randomMove();

};



#endif