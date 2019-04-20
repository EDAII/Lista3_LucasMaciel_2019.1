all:
	g++ -std=c++14 -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system

install:
	sudo apt-get install libsfml-dev

run:
	./main