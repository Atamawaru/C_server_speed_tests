all: build run

build: speed_test.c
	gcc -Wall -Werror speed_test.c -lcurl -lcjson -o speed_test

run: build
	./speed_test
