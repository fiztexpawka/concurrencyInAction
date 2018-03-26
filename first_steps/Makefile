all: super_hello

CFLAGS=-std=c++14

super_hello: hello_world.o
	g++ hello_world.o $(CFLAGS) -o super_hello

hello_world.o: hello_world.cpp
	g++ -c hello_world.cpp $(CFLAGS) -o hello_world.o

clean:
	rm -rf *.o super_hello
