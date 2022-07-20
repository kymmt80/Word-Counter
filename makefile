all: main mapper reducer

main: main.cpp build
	g++ main.cpp -o build/main

mapper: src/mapper.cpp build
	g++ src/mapper.cpp -o build/mapper

reducer: src/reducer.cpp build
	g++ src/reducer.cpp -o build/reducer

build: build
	mkdir build

.PHONY : run

run: main mapper reducer build
	mkdir tmp && cd build && ./main && cd .. && rm -r tmp