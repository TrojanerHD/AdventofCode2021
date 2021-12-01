CC = g++

all:
	make compile
	make 01

01: 
	cd src/01; \
	./a.out

clean:
	for i in main; do find ./src -name "a.out" -delete; done

compile:
	for i in dir; do find ./src -name "*.cpp" -execdir $(CC) "{}" \;; done