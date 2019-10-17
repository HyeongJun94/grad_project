CC = gcc
CXX = g++

all : pcServerHelper pcServerRas pcServerAndroid

pcServerHelper: pcServerHelper.o
	$(CC) -o $@ $^

pcServerRas: pcServerRas.o
	$(CC) -o $@ $^

pcServerAndroid: pcServerAndroid.o
	$(CXX) -o $@ $^

pcServerHelper.o : pcServerHelper.c
	$(CC) -c -o $@ $^

pcServerRas.o: pcServerRas.c
	$(CC) -c -o $@ $^

pcServerAndroid.o : pcServerAndroid.cpp
	$(CXX) -c -o $@ $^

clean : 
	rm pcServerHelper pcServerRas pcServerAndroid
	rm *.o
