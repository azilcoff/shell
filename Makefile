all: main

main: src/main.cpp
	mkdir -p bin
	c++ -o bin/shell -Wall -Wextra -std=c++20 src/main.cpp
clean:
	rm -rf bin
