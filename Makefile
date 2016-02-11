all:
	-mkdir -p bin 
	g++ -std=c++11 -Wall -Werror -ansi -pedantic -o bin/rshell src/main.cpp
	
rshell:
	-mkdir -p bin 
	g++ -std=c++11 -Wall -Werror -ansi -pedantic -o bin/rshell src/main.cpp