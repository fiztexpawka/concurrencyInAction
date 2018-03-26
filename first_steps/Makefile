all: super_hello

super_hello: hello_world.o
	g++ hello_world.o -std=c++14 -o super_hello

hello_world.o: hello_world.cpp
	g++ -c hello_world.cpp -o hello_world.o -std=c++14

clean:
	rm -rf *.o super_hello
