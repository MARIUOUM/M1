CPP=g++ --std=c++11
CFLAGS  = -Wall -W -O2 -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT -I/usr/share/qt3/mkspecs/default -I. -I/usr/include/qt3
EXEC = Jeux

HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))


all: $(EXEC)


Jeux: $(OBJECTS)
	$(CPP) -o $@ $^ $(CFLAGS)

jeux.o: -c jeux.hpp
	$(CPP) -c -o $@ $< $(CFLAGS)
taquin.o: taquin.cpp taquin.hpp
	$(CPP) -c -o $@ $< $(CFLAGS)

TilesNegatives.o: TilesNegatives.cpp TilesNegatives.hpp
	$(CPP) -c -o $@ $< $(CFLAGS)
	
%.o: %.cpp $(HEADERS)
	$(CPP) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)

