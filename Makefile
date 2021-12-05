CC = g++

all:
	make compile
	make 01
	make 02
	make 03
	make 04
	make 05

01: 
	cd src/01; \
	./a.out

02:
	cd src/02; \
		./a.out

03:
	cd src/03; \
		./a.out

04:
	cd src/04; \
		./a.out

05:
	cd src/05; \
		./a.out

clean:
	for i in main; do find ./src -type f -name "a.out" -delete; done

compile:
	cd src/common && $(CC) -c -o common.o common.cpp
	for i in dir; do find ./src -type f -name "*.cpp" -not -name "common.cpp" -execdir $(CC) -c -o output.o "{}" \; -execdir $(CC) output.o ../common/common.o -lm \;; done
	for i in main; do find ./src -type f \( -name "output.o" -o -name "common.o" \) -delete; done