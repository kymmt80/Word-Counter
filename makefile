all: main mapper reducer

main: main.cpp build_dir
	g++ main.cpp -o build/main

mapper: src/mapper.cpp build_dir
	g++ src/mapper.cpp -o build/mapper

reducer: src/reducer.cpp build_dir
	g++ src/reducer.cpp -o build/reducer

build_dir: build
	mkdir -p build

.PHONY : run

run: main mapper reducer build_dir
	bash prepare.sh && mkdir -p tmp && cd build && ./main && cd .. && rm -r tmp && rm -r testcases