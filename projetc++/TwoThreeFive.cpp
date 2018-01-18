
#include "TwoThreeFive.hpp"


TwoThreeFive::TwoThreeFive(int taille,int c,int m):jeux(taille,taille,m),nFusion(0),maxFusion(taille/2){
	
	
	
	for (int i=0; i < taille*taille; i++){
                
    	grid[i] = new Case<int>();
	
        }
   		


		int pos1= generateRandomValue(taille*taille);
		int pos2 = generateRandomValue(taille*taille);
		//int value = (rand() % 2);
		(*grid[(pos1/row)*row+(pos2%columns)]).setValue(((rand()%(columns))?((rand()%(columns)?2:5)):3));
		(*grid[(pos2/row)*columns+(pos2%columns)]).setValue(((rand()%(columns))?((rand()%(columns)?2:5)):3));
 }
 
 TwoThreeFive::~TwoThreeFive(){
}

bool TwoThreeFive::testMove(char input)const{
   
	switch(input){
 		case 'u':
			for(int j=0;j<columns;j++){
				for(int i=0; i<row;i++){
					if(i==0){
                                          
						if((*grid[i*columns+j]).getValue()==0)
							return true;
					}
					else{

						if((*grid[i*columns+j]).getValue()==0 || (*grid[i*columns+j]).getValue()==(*grid[(i-1)*columns+j]).getValue())
							return true;
					}
				}

			}
			return false;
			case 'l':
				for(int i=0;i<row;i++){
					for(int j=0; j<columns; j++){
						if(j==0){
						if((*grid[i*columns+j]).getValue()==0)
							return true;
					}
					else{

						if((*grid[i*columns+j]).getValue()==0|| (*grid[i*columns+j]).getValue()==(*grid[i*columns+(j-1)]).getValue())
							return true;
					}
				}
			}
				return false;
			case 'd':

			for(int j=0;j<columns;j++){
					for(int i=row-1; i>-1; i--){
						if(i==row-1){
						if((*grid[i*columns+j]).getValue()==0)
							return true;
					}
					else{

						if((*grid[i*columns+j]).getValue()==0|| (*grid[i*columns+j]).getValue()==(*grid[(i+1)*columns+j]).getValue())
							return true;
					}
				}
			}
				return false;

			case 'r':

			for(int i=0;i<row;i++){
					for(int j=columns-1; j>-1; j--){
						if(j==columns-1){
						if((*grid[i*columns+j]).getValue()==0)
							return true;
					}
					else{

						if((*grid[i*columns+j]).getValue()==0|| (*grid[i*columns+j]).getValue()==(*grid[i*columns+(j+1)]).getValue())
							return true;
					}
				}
			}
				return false;
				default:
				return false;
	}
}
void TwoThreeFive::up(){
        bool move = false;
	 for(int j=0;j<columns;j++)
		{
			nFusion=0;
			for(int i=0;i<row;i++)
			{
                while(true)
				{

					if(i == 0) 
                       	break;     


					if((*grid[i*columns+j]).getValue()==(*grid[(i-1)*columns+j]).getValue() && (*grid[i*columns+j]).getValue()!=0 && nFusion<=maxFusion){
						 (*grid[(i-1)*columns+j]).setValue((*grid[(i-1)*columns+j]).getValue() + (*grid[i*columns+j]).getValue());
						 (*grid[i*columns+j]).setValue(0);
                                                 move = true;
						nFusion++;
					}else{
						if((*grid[i*columns+j]).getValue()!=0 && (*grid[(i-1)*columns+j]).getValue()==0){
							(*grid[(i-1)*columns+j]).setValue((*grid[i*columns+j]).getValue());
							(*grid[i*columns+j]).setValue(0);
                                                        move = true;
							i--;

						}else

						break;
					}
					
				}
				
			}
		}
		if(move)
                    newCase();

	
}


void TwoThreeFive:: left(){
	
        bool move=false;
	for(int i=0;i<row;i++)
		{
			for(int j=0;j<columns;j++)
			{
				while(true)
				{
					if(j==0)
						break;


					if(j==0)
						break;

					if((*grid[i*columns+j]).getValue()==(*grid[i*columns+(j-1)]).getValue() && (*grid[i*columns+j]).getValue()!=0 && nFusion<=maxFusion){
					(*grid[i*columns+(j-1)]).setValue((*grid[i*columns+(j-1)]).getValue()+(*grid[i*columns+(j)]).getValue());
					(*grid[i*columns+j]).setValue(0);
					nFusion++;
                                        move = true;
					}
					else{
					if((*grid[i*columns+j]).getValue()!=0 && (*grid[i*columns+(j-1)]).getValue()==0){
						(*grid[i*columns+(j-1)]).setValue((*grid[i*columns+j]).getValue());
						(*grid[i*columns+j]).setValue(0);
	                                        move = true;
						j--;
					}else
					break;

			}
		}
	}
    }
    if(move)
        newCase();

	
}

    
void TwoThreeFive::down(){
        bool move = false;
        for(int j=0;j<columns;j++){
		nFusion=0;
		for(int i=row-1;i>-1;i--){
                    while(true){
                      

			if(i==row-1)
                                break;
                        
			      if((*grid[i*columns+j]).getValue()==(*grid[(i+1)*columns+j]).getValue() && (*grid[i*columns+j]).getValue()!=0 && nFusion<=maxFusion){
						 (*grid[(i+1)*columns+j]).setValue((*grid[(i+1)*row+j]).getValue() + (*grid[i*row+j]).getValue());
						 (*grid[i*row+j]).setValue(0);
                                                 move = true;
						nFusion++;
                                                
                        }else{
                                if((*grid[i*row+j]).getValue()!=0 && (*grid[(i+1)*row+j]).getValue()==0){
							(*grid[(i+1)*row+j]).setValue((*grid[i*row+j]).getValue());
							(*grid[i*row+j]).setValue(0);
                                                        move = true;
							i++;

                                }else

                                    break;
                        }
					
                    }
				
                }
        }
        if(move)
            newCase();
}

void TwoThreeFive::right(){
    bool move = false;
 for(int i=0;i<row;i++)
		{
			nFusion=0;
			for(int j=row-1;j>-1;j--)
			{
                while(true)
				{

					if(j==row-1)
						break;
				if((*grid[i*row+j]).getValue()==(*grid[i*row+(j+1)]).getValue() && (*grid[i*row+j]).getValue()!=0 && nFusion<=maxFusion){
						 (*grid[i*row+(j+1)]).setValue((*grid[i*row+(j+1)]).getValue() + (*grid[i*row+j]).getValue());
						 (*grid[i*row+j]).setValue(0);
                                                 move = true;
						nFusion++;
					}else{
						if((*grid[i*row+j]).getValue()!=0 && (*grid[i*row+(j+1)]).getValue()==0){
							(*grid[i*row+(j+1)]).setValue((*grid[i*row+j]).getValue());
							(*grid[i*row+j]).setValue(0);
                                                        move = true;
							j++;

						}else

						break;
					}
					
				}
				
			}
		}
		if(move)
                    newCase();
}

bool TwoThreeFive::aPerdu()const{
    if(testMove('u')||testMove('l')||testMove('r')||testMove('d'))
    	return false;
    else
     return true;
}

bool TwoThreeFive::aGagner()const{
    for(int i=0;i<row*row;i++){
            if(grid[i]->getValue()==2048)
                return true;
        
    }
    return false;
}


void TwoThreeFive::newCase(){
	vector<int> vector;
	for(int i=0; i<row;i++)
		for(int j=0;j<row;j++)
			if((*grid[i*columns+j]).getValue()==0)
				vector.push_back(columns * i+j);
        if(vector.size()>0){
	int pos1=vector[generateRandomValue(vector.size())];
	
		  (*grid[pos1/row*row+pos1%columns]) = rand()%2?(rand()%2?2:3):5;

}
        }
    
	

char TwoThreeFive::randomMove(){
    char t[4]= {'u','d','l','r'};
    int r = std::rand() % 4;
    return t[r];
    
}
 

void TwoThreeFive::play(){

while(true){
        if(aPerdu()){

		cout<< "Game Over!!"<<endl;
		break;

	}
	char input;
	if(mode==1){
         input=getchar();
        cout<< "Choisissez le mouvement a effectuer 'u', 'l', 'd'ou 'r':"<<endl;
                    
		  cin>>input;
        }else{
             input = randomMove();
        }
	
	if(!testMove(input)){
                if(mode==1)
		  cout<< "Mouvement invalide!"<<endl;
		

	}else{

	

	switch(input){


		 case 'l':
			            left();
				    	//std::cin.clear();
			            //cin.ignore();

			            break;
			        
			        case 'r':
			             right();
			        
					    //std::cin.clear();
					    //cin.ignore();
			            break;
			        
			        case 'd':
			           down();
					    //std::cin.clear();
						//cin.ignore();
			            break;
			        
			        case 'u':
			            up();
			            //std::cin.clear();
			   			//cin.ignore();
			            break;
		            default:
		            	cout<<"entrer un choix valide";
	            	break;
			    }
			   
       
        affichage();
	}
	
        }

}






// int main(){
//             std::srand(std::time(0)); 
// 	  cout<<"Bienvenu! \nEntrez la taille de la grille: ";
// 	  char ch=getchar();
// 	  int n = (int)((char)ch - '0');
//          
//             char m=getchar();
//            
//           while((char)m!='1'&&(char)m!='2'){
//            cout << "Enter 1 pour le mode joueur et 2 pour le mode robot: " << endl;
//              m=getchar();
//              
//           }
// 		
//             int md = (int)((char)m - '0');
//             jeu2048 g(n,n,md);
// 	 
// 	 
//        
//          	g.newCase();
//          	
// 
// 
// 	    if (md ==1) {
//             cout <<"Choisissez u pour effectuer un mouvement vers le haut."<<endl;
//             cout <<"Choisissez d pour effectuer un mouvement vers le bas."<<endl;
//             cout <<"Choisissez l pour effectuer un mouvement vers la gauche."<<endl;
//             cout <<"Choisissez r pour effectuer un mouvement vers la droite."<<endl;
//             g.affichage();
//           g.play();
//         }else {
//           g.play();
//         }
// 
//         
// 	return 0;
// }
