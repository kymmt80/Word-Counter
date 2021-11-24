all: main mapper reducer

main: main.cpp
	g++ main.cpp -o main

mapper: mapper.cpp
	g++ mapper.cpp -o mapper

reducer: reducer.cpp
	g++ reducer.cpp -o reducer