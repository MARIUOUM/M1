CC = g++
CFLAGS = -std=c++11
LIBS = -lstdc++fs
EXEC = main
SRCS = $(wildcard *.cpp) $(wildcard *.hpp)

all:
	$(CC) -o $(EXEC) $(CFLAGS) $(SRCS) $(LIBS)

clean:
	rm -rf $(EXEC).exe $(EXEC)