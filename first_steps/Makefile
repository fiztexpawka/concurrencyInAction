all: super_hello.o

CFLAGS=-std=c++1z

super_hello.o: hello_world.o
	g++ hello_world.o $(CFLAGS) -o super_hello.o

hello_world.o: hello_world.cpp
	g++ -c hello_world.cpp $(CFLAGS) -o hello_world.o

clean:
	rm -rf *.o super_hello
