CC = g++

all:
	make compile
	make 01
	make 02
	make 03
	make 04
	make 05
	make 06
	make 07
	make 08
	make 09
	make 10
	make 11
	make 12
	make 13
	make 14
	make 15
	make 16

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

06:
	cd src/06; \
		./a.out

07:
	cd src/07; \
		./a.out

08:
	cd src/08; \
		./a.out

09:
	cd src/09; \
		./a.out

10:
	cd src/10; \
		./a.out

11:
	cd src/11; \
		./a.out

12:
	cd src/12; \
		./a.out

13:
	cd src/13; \
		./a.out

14:
	cd src/14; \
		./a.out

15:
	cd src/15; \
		./a.out

16:
	cd src/16; \
		./a.out

clean:
	for i in main; do find ./src -type f -name "a.out" -delete; done

compile:
	cd src/common && $(CC) -c -o common.o common.cpp
	for i in dir; do find ./src -type f -name "*.cpp" -not -name "common.cpp" -execdir $(CC) -c -o output.o "{}" \; -execdir $(CC) output.o ../common/common.o -lm \;; done
	for i in main; do find ./src -type f \( -name "output.o" -o -name "common.o" \) -delete; done