#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "conduct.h"


struct conduct *conduct_create(const char *name, size_t a, size_t c){
  int fd;
  pthread_mutexattr_t ma;
  pthread_condattr_t ca;
    
  struct conduct * cdt;
    
  pthread_mutexattr_init(&ma);
  pthread_mutexattr_setpshared(&ma,PTHREAD_PROCESS_SHARED);
  pthread_condattr_init(&ca);
  pthread_condattr_setpshared(&ca,PTHREAD_PROCESS_SHARED);
  if(a < 0 || c < 0){ 
        
    fprintf(stderr,"taille ou capacite inferieur a zero\n");
    exit(EXIT_FAILURE);
  }
  if(a > c){
    fprintf(stderr,"a est inferieur a c\n");

        
  }
    
    
   
  if(name != NULL){
    if((fd = open(name, O_RDWR |O_CREAT  |O_TRUNC,0666))<0){
      perror("open ");
      exit(EXIT_FAILURE);
    }
    if (ftruncate(fd,c) == -1){
      perror("ftruncate ");
      exit(EXIT_FAILURE);
    }
  	
    if((cdt = mmap(0, sizeof(struct conduct)+c*sizeof(void),
		   PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
      perror("mmap ");
      exit(EXIT_FAILURE);
            
    }
        
    close(fd);
    sprintf(cdt->name,name);
        
  }else{
        
    if((cdt = mmap(0, sizeof(struct conduct)+c*sizeof(void),
		   PROT_READ | PROT_WRITE, MAP_SHARED |  MAP_ANONYMOUS , -1, 0)) == MAP_FAILED){
      perror("mmap ");
      exit(EXIT_FAILURE);
            
    }
  }
    
  cdt->buffer=mmap(NULL,c*sizeof(void),PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,-1,0);
  if (cdt->buffer==MAP_FAILED)
    {
      perror("mmap");
      exit(EXIT_FAILURE);
    }
    
  memset(cdt->buffer,0,c);
    
  //cdt->name = name;
  cdt->a = a;
  cdt->c = c;
  cdt->eof = 0;
  cdt->nbReader = 0;
  cdt->nbWritter = 0;
  //cdt->buffer = malloc(8*c);
  //cdt->verrou = malloc(sizeof(pthread_mutex_t));

  if(pthread_mutex_init (&(cdt->verrou), &ma)<0){
    perror("mutex int:");
  } 
    
    
  // cdt->lectureOk = malloc(sizeof(pthread_cond_t));
  // cdt->ecritureOk = malloc(sizeof(pthread_cond_t));
  if(pthread_cond_init (&(cdt->lectureOk),&ca)<0){
    perror("init cond:");
  }
  if(pthread_cond_init (&(cdt->ecritureOk),&ca)<0){
    perror("cond init: ");
  }
    
  pthread_mutexattr_destroy(&ma);
  pthread_condattr_destroy(&ca);
    
  return cdt;
    
}

struct conduct * conduct_open(const char *name){
  int fd;
  struct conduct * cdt;
    
  if((fd = open(name, O_RDWR))<0){
    perror("open ");
    exit(EXIT_FAILURE);
  }
    
  if((cdt = mmap(0, sizeof(struct conduct),
		 PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
    perror("mmap ");
    exit(EXIT_FAILURE);
            
  }
    
  close(fd);
    
  return cdt;
}


ssize_t conduct_write(struct conduct *c, const void *buf, size_t count){
  int i = 0;
  if(count < 1)                              //Si count < 0 on ne fait rien
    return count;
  if(pthread_mutex_lock (&(c->verrou))<0){
    perror("lock write");
  }
  if((c->eof)==1){                            // si un end of file est vrai on return -1                         
    errno = EPIPE; 
    if(pthread_mutex_unlock (&(c->verrou))<0){
      perror("lock write");
    }
    return -1;
  }
    
    
  while(1){
    if(c->n == c->c||(count >( c->c - c->n) && count < c->a)){     //si le buffer est plein  ou que count est > a l'espace disponible dans le buffer
      if(pthread_cond_signal(&(c->lectureOk))<0){
	perror("broadcast lectureok");
      }                                    
      while(c->n == c->c){
	c->nbWritter++;
                
	if(pthread_cond_wait(&(c->ecritureOk),&(c->verrou))<0){                //on attend que le buffer soit remplie
                    
	  perror("wait ecritureOk");   
	}
	if(c->eof==1){
	  errno = EPIPE;
	  return -1;
	}
	c->nbWritter--;
      }
            
    }
    if(count <= (c->c - c->n)){                                     //si count < a l'espace disponible dans le buffer
         
      memcpy(c->buffer+c->n,buf,count);                           //on copie buf dans buffer
	    
     /* if (msync(c,count,MS_SYNC ) < 0) {
	perror("msync");
	exit(EXIT_FAILURE);
 
      }*/

      c->n+=count;
      if(c->nbReader > 0){
	if(pthread_cond_signal (&(c->lectureOk))<0){
	  perror("broadcast lectureok:");
	}
      }
      if(pthread_mutex_unlock (&(c->verrou))<0){
	perror("write unlock");
      }
      return count;
    } 
    if(count > (c->c - c->n) && (c->c -c->n) >= c->a){   //si count > a l'espace disponible dans le bufffer
      i = (c->c - c->n)/c->a;
      memcpy(c->buffer+c->n,buf,i*c->a);             //on copie buf dans buffer en respectant les regles d'atomicite
    /*  if (msync(c,count,MS_SYNC ) < 0) {
	perror("msync");
	exit(EXIT_FAILURE);
 
      }*/

      c->n += i * c->a;
      if(c->nbReader > 0){
	if(pthread_cond_signal (&(c->lectureOk))<0){   //on au lecteur que le buffer est remplie
	  perror("broadcast lectureOk");
                    
	}
      }
      if(pthread_mutex_unlock (&(c->verrou))<0){
	perror("write unlock");
      }
           
      return i*c->a;
            
    }else if(count < c->a){
      if(c->nbReader > 0){
	if(pthread_cond_signal (&(c->lectureOk))<0){   //on au lecteur que le buffer est remplie
	  perror("broadcast lectureOk");
                    
	}
      }
      while((c->c - c->n) < count){
	c->nbWritter++;
	if(pthread_cond_wait(&(c->ecritureOk),&(c->verrou))<0){                //on attend que le buffer soit remplie
                
	  perror("wait ecritureOk");   
	}
      }
            
    }
    /* pthread_cond_signal (c->lectureOk);
       printf("write on bloque\n");
       if(c->eof==0)
       pthread_cond_wait(c->ecritureOk,c->verrou);
       printf("write on DEbloque\n");
       if((c->eof)==1){
       printf("WRITE test EOF\n");
       pthread_mutex_unlock (c->verrou);
       errno = EPIPE;
       return -1;
        
       }*/
        
  
  }
  
  return -1;
    
}


ssize_t conduct_read(struct conduct *c, void *buf, size_t count){ 
  //int eofInsere=0;
  //printf("n:%d count:%d\n",c->n,count);
  if(count < 1){
    return count;
        
  }
  if(pthread_mutex_lock (&(c->verrou))<0){
    perror("read lock");
  }
    
  // while(1){
  int tmp = c->n;
  if(c->n<=0){                                               //si le buffer est vide 
    if((c->eof) == 1){
      return 0;
    }else{
               
      if(pthread_cond_signal (&c->ecritureOk)<0){            //on previent les ecrivains qu'ils peuvent ecrire
                
	perror("broadcast");
                
      }
      while(c->n==0){
	c->nbReader++;
	if(pthread_cond_wait(&c->lectureOk,&c->verrou)<0){         //on attent qu'un ecrivain nous reveil
	  perror("wait read:");
	}
	c->nbReader--;
	if(c->eof == 1 && c->n == 0){
	  return 0;
	}
      }
    }
               
               
        
  } 
        
  if(count >= c->n){                         //si count superieur a la taille de donnée dans le buffer on lit n octet 
          

    tmp = c->n;
    memcpy(buf,c->buffer,c->n);

           
    if(c->nbWritter > 0)
      if(pthread_cond_signal (&c->ecritureOk)<0){
	perror("read broadcast:");
      }
    if(pthread_mutex_unlock (&(c->verrou))<0){
      perror("read unlock:");
    }

    c->n = 0;
    printf("tmp:%d n:%d count:%d\n",tmp,c->n,count);  
    return tmp;
  }
  if(count < c->n){                       //sinon on lit count octet
    tmp=c->n;
    memcpy(buf,c->buffer,count);
    
    memmove (c->buffer,c->buffer+count,c->n-count);  //on deplace les donnees non lut a l'avant du buffer
    /*if (msync(c,count,MS_SYNC ) < 0) {
      perror("msync");
      exit(EXIT_FAILURE);
 
    }*/
    if( c->nbReader > 0){
      if(pthread_cond_signal (&c->ecritureOk) < 0){
	perror("broadcast:");
      }
    }
    if(pthread_mutex_unlock (&(c->verrou))<0){
      perror("read unlock:");
    }
    c->n -= count;
   printf("n:%d count:%d tmp:%d\n",c->n,count,tmp);  
    return count;
  }
  return -1;
            
  //}
}

int conduct_write_eof(struct conduct *c){
  pthread_mutex_lock (&c->verrou);
  c->eof=1;
  if(c->nbWritter > 0 ){
        
    if(pthread_cond_signal (&c->ecritureOk) < 0){
      perror("broadcast ecritureok eof:");
    }
  }
  if(c->nbReader > 0){
    if(pthread_cond_signal (&c->lectureOk)<0){
      perror("broadcast eof lecutreok:");
    }
    
  }
  if(pthread_mutex_unlock (&(c->verrou))<0){
    perror("unlock eof: ");
  }
  return 1;
   
}

void conduct_close(struct conduct *conduct){
  int size = conduct->c;
  if(munmap(conduct->buffer,size) < 0){
    perror("munmap ");
    exit(EXIT_FAILURE);
  }
  if(munmap(conduct,size) < 0){
    perror("munmap ");
    exit(EXIT_FAILURE);
  }
    
    
}

void conduct_destroy(struct conduct *conduct){
  const char * pathname = conduct->name;
  conduct_close(conduct);
  if(pathname != NULL){
    if(remove(pathname) <0){
      perror("remove ");
      exit(EXIT_FAILURE);
    }
  }
}
/*int main(){
  struct conduct * c = conduct_create("titi",1,5);
  void * cg;
  //conduct_read(c,cg,5);
  int t = conduct_write(c,"hello",5);
  t = conduct_write(c,"hello",5);
  printf("%d",t);
  conduct_destroy(c);
    
  return 0;
  }*/
