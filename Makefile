CC = g++

all:
	$(CC) -std=c++11 -o a.exe SCC.cpp

clean:
	rm -f a.exe

