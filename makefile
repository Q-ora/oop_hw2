all: poly.exe

poly.exe: poly.cpp
	g++ -g poly.cpp -o poly.exe

clean: poly.exe
	rm poly.exe